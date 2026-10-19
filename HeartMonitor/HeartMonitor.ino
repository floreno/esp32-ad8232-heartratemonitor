#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <esp_system.h>
#include <esp_timer.h>
#include "sample_packet.h"
#include "config.h"
#include "web_page.h"

WebServer server(80);
DNSServer dnsServer;
uint16_t samples[Config::SAMPLE_COUNT] = {};
size_t writeIndex = 0;
size_t sampleCount = 0;
portMUX_TYPE sampleMux = portMUX_INITIALIZER_UNLOCKED;
TaskHandle_t samplingTask = nullptr;
esp_timer_handle_t samplingTimer = nullptr;
uint32_t missedSamples = 0;
uint32_t minIntervalUs = UINT32_MAX, maxIntervalUs = 0;
uint32_t totalSamples = 0;
uint32_t sampleSession = 0;
uint8_t currentLeadStatus = 0;

// Gemeinsamer Einstieg für die lokale Anzeige und eine spätere MQTT-Anbindung.
void recordSample(uint16_t value) {
  portENTER_CRITICAL(&sampleMux);
  currentLeadStatus = value >> 14;
  // Auch nach einem Sequenzüberlauf eine eindeutig neue Messsitzung beginnen.
  if (totalSamples == UINT32_MAX) {
    ++sampleSession;
    totalSamples = 0; writeIndex = 0; sampleCount = 0;
  }
  samples[writeIndex] = value;
  writeIndex = (writeIndex + 1) % Config::SAMPLE_COUNT;
  if (sampleCount < Config::SAMPLE_COUNT) ++sampleCount;
  ++totalSamples;
  portEXIT_CRITICAL(&sampleMux);
}

// Fehlende Timertermine erhalten ihre Position auf der Zeitachse.
// Keine ADC-Werte erfinden und keine neue Sitzung für kurze Verzögerungen.
void recordMissingSamples(uint32_t count) {
  if (!count) return;
  portENTER_CRITICAL(&sampleMux);
  SamplePacket::insertMissing(samples, Config::SAMPLE_COUNT, writeIndex,
      sampleCount, totalSamples, sampleSession, count);
  missedSamples+=count;
  portEXIT_CRITICAL(&sampleMux);
}

// Timer meldet nur den Termin; kalibrierte ADC-Aufrufe laufen in eigener Task.
void samplingTick(void*) {
  if (samplingTask) xTaskNotifyGive(samplingTask);
}
void samplingWorker(void*) {
  int64_t previousUs = 0;
  unsigned int samplesSinceYield = 0;
  for (;;) {
    const uint32_t ticks = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    const int64_t nowUs = esp_timer_get_time();
    const uint32_t elapsedUs = previousUs ? static_cast<uint32_t>(nowUs - previousUs) : 0;
    // Mehrere aufgelaufene Termine: nur einmal aktuell messen, fehlende
    // Termine als Lücken speichern. Jitter allein setzt die Sitzung nicht zurück.
    if (ticks > 1) recordMissingSamples(ticks-1);
    if (elapsedUs) {
      portENTER_CRITICAL(&sampleMux);
      minIntervalUs = min(minIntervalUs, elapsedUs);
      maxIntervalUs = max(maxIntervalUs, elapsedUs);
      portEXIT_CRITICAL(&sampleMux);
    }
    previousUs = nowUs;
    const uint16_t millivolts = analogReadMilliVolts(Config::SENSOR_PIN);
    const uint8_t leads = (digitalRead(Config::LEAD_OFF_MINUS_PIN) == HIGH ? 1 : 0)
                        | (digitalRead(Config::LEAD_OFF_PLUS_PIN) == HIGH ? 2 : 0);
    recordSample(SamplePacket::packSample(millivolts, leads));
    // Bei dauerhaftem Rückstau würde ulTaskNotifyTake nicht mehr blockieren.
    // Regelmäßig auch Webserver/Idle-Task auf dem einzelnen C3-Kern ausführen.
    if (++samplesSinceYield >= 16) { samplesSinceYield=0;vTaskDelay(1); }
  }
}

void sendSamples() {
  // Nur kopieren unter Sperre; String-Erzeugung und HTTP bleiben außerhalb.
  static uint16_t snapshot[Config::SAMPLE_COUNT];
  size_t count, index;uint32_t total, missed, minUs, maxUs;uint8_t leads;
  portENTER_CRITICAL(&sampleMux);
  memcpy(snapshot, samples, sizeof(samples));
  count=sampleCount;index=writeIndex;total=totalSamples;leads=currentLeadStatus;
  missed=missedSamples;minUs=minIntervalUs;maxUs=maxIntervalUs;
  portEXIT_CRITICAL(&sampleMux);
  String json;
  json.reserve(Config::SAMPLE_COUNT * 5 + 160);
  json = "{\"intervalUs\":";
  json += Config::SAMPLE_INTERVAL_US;
  json += ",\"total\":";
  json += total;
  json += ",\"gain\":";
  json += Config::ECG_GAIN;
  json += ",\"referenceMv\":";
  json += Config::ECG_REFERENCE_MV;
  json += ",\"unit\":\"mV-output\",\"values\":[";
  const size_t first = (index + Config::SAMPLE_COUNT - count) % Config::SAMPLE_COUNT;
  for (size_t i = 0; i < count; ++i) {
    if (i) json += ',';
    const uint16_t word = snapshot[(first + i) % Config::SAMPLE_COUNT];
    if ((word >> 14) || (word & SamplePacket::VALUE_MASK) == SamplePacket::MISSING_SAMPLE) json += "null";
    else json += word & SamplePacket::VALUE_MASK;
  }
  json += "],\"leadOff\":[";
  for (size_t i = 0; i < count; ++i) {
    if (i) json += ',';
    json += snapshot[(first + i) % Config::SAMPLE_COUNT] >> 14;
  }
  json += "],\"leadStatus\":";
  json += leads;
  json += ",\"timing\":{\"missed\":";json += missed;
  json += ",\"minIntervalUs\":";json += minUs == UINT32_MAX ? 0 : minUs;
  json += ",\"maxIntervalUs\":";json += maxUs;json += "}}";
  server.sendHeader("Cache-Control", "no-store");
  server.send(200, "application/json", json);
}

void sendSamplePacket() {
  uint32_t after = 0, requestedSession = 0;
  const bool hasCursor = server.hasArg("after") && server.hasArg("session");
  if ((server.hasArg("after") || server.hasArg("session")) &&
      (!hasCursor || !SamplePacket::parseUint32(server.arg("after").c_str(), after) ||
       !SamplePacket::parseUint32(server.arg("session").c_str(), requestedSession))) {
    server.send(400, "text/plain", "Ungueltiger Messcursor");
    return;
  }
  // Feste Paketgröße: keine JSON-Erzeugung oder dynamischen Messwert-Strings.
  static uint8_t packet[SamplePacket::HEADER_BYTES + SamplePacket::MAX_VALUES * 2];
  portENTER_CRITICAL(&sampleMux);
  const auto range = SamplePacket::selectRange(totalSamples, sampleCount, after,
                                               hasCursor && requestedSession == sampleSession);
  const size_t length = SamplePacket::encode(packet, sampleSession, range, totalSamples,
      Config::SAMPLE_INTERVAL_US, Config::ECG_GAIN, Config::ECG_REFERENCE_MV,
      samples, Config::SAMPLE_COUNT, writeIndex, sampleCount, currentLeadStatus);
  portEXIT_CRITICAL(&sampleMux);
  server.sendHeader("Cache-Control", "no-store");
  server.setContentLength(length);
  server.send(200, "application/octet-stream", "");
  server.sendContent(reinterpret_cast<const char*>(packet), length);
}

// Unbekannte HTTP-Anfragen umfassen auch die Portal-Prüfungen von
// Android, Apple und Windows. Immer zur lokalen IP umleiten, damit
// relative API-Aufrufe anschließend auf demselben Ursprung bleiben.
void redirectToPortal() {
  server.sendHeader("Cache-Control", "no-store");
  server.sendHeader("Location", String("http://") + WiFi.softAPIP().toString() + "/", true);
  server.send(302, "text/plain", "Lokale Messanzeige oeffnen");
}

void setup() {
  Serial.begin(115200);
  sampleSession = esp_random();
  pinMode(Config::SENSOR_PIN, INPUT);
  pinMode(Config::LEAD_OFF_MINUS_PIN, INPUT);
  pinMode(Config::LEAD_OFF_PLUS_PIN, INPUT);
  analogReadResolution(12);
  analogSetPinAttenuation(Config::SENSOR_PIN, ADC_11db);
  WiFi.mode(WIFI_AP);
  if (!WiFi.softAP(Config::AP_SSID, Config::AP_PASSWORD)) {
    Serial.println("Hotspot konnte nicht gestartet werden.");
    return;
  }
  // AP-Start erfolgt asynchron; kurz begrenzt erneut versuchen, falls nötig.
  bool powerApplied = false;
  for (unsigned int attempt = 0; attempt < 10; ++attempt) {
    if (WiFi.setTxPower(Config::WIFI_TX_POWER)) {
      powerApplied = true;
      break;
    }
    delay(20);
  }
  if (powerApplied) {
    Serial.print("WLAN-Sendeleistungsgrenze (dBm): ");
    Serial.println(static_cast<int>(WiFi.getTxPower()) / 4.0f, 2);
  } else {
    Serial.println("WLAN-Sendeleistung konnte nicht reduziert werden.");
  }
  // Alle DNS-Namen im Hotspot auf diesen ESP auflösen.
  dnsServer.start(53, "*", WiFi.softAPIP());
  server.on("/", HTTP_GET, []() {
    server.sendHeader("Cache-Control", "no-store");
    server.send_P(200, "text/html; charset=utf-8", WEB_PAGE);
  });
  server.on("/api/samples", HTTP_GET, sendSamples);
  server.on("/api/samples.bin", HTTP_GET, sendSamplePacket);
  server.onNotFound(redirectToPortal);
  server.begin();
  Serial.print("WLAN: ");
  Serial.println(Config::AP_SSID);
  Serial.print("Webseite: http://");
  Serial.println(WiFi.softAPIP());
  // Erstkalibrierung vor dem Start der periodischen Erfassung.
  analogReadMilliVolts(Config::SENSOR_PIN);
  if (xTaskCreate(samplingWorker, "ecg-sampling", 4096, nullptr, 3, &samplingTask) != pdPASS) {
    Serial.println("Mess-Task konnte nicht gestartet werden.");return;
  }
  esp_timer_create_args_t timerArgs = {};
  timerArgs.callback = samplingTick;timerArgs.name = "ecg-sampling";
  if (esp_timer_create(&timerArgs, &samplingTimer) != ESP_OK ||
      esp_timer_start_periodic(samplingTimer, Config::SAMPLE_INTERVAL_US) != ESP_OK) {
    Serial.println("Mess-Timer konnte nicht gestartet werden.");
    vTaskDelete(samplingTask);samplingTask=nullptr;return;
  }
  Serial.printf("Abtastrate: %lu Samples/s\n", 1000000UL / Config::SAMPLE_INTERVAL_US);
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
}
