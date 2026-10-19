# ESP32-C3 + AD8232 Heart Rate Monitor

Ein lokaler EKG-Monitor mit **ESP32-C3 SuperMini** und **SparkFun AD8232 Heart Rate Monitor**. Der ESP32 stellt einen eigenen WLAN-Hotspot bereit; Anzeige, Herzfrequenzschätzung und Kurvenarchiv laufen im Browser. Die Oberfläche benötigt weder Cloud noch externe Webressourcen.

- Livekurve mit EKG-Raster, mV-Achse, Autozoom und Zentrierung
- Fließende Ansicht oder Schreibstrahl von links nach rechts
- Geschätzte elektrische Herzfrequenz und Trendpfeil
- Bis zu 100 ausgerichtete Herzschlagsamples mit Mittelwert, Median und Streuungsband
- Manuelle Zeitmessung an der Mittelkurve
- Lokales Kurvenarchiv mit SVG-Download und vergrößerbarer Vorschau
- Elektrodenstatus und integrierte Platzierungshilfe

## Sicherheit und Grenzen

**Bei angelegten Elektroden ausschließlich Batteriebetrieb verwenden. Keine gleichzeitige USB-Verbindung zu Rechner, Ladegerät oder anderen netzbetriebenen Geräten. Zum Programmieren die Elektroden vom Körper trennen.**

Dieser Aufbau ist kein medizinisch geprüftes Messgerät. Erkennung, Spannungsdarstellung und Zeitmessung sind experimentell und nicht zur Diagnose oder Überwachung medizinischer Zustände bestimmt. Bewegungen, Störungen, Kontaktfehler und abgeschnittene Signale können falsche oder fehlende Anzeigen verursachen.

## Hardware und Verkabelung

Benötigt werden ein ESP32-C3 SuperMini, ein SparkFun AD8232-Modul, ein passendes Elektrodenkabel mit drei Elektroden, Verbindungsleitungen und eine für das Board geeignete Batterieversorgung. Bei anderen AD8232-Platinen können Verstärkung, Pinbelegung und Beschaltung abweichen.

![Schematische Verbindung zwischen ESP32-C3 und AD8232](assets/wiring.svg)

Die Zeichnung zeigt die **elektrischen Verbindungen**, nicht die räumliche Anordnung der Pins. Vor dem Anschluss die Beschriftung und das Pinout des konkreten Boards prüfen.

| AD8232 | ESP32-C3 SuperMini | Funktion |
|---|---|---|
| 3.3V | 3V3 | Versorgung des Sensors mit 3,3 V |
| GND | GND | Gemeinsame Masse |
| OUTPUT | GPIO 4 | Analoger Sensorausgang |
| LO− | GPIO 3 | Digitaler Kontaktstatus |
| LO+ | GPIO 1 | Digitaler Kontaktstatus |
| SDN | Unverbunden | Beim SparkFun-Modul durch vorhandenen Pull-up beschaltet |

Die Elektroden werden am AD8232 angeschlossen. Maßgeblich sind die Kabelbeschriftungen **RA**, **LA** und **RL**. Die Hilfe in der Oberfläche zeigt RA rot, LA gelb und RL grün; diese Farben sind keine universelle Kabelnorm.

## Einrichtung

1. In Arduino IDE 2 das Boardpaket **esp32 by Espressif Systems** installieren.
2. `HeartMonitor/HeartMonitor.ino` öffnen. Alle Header im selben Ordner belassen.
3. **ESP32C3 Dev Module** auswählen; **USB CDC On Boot: Enabled**, beim üblichen SuperMini **4 MB Flash** und den passenden USB-Port einstellen.
4. Anschlüsse und Einstellungen in [`HeartMonitor/config.h`](HeartMonitor/config.h) prüfen.
5. Sketch hochladen. Bei Bedarf BOOT halten, RESET kurz drücken, BOOT loslassen und erneut hochladen.
6. Für den Messbetrieb USB trennen und auf Batterieversorgung wechseln.
7. Mit dem WLAN **HeartMonitor**, Standardpasswort **herzkurve123**, verbinden. Das Passwort lässt sich vor dem Kompilieren in `config.h` ändern.
8. **http://192.168.4.1/** im Browser öffnen. Je nach Betriebssystem öffnet sich zunächst ein Captive Portal. Für verlässliche Cookies und Downloads dieselbe IP in einem normalen Browser verwenden.

Der serielle Monitor arbeitet mit **115200 Baud** und meldet unter anderem die Hotspot-Adresse und den Start der Erfassung. Nach einem Firmware-Upload die Browserseite neu laden.

## Liveanzeige

**Fließende Kurve** bewegt Signal und Raster gleichmäßig nach links. **Schreibstrahl links → rechts** zeichnet bei stationärem Raster eine Seite und beginnt am rechten Rand wieder links. Ein Wiedergabepuffer von etwa 550 ms gleicht kurze WLAN-Verzögerungen aus. Die Anzeige hält an, wenn neue Daten fehlen.

**Autozoom** und **Zentrieren** sind standardmäßig aktiv und unabhängig schaltbar. Autozoom passt die Höhe an das sichtbare Signal an. Zentrieren verschiebt die Mittellinie; die Bildschirmmitte entspricht dann keiner festen elektrischen Null. Ohne Autozoom gilt die unter „Darstellung einstellen“ gewählte Höhe.

Unter **Spannung** stehen zwei Darstellungen zur Verfügung:

- **EKG · mV (geschätzt):** `(Modulausgang_mV − Referenz_mV) / Gesamtverstärkung`
- **Modulausgang · mV:** kalibrierter ADC-Spannungswert am ESP32-Eingang

Der ADC verwendet `analogReadMilliVolts()` mit `ADC_11db`. Für das SparkFun-Modul sind nominell **1100-fache Verstärkung** und **1650 mV Referenz** eingestellt. Die Verstärkung ist frequenzabhängig; diese Umrechnung ersetzt keine Kalibrierung der gesamten Messkette. Der spezifizierte ADC-Messbereich des ESP32-C3 reicht bei dieser Einstellung ungefähr bis **2500 mV**. Darüber liegende Signalanteile können abgeschnitten werden und lassen sich nicht rekonstruieren.

Ein kleines Rasterkästchen entspricht nominal **0,04 s**, ein großes **0,20 s**. Bei **0,1 mV/Kästchen** entspricht die Amplitudenaufteilung klassischem EKG-Papier; Bildschirmkästchen besitzen jedoch keine garantierte physische Millimetergröße. Die geltende Skala steht unter der Kurve und in den SVG-Exporten.

Ansicht, Spannung, Höhe, Autozoom, Zentrierung, Archivlänge und die Darstellungsoptionen der Herzschlagsamples werden für ein Jahr im lokalen Cookie `heartmonitor_settings` gespeichert. **Pause** hält nur die Liveanzeige an; Erfassung, Status, Auswertung und Archiv laufen weiter.

## Kontaktstatus und Datenlücken

LO− und LO+ werden mit jeder Messung eingelesen. Die Oberfläche bezeichnet GPIO 3 als **Rot**, GPIO 1 als **Grün** und zeigt deren unmittelbaren Zustand als verbunden/nicht verbunden. **Gelb** ist ausschließlich abgeleitet: verbunden, sobald mindestens einer der beiden Eingänge LOW meldet. Es gibt keinen dritten Messeingang. Insbesondere wird der RL-Kontakt nicht separat überwacht; die Anzeigen bestätigen keinen vollständigen Kontakt aller Elektroden.

Beim Start und nach einem bestätigten Kontaktfehler wird die Kurve erst nach insgesamt einer Sekunde gültiger LOW-Messwerte freigegeben. Kurze tolerierte Timinglücken zählen dabei nicht als gültige Messzeit. Ein anhaltender Kontaktfehler sperrt eine bereits freigegebene Anzeige nach einer Sekunde; auch kürzere Fehler bleiben an den betroffenen Messpunkten als Lücken erhalten. Bei Verbindungsverlust wird der Status als veraltet gekennzeichnet.

Reine Timinglücken werden getrennt von Kontaktfehlern behandelt. Die Standardtoleranz beträgt **40 ms am Stück** und höchstens **10 % fehlende Punkte** im betrachteten Abschnitt. Kurze Timinglücken dürfen intern für die Zeiterkennung überbrückt werden; Rohdaten bleiben unverändert. In Livekurve, Samples und SVG-Archiven verbindet eine schwarze Linie mit 90 % Deckkraft die benachbarten gemessenen Punkte. Diese Gerade ist eine Zeichenhilfe, keine rekonstruierte Messung. Kontaktlücken, längere Lücken und offene Enden bleiben unverbunden.

## Herzfrequenz und Herzschlagsamples

Die angezeigte Herzfrequenz ist eine **Schätzung der elektrischen Schlagfrequenz**, nicht zwingend des tastbaren Pulses. Der eigene, nicht klinisch validierte Detektor erkennt positive oder negative Spitzen und berechnet `60 / Median(der letzten bis zu vier Schlagabstände in Sekunden)`. Standardmäßig sind mindestens **zwei Sekunden verwertbares Signal** und **drei erkannte Spitzen** erforderlich. Bei langsamem Herzschlag kann die Wartezeit länger sein.

Der technische Auswertebereich ist **35–210 /min**. Ungeeignete Signale, Kontaktfehler, längere oder häufige Grenzwertüberschreitungen und unplausible Schlagabstände führen zur Anzeige **—**. Kurze Grenzwertüberschreitungen bis 80 ms werden innerhalb der Plausibilitätsgrenzen toleriert, ohne ihre Amplitude zu korrigieren. Netzwerkfehler und länger als drei Sekunden ausbleibende neue Werte blenden die Schätzung aus.

Der Trendpfeil vergleicht die jüngsten drei Schlagabstände mit der vorherigen Dreiergruppe. **↑ / ↓** erscheint bei einer Änderung um mehr als 2 /min oder 3 % (der größere Schwellwert gilt), sonst **→**. Ohne ausreichende Daten erscheint **—**.

**Herzschlagsamples** öffnet ein separates Fenster. Bis zu 100 Schläge werden an der erkannten Spitze ausgerichtet: **−250 bis +450 ms**, **701 Punkte im Abstand von 1 ms**, Spitze bei Index 250. Jeder Schlag erhält eine eigene Grundlinienkorrektur, aber keine Höhennormalisierung oder zeitliche Dehnung.

- Türkis gestrichelt: Einzelkurven
- Dunkel durchgezogen: Mittelwert
- Violett durchgezogen: punktweiser Median
- Band um den Mittelwert: ±1 Stichprobenstandardabweichung

Mittelwert und Median sind unabhängig schaltbar und anfangs aktiv. Alle gesammelten Samples tragen zur Statistik bei, einschließlich abgeschnittener Kurven. Fehlende Punkte bleiben leer und werden punktweise aus der Berechnung ausgelassen. Kontaktlücken verwerfen ein Sample; Timinglücken sind innerhalb der konfigurierten Grenzen erlaubt. Die Streuung beschreibt Kurvenformen, keine RR-basierte HRV-Auswertung.

**Glätten (Anzeige)** ist anfangs aus und verändert ausschließlich angezeigte Samplekopien. Der Bereich ±40 ms um die Spitze bleibt unverändert; Mittelwert, Median und Streuungsband beziehen sich bei aktiver Glättung auf die geglätteten Kopien. Die Rohdaten, Livekurve, Archive und BPM-Erkennung bleiben unverändert.

**Beispielkurve** blendet eine synthetische PQRST-Kurve mit illustrativen Abschnitten ein. **Zeitabschnitte an der Mittelkurve messen** bietet sechs geordnete Marken für P-, QRS- und T-Anfang/-Ende, per Ziehen oder Zahleneingabe mit 1-ms-Raster. Daraus entstehen P-Dauer, PR-Intervall, PR-Strecke, QRS-Dauer, ST-Strecke, T-Dauer und QT-Intervall. Die Marken werden manuell gesetzt; es gibt keine automatische Wellenklassifikation. Die Mittelkurve aktualisiert sich mit neuen Samples, daher müssen die Marken geprüft werden.

Die Sammlung läuft bei geschlossenem Fenster weiter. **Samples leeren** beginnt neu. Beim Neuladen der Seite gehen Samples und Messmarken verloren.

## Kurvenarchiv

Archivabschnitte umfassen **25, 50 oder 100 große Kästchen**, entsprechend nominal **5, 10 oder 20 Sekunden**. Längere Abschnitte erscheinen mit fünf Sekunden pro Zeile. Jeder Abschnitt übernimmt seine Anzeigeeinstellungen bei Beginn; Autozoom und Zentrierung werden beim Abschluss anhand seiner Werte berechnet. Die SVGs enthalten Raster, Spannungsskala und Browser-Uhrzeit.

**Abschnitt jetzt sichern** schließt einen kürzeren Teilabschnitt ab. Es bleiben höchstens **20 Grafiken** in der geöffneten Seite; danach wird die älteste entfernt. Abschnitte ohne mindestens 0,5 Sekunden zusammenhängenden sichtbaren Kurvenzug werden übersprungen. Kontaktlücken bleiben auch im Export offen.

Ein Klick auf eine Vorschau öffnet die Großansicht mit **100–400 % Zoom**, Einpassen, Scrollen und Verschieben. Jede Grafik lässt sich als SVG herunterladen.

**Das Archiv liegt nur im RAM der Browserseite. Beim Schließen oder Neuladen gehen die Grafiken verloren. Wichtige Abschnitte vorher herunterladen.** Der ESP32 zeichnet nicht im Flash auf. Bei geschlossener oder länger inaktiver Browserseite gibt es keine verlässliche fortlaufende Archivierung.

## Konfiguration und Erfassung

Die zentralen Einstellungen stehen in [`HeartMonitor/config.h`](HeartMonitor/config.h):

| Einstellung | Standard | Bedeutung |
|---|---|---|
| `SAMPLE_INTERVAL_US` | `1000` | Sollintervall 1000 µs, entsprechend 1000 Samples/s |
| `SAMPLE_COUNT` | automatisch `5000` | Fünf Sekunden Firmware-Ringpuffer |
| `SENSOR_PIN` | `4` | Analogeingang |
| `LEAD_OFF_MINUS_PIN` / `LEAD_OFF_PLUS_PIN` | `3` / `1` | Kontakteingänge |
| `ECG_GAIN` / `ECG_REFERENCE_MV` | `1100` / `1650` | Umrechnung der Spannungsanzeige |
| `HEART_MIN_SIGNAL_SECONDS` | `2` | Mindestdauer für die Herzfrequenzschätzung |
| `HEART_MIN_BEATS` | `3` | Mindestzahl erkannter Spitzen |
| `HEART_MAX_TIMING_GAP_MS` | `40` | Maximale tolerierte einzelne Timinglücke |
| `HEART_MAX_TIMING_GAP_PERCENT` | `10` | Maximaler Anteil fehlender Timingpunkte |
| `WIFI_TX_POWER` | `WIFI_POWER_8_5dBm` | Maximale WLAN-Sendeleistung |
| `AP_SSID` / `AP_PASSWORD` | `HeartMonitor` / `herzkurve123` | Hotspot-Zugang |

Ein periodischer ESP-Timer benachrichtigt eine eigene Messtask. Aufgelaufene Termine werden als fehlende Zeitschritte markiert; die Task misst einmal den aktuellen Wert und gibt regelmäßig Rechenzeit für Webserver und System frei. Der Browser hält 30 Sekunden Verlauf.

**Die Zeitachse verwendet das Sollintervall, keine individuellen ADC-Zeitstempel.** Die eingestellten 1000 Samples/s garantieren keine lückenlose Erfassung. Tatsächliche Messabstände und Ausfälle unter WLAN-Last müssen am Gerät geprüft werden. `/api/samples` enthält dafür `timing.missed`, `timing.minIntervalUs` und `timing.maxIntervalUs`.

## Schnittstellen

| Pfad | Inhalt |
|---|---|
| `/` | Vollständig lokale Weboberfläche |
| `/api/samples.bin?session=<Boot-ID>&after=<Sequenz>` | Inkrementelle Binärpakete für die Liveanzeige |
| `/api/samples` | JSON mit Werten, Kontaktstatus, Skalierung und Timingdiagnosen |

Die Webseite ruft nominal alle **100 ms** neue Werte ab; bei Rückstand folgen weitere Abrufe ohne zusätzliche Pause. Ein Paket enthält höchstens **128 Werte**. Sitzungskennung und Sequenznummern erkennen Neustarts, vermeiden Duplikate und markieren abgelaufene Cursor.

Das **HMS2-Format** verwendet Little Endian, einen 32-Byte-Header und zwei Byte pro Sample. Der Header enthält Magic, Sitzung, erste/nächste/neuste Sequenz, Sollintervall, Verstärkung, Referenz, Anzahl und Flags. Im Samplewort stehen der Ausgangswert in Bit 0–13 sowie LO−/LO+ in Bit 14/15. `0x3fff` ohne Kontaktbits kennzeichnet eine reine Timinglücke. Details stehen in [`HeartMonitor/sample_packet.h`](HeartMonitor/sample_packet.h).

MQTT und WLAN-Client-Betrieb sind nicht implementiert. Der Hotspot ist nicht mit dem Heimnetz verbunden.

## Tests

Die Tests verwenden simulierte Signale und ausschließlich synthetische Testdaten. Benötigt werden Node.js und ein C++-Compiler:

```sh
c++ -std=c++11 -Wall -Wextra -pedantic tests/sample_packet_test.cpp -o /tmp/heart-packet-test
/tmp/heart-packet-test /tmp/heart-packet-fixture.bin
node tests/browser_logic.cjs /tmp/heart-packet-fixture.bin
node tests/heart_analysis.cjs
```

Geprüft werden unter anderem Binärkodierung und Browserdekodierung, Ringpuffer und Cursor, Kontaktfreigabe, Timinglücken, Herzfrequenzschätzung, Statistik, Archivdarstellung und Einstellungswiederherstellung. Browserinteraktionen werden mit simulierten DOM-Elementen geprüft. Die Softwaretests ersetzen keinen Test im Zielbrowser, keinen Lasttest am ESP32 und keine elektrische Kalibrierung.

## Projektdateien und Quellen

- [`HeartMonitor/`](HeartMonitor/): Arduino-Sketch, Konfiguration, Paketformat und eingebettete Oberfläche
- [`tests/`](tests/): Protokoll-, Browserlogik- und Detektortests
- [`assets/`](assets/): Anschlusszeichnung und Elektrodenillustrationen
- [`assets/THIRD_PARTY.md`](assets/THIRD_PARTY.md): Herkunft und CC0-Lizenz der anatomischen Vorlage

Technische Grundlagen:

- [SparkFun AD8232 Hookup Guide](https://learn.sparkfun.com/tutorials/ad8232-heart-rate-monitor-hookup-guide)
- [SparkFun AD8232 Schaltplan](https://cdn.sparkfun.com/datasheets/Sensors/Biometric/AD8232_Heart_Rate_Monitor_v10.pdf)
- [AD8232-Datenblatt](https://www.analog.com/media/en/technical-documentation/data-sheets/AD8232.pdf)
- [Espressif Arduino ADC API](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/adc.html)

Die Quellen beschreiben Hardware und Grundlagen; der implementierte Detektor ist kein klinisch validiertes Referenzverfahren.
