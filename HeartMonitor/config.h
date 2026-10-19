#pragma once
#include <WiFi.h>

// Herzschlagerkennung im Browser: vor dem Kompilieren anpassen.
// Mindestdauer ohne Kontaktlücke/längere Übersteuerung, in Sekunden (z. B. 1 oder 2).
#define HEART_MIN_SIGNAL_SECONDS 2
// Mindestanzahl erkannter Spitzen; 3 Schläge ergeben 2 Schlagabstände.
#define HEART_MIN_BEATS 3
// Toleranz für reine Timinglücken (keine Elektroden-Kontaktfehler).
#define HEART_MAX_TIMING_GAP_MS 40
#define HEART_MAX_TIMING_GAP_PERCENT 10
static_assert(HEART_MAX_TIMING_GAP_MS >= 0 && HEART_MAX_TIMING_GAP_MS <= 100, "Timingluecke: 0 bis 100 ms");
static_assert(HEART_MAX_TIMING_GAP_PERCENT >= 0 && HEART_MAX_TIMING_GAP_PERCENT <= 25, "Lueckenanteil: 0 bis 25 Prozent");
static_assert(HEART_MIN_SIGNAL_SECONDS >= 0.5 && HEART_MIN_SIGNAL_SECONDS <= 10, "HEART_MIN_SIGNAL_SECONDS: 0.5 bis 10 Sekunden");
static_assert(HEART_MIN_BEATS >= 2 && HEART_MIN_BEATS <= 10, "HEART_MIN_BEATS: 2 bis 10");

namespace Config {
constexpr char AP_SSID[] = "HeartMonitor";
// Reduzierte maximale Sendeleistung: 8,5 dBm (~7 mW HF-Leistung).
// Für noch kürzere Distanz ggf. WIFI_POWER_5dBm; mehr Reichweite: WIFI_POWER_11dBm.
constexpr wifi_power_t WIFI_TX_POWER = WIFI_POWER_8_5dBm;
constexpr char AP_PASSWORD[] = "herzkurve123"; // Mindestens 8 Zeichen
// Vor dem Anschluss anhand des Pinouts deines konkreten Boards prüfen.
constexpr unsigned char SENSOR_PIN = 4;
constexpr unsigned char LEAD_OFF_MINUS_PIN = 3;
constexpr unsigned char LEAD_OFF_PLUS_PIN = 1;
constexpr unsigned long SAMPLE_INTERVAL_US = 1000; // 1000 Hz, mit korrigierter Kontaktfreigabe und Task-Yield
// SparkFun AD8232: 100 * (1 + 1 MOhm / 100 kOhm), nominell.
constexpr unsigned int ECG_GAIN = 1100;
// REFOUT liegt nominell bei Versorgung / 2. Für genauere Werte messen/anpassen.
constexpr unsigned int ECG_REFERENCE_MV = 1650;
constexpr unsigned int SAMPLE_COUNT = 5UL * 1000000UL / SAMPLE_INTERVAL_US; // Fünf Sekunden
}
