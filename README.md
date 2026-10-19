# ESP32-C3 HeartMonitor

Lokaler WLAN-Hotspot mit EKG-Papieransicht, flüssiger Animation und Browserarchiv. Keine Cloud oder externen Webressourcen. Hardware: ESP32-C3 SuperMini, SparkFun AD8232 Heart Rate Monitor.

## Einrichtung

1. Arduino IDE 2: Boardpaket **esp32 by Espressif Systems** installieren.
2. `HeartMonitor/HeartMonitor.ino` öffnen; alle Header im selben Ordner belassen.
3. **ESP32C3 Dev Module**, **USB CDC On Boot: Enabled**, übliches SuperMini mit **4 MB Flash**, passenden USB-Port auswählen.
4. `config.h` prüfen: Sensor-OUTPUT an **GPIO 4**, gemeinsame GND-Verbindung. AD8232 mit **3,3 V** versorgen. Das Beispielbild mit einem großen ESP32-Board verwendet andere GPIOs; für dieses Projekt gilt GPIO 4.
5. Sketch hochladen. Bei Bedarf BOOT halten, RESET kurz drücken, BOOT loslassen und Upload erneut starten.
6. WLAN **HeartMonitor**, Passwort **herzkurve123**. Das Captive Portal bietet je nach Betriebssystem die Messseite automatisch an. Alternativ **http://192.168.4.1/** im normalen Browser öffnen. Die IP erscheint auch im seriellen Monitor bei 115200 Baud.

Bei angelegten Elektroden ausschließlich Batteriebetrieb ohne gleichzeitige USB-Verbindung zu Rechner, Ladegerät oder anderen netzbetriebenen Geräten. Der Aufbau ist kein medizinisch geprüftes Messgerät.

## Spannung in mV

Der ESP erfasst mit `analogReadMilliVolts()` kalibrierte Spannungswerte am ADC-Eingang. Die Dämpfung wird explizit auf `ADC_11db` eingestellt. Eine pauschale Rechnung `Rohwert * 3300 / 4095` wird nicht verwendet.

Über **Spannung** sind zwei Darstellungen wählbar:

- **EKG · mV (geschätzt)**: `(Modulausgang_mV − Referenz_mV) / Gesamtverstärkung`.
- **Modulausgang · mV**: die am ESP-Eingang erfasste Spannung direkt.

Für das vom Nutzer bestätigte SparkFun-Modul gilt nominell `100 * (1 + 1 MOhm / 100 kOhm) = 1100`. Die Referenz liegt bei halber Versorgung, nominell **1650 mV** bei 3,3 V. Beide Werte sind in `config.h` konfigurierbar. Die Gesamtverstärkung ist frequenzabhängig; besonders an den Filtergrenzen entspricht sie nicht exakt 1100. Das ist keine vollständige Rückrechnung des ungefilterten Elektrodensignals und keine medizinische Kalibrierung. Eine genauere Amplitudenmessung benötigt eine gemessene Referenz sowie eine Überprüfung der gesamten Übertragungsfunktion mit bekanntem Prüfsignal.

**ADC-Grenze:** Beim ESP32-C3 reicht der spezifizierte Messbereich mit dieser Dämpfung nur bis ungefähr **2500 mV**, nicht bis 3300 mV. Der AD8232-Ausgang kann darüber liegen. Die Anzeige meldet Werte an der Messgrenze; bereits abgeschnittene Signalanteile lassen sich softwareseitig nicht rekonstruieren. Die Erkennung anhand der mV-Werte ist nur ein Hinweis, keine garantierte Sättigungserkennung.

Das Raster entspricht nominal 0,04 s je kleinem und 0,20 s je großem Kästchen. In der manuellen EKG-Einstellung **0,1 mV/Kästchen** entspricht die Amplitudenaufteilung klassischem EKG-Papier bei 10 mm/mV; Bildschirmkästchen haben jedoch keine garantierte physische Millimetergröße. Die tatsächlich geltende Skala wird unter der Kurve und in jeder Archivgrafik angegeben.

Quellen:

- [SparkFun-Schaltplan AD8232 Heart Rate Monitor v10](https://cdn.sparkfun.com/datasheets/Sensors/Biometric/AD8232_Heart_Rate_Monitor_v10.pdf)
- [Analog Devices: Erklärung der SparkFun-Gesamtverstärkung](https://ez.analog.com/amplifiers/instrumentation-amplifiers/f/q-a/103051/some-questions-about-sparkfun-ad8232)
- [AD8232-Datenblatt](https://www.analog.com/media/en/technical-documentation/data-sheets/AD8232.pdf)
- [Espressif Arduino ADC API und Messbereiche](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/adc.html)

## Anzeige und Einstellungen

**Fließende Kurve** verschiebt das Signal gleichmäßig nach links. **Schreibstrahl links → rechts** baut eine Bildschirmseite auf und beginnt anschließend wieder links. Die Animation nutzt `requestAnimationFrame`, einen Zielpuffer von ca. 550 ms und eine geringe Geschwindigkeitskorrektur gegen WLAN-Jitter. Zwischen vorhandenen Punkten wird linear gezeichnet. Bei fehlenden zukünftigen Werten hält die Kurve an; größere Rückstände setzen die Anzeige auf aktuelle Werte zurück.

**Autozoom** und **Zentrieren** sind bei fehlendem Cookie standardmäßig eingeschaltet. Bereits gespeicherte Einstellungen haben Vorrang.

**Autozoom** passt die Höhe mit ungefähr 10 % Abstand je Rand an. **Zentrieren** passt die Mittellinie an die Mitte zwischen Minimum und Maximum des zurückliegenden sichtbaren Zeitfensters an. Beide Checkboxen arbeiten unabhängig im selben Animationszyklus. Bei aktiver Zentrierung ist die Bildschirmmitte keine feste elektrische Null. Ohne Zentrierung liegt sie im EKG-Modus bei nominell 0 mV, im Ausgangsmodus bei der Referenzspannung. Ohne Autozoom gilt die manuelle Höhe; eine Mindestspanne von 32 mV am Modulausgang verhindert übermäßige Verstärkung kleinster Schwankungen.

Ansicht, Spannungsdarstellung, Höhe, Autozoom, Zentrierung und Archivlänge werden für ein Jahr im lokalen Cookie `heartmonitor_settings` gespeichert. Ältere Cookies behalten kompatible Optionen; frühere ADC-Höhenwerte werden nicht als neue mV-Werte übernommen. Für verlässliche Cookies und Downloads dieselbe lokale IP im normalen Browser verwenden. Captive-Portal-Fenster können getrennte oder flüchtige Browserdaten besitzen.

## Kurvenarchiv

Abschnitte umfassen wahlweise 25, 50 oder 100 große Kästchen, nominal 5, 10 oder 20 Sekunden. SVG-Grafiken enthalten Raster, Skala, Spannungsart und Browser-Uhrzeit. Längere Aufnahmen werden mit fünf Sekunden pro Zeile dargestellt. Jeder Abschnitt übernimmt seine Anzeigeeinstellungen bei Beginn. Autozoom/Zentrierung werden beim Abschluss anhand aller enthaltenen Werte berechnet.

„Abschnitt jetzt sichern“ speichert einen kürzeren Teilabschnitt. Bei Änderung der Archivlänge wird der laufende Abschnitt abgeschlossen. Es bleiben höchstens 20 Bilder in dieser geöffneten Seite, danach wird das älteste entfernt. **Beim Schließen oder Neuladen gehen die Bilder verloren: wichtige Grafiken vorher herunterladen.** Es gibt keine Archivspeicherung im ESP-Flash und keine Aufzeichnung bei geschlossener oder länger inaktiver Seite. Pause hält nur die Live-Anzeige an; das Archiv läuft weiter.

Sequenznummern verhindern doppelte Werte aus überlappenden Messpaketen. Datenlücken schließen den vorhandenen Teilabschnitt ab, statt fehlende Werte durch eine Linie zu überbrücken. Nach einem ESP-Neustart Bilder herunterladen und Seite neu laden, da nicht jeder Neustart allein aus den Sequenznummern erkannt werden kann.

## Messung und spätere MQTT-Anbindung

Soll-Abtastrate 100 Hz, RAM-Puffer bis zu 500 Werte. Die Abtastung erfolgt kooperativ: HTTP und DNS können Messabstände verlängern. Die Zeitachse verwendet Soll-Abstände, keine tatsächlichen Einzelzeitstempel. Die Hauptkurve wird nicht digital gefiltert. Eine getrennte experimentelle Herzfrequenz-Erkennung arbeitet im Browser auf denselben Messwerten.

`GET /api/samples` liefert `intervalUs`, `total`, `gain`, `referenceMv`, `unit: "mV-output"` und chronologisch geordnete `values` in kalibrierten Ausgangs-mV. Zusätzlich enthalten `leadOff` pro Messwert und `leadStatus` für den aktuellen Stand eine Bitmaske (Bit 0 = LO−, Bit 1 = LO+). Bei Kontaktverlust wird der entsprechende `values`-Eintrag als `null` ausgegeben. Die ursprünglichen ADC-Rohzahlen werden nicht mehr übertragen. Die Weboberfläche speichert Messwerte intern ebenfalls in Ausgangs-mV und rechnet nur die Darstellung um.

`recordSample()` ist der zentrale Messpfad für eine spätere MQTT-Anbindung. Veröffentlichungen sollten außerhalb dieses Pfads zeitgesteuert erfolgen. Für einen Home-Assistant-Broker im Heimnetz wäre WLAN-Client-Betrieb (gegebenenfalls AP+STA) erforderlich; der reine Hotspot ist nicht mit dem Heimnetz verbunden.

## Prüfung

`node tests/browser_logic.cjs` prüft Spannungsumrechnung und Archivbeschriftung, alle Checkboxkombinationen, Cookie-Wiederherstellung und Migration, Animation, Datenlücken, Deduplizierung und Archivlimit mit simulierten Messwerten. Der tatsächliche Browser- und Hardwaretest sowie die elektrische Kalibrierung müssen am Zielaufbau erfolgen.

Firmware erfolgreich mit Arduino-ESP32 **3.3.12**, Ziel `esp32:esp32:esp32c3:CDCOnBoot=cdc`, kompiliert: 1.039.053 Byte Flash (79 %) und 39.192 Byte globale RAM-Nutzung (11 %). Kein Upload oder Hardwaretest durch den Agenten durchgeführt.


## Reduzierte WLAN-Sendeleistung

Die maximale WLAN-Sendeleistung wird nach dem Hotspot-Start über `WiFi.setTxPower()` auf **8,5 dBm** eingestellt (ca. 7 mW ausgestrahlte HF-Leistung, nicht der gesamte Stromverbrauch des Boards). In `config.h` lässt sich `WIFI_TX_POWER` ändern, etwa auf `WIFI_POWER_5dBm` für kurze Distanzen oder `WIFI_POWER_11dBm` für mehr Reichweite. Der Start versucht die Einstellung für maximal ca. 200 ms erneut, falls der AP noch nicht bereit ist. Der serielle Monitor meldet die gelesene Leistungsgrenze oder einen Fehler. Ob Temperatur und Stromverbrauch sinken, muss am Aufbau geprüft werden; die geringere Sendeleistung kann die Reichweite verringern.

Wird der AD8232 oder der Spannungsregler stark heiß, nicht von einer WLAN-Ursache ausgehen: Stromversorgung trennen und Versorgung/Anschlüsse prüfen. Die Änderung betrifft nur den ESP32-Funkteil.


## Optimierte Sample-Übertragung

Die Webseite verwendet `GET /api/samples.bin?session=<Boot-ID>&after=<nächste Sequenznummer>`. Ohne Cursor liefert der ESP höchstens die letzten 128 Werte. Danach werden nur neue Werte übertragen, gebündelt mit maximal 128 Werten pro Antwort. Normale Abrufe erfolgen etwa alle 200 ms zuzüglich Verarbeitungszeit; bei Rückständen folgen weitere Abrufe ohne zusätzliche Pause. JSON über `/api/samples` bleibt zur Kontrolle verfügbar und wird von der Live-Seite nicht mehr verwendet.

Binärformat HMS2: Little Endian, 32 Byte Header, danach zwei Byte pro Messwert (14 Bit kalibrierte Ausgangs-mV und zwei Kontaktstatusbits). Header: Magic bei Byte 0, Boot-ID 4, erste Sequenz 8, nächste Sequenz 12, neueste verfügbare Sequenz 16, Soll-Intervall in µs 20 (jeweils uint32); Verstärkung 24, Referenz-mV 26, Anzahl 28 und Flags 30 (jeweils uint16). Es gibt keine zusätzliche verlustbehaftete Reduktion oder gzip-Kompression.

Bei typischen 20 neuen Werten pro Abruf sind das **72 Byte Nutzdaten** gegenüber ungefähr **2,5 KB JSON** für 500 vierstellige Werte. Die Nutzdatenmenge sinkt rechnerisch um rund 97 %. HTTP/TCP/WLAN-Overhead ist darin nicht enthalten; der gesamte Funkverkehr wird deshalb nicht um denselben Prozentsatz reduziert. Weniger Daten und entfallene JSON-Erzeugung können Last reduzieren; konkrete Auswirkungen auf Verbrauch, Temperatur und Netzwerkqualität müssen gemessen werden.

Die Boot-ID erkennt ESP-Neustarts unabhängig vom Zählerstand. Ungültige oder abgelaufene Cursor erhalten einen markierten Neustartpunkt; die Anzeige und das Archiv beginnen einen getrennten Abschnitt. Während der Pufferdauer können verzögerte Abrufe in mehreren Paketen nachholen. Das Protokoll ändert weder Abtastrate noch die weiterhin nominale Zeitachse.

Protokollprüfung:

```sh
c++ -std=c++11 -Wall -Wextra -pedantic tests/sample_packet_test.cpp -o /tmp/heart-packet-test
/tmp/heart-packet-test /tmp/heart-packet-fixture.bin
node tests/browser_logic.cjs /tmp/heart-packet-fixture.bin
```

Die Tests prüfen native Binärpaketerzeugung und browserseitige Dekodierung gemeinsam, Cursorgrenzen, Ringpuffer-Umbruch, defekte Pakete, inkrementelle Übernahme, Neustarts und Datenlücken sowie die bestehende Anzeige- und Archivlogik.

Abschließender Build einschließlich Binärtransport und aktivierter Standard-Checkboxen erfolgreich: Arduino-ESP32 3.3.12, ESP32-C3 mit USB CDC; 1.043.341 Byte Flash (79 %) und 39.480 Byte globale RAM-Nutzung (12 %). Funkdurchsatz, Stromverbrauch und Temperatur wurden nicht am Gerät gemessen.


## Elektrodenstatus und aktuelle Verdrahtung

| AD8232 | ESP32-C3 SuperMini |
|---|---|
| 3.3V | 3V3 |
| GND | GND |
| OUTPUT | GPIO 4 (ADC1) |
| LO− | GPIO 3 (digitaler Eingang) |
| LO+ | GPIO 1 (digitaler Eingang) |
| SDN | Unverbunden; SparkFun-Modul mit vorhandenem Pull-up |

LO− und LO+ werden bei jeder Messung gelesen. HIGH meldet im DC-Leads-off-Betrieb des SparkFun-Moduls Kontaktverlust. Die Webseite zeigt beide Pegel einzeln und eine zusammengefasste Meldung. Das ist keine vollständige Kontaktqualitätsmessung und überwacht insbesondere nicht jeden möglichen Fehler der RL-Elektrode. Bei Netzwerkverlust wird die Kontaktanzeige als veraltet gekennzeichnet; bei pausierter Kurve läuft die Statusanzeige weiter.

Bei mindestens einem HIGH bleibt der Zeitschritt erhalten, die Kurve enthält aber eine Lücke. Autozoom ignoriert die ungültigen Werte. Archivgrafiken verbinden die gültigen Abschnitte nicht über diese Lücken hinweg und nennen deren Anzahl. Nach Rückkehr beider Leitungen auf LOW wird erst nach einer durchgehend fehlerfreien Sekunde wieder gezeichnet. Jeder gemeldete Fehler wird sofort angezeigt und startet diese Freigabezeit neu. Währenddessen bleiben Messwerte für Kurve, Archiv und Herzfrequenz ungültig. Die einzelnen LO-Pegel zeigen weiterhin die Rohzustände; beim Start erscheint zunächst „Kontakt wird geprüft …“. Die Freigabe ist keine Bestätigung aller drei Elektrodenkontakte.

Im HMS2-Samplewort stehen LO− in Bit 14 und LO+ in Bit 15; Bit 0–13 enthalten den Ausgangswert in mV. Der Header enthält zusätzlich den aktuellen Status (Flagbit 1 = LO−, Flagbit 2 = LO+, Flagbit 0 bleibt Reset). Somit wächst die Paketgröße trotz zweier Statusleitungen nicht. HMS1-Seiten sind nicht kompatibel; nach dem Upload die Webseite neu laden.

LO+ verwendet GPIO 1, damit die Statusleitung keinen Strapping-Pin beeinflusst.

Geprüft mit Simulationen: alle vier LO-Pegelkombinationen, HIGH/LOW-Anzeige und Rückkehr des Kontakts, unveränderte Spannungskodierung, Kontaktlücken in SVG und Autozoom bei ausschließlich ungültigen Werten. Elektrische Prüfung und Elektroden-Kontaktprüfung am Gerät stehen aus.


Archivabschnitte werden nur gespeichert, wenn mindestens 0,5 Sekunden eines zusammenhängenden Kurvenzuges innerhalb des tatsächlichen SVG-Ausschnitts liegen. Die Prüfung verwendet dieselbe Skala, Mittellinie und Zeileneinteilung wie der Export. Rein ungültige Werte, isolierte Punkte, nur über Zeilengrenzen benachbarte Punkte, kurze Kontaktblitzer und vollständig abgeschnittene Kurven werden verworfen – auch beim manuellen Sichern. Sie belegen keinen Archivplatz und erhöhen die Grafiknummer nicht; die Oberfläche zählt die übersprungenen Abschnitte. Teilweise gültige Abschnitte mit ausreichendem sichtbarem Kurvenzug sowie gültige flache Linien bleiben erhalten.


## Herzfrequenz, Trend und Schlagüberlagerung

Oben zeigt die Seite eine **geschätzte elektrische Herzfrequenz in /min**. Sie entspricht nicht zwingend dem tastbaren peripheren Puls. Aus den Abständen erkannter Spitzen wird `60 / Median(der letzten vier Abstände in Sekunden)` berechnet. Mindestens drei erkennbare Schläge (zwei Abstände) sind erforderlich. Anfangs verwendet die Schätzung zwei oder drei Abstände, später bis zu vier. Die Zeitbasis bleibt das Soll-Sampleintervall: unregelmäßige tatsächliche ADC-Abstände können deshalb auch den Herzfrequenzwert verfälschen.

Die Erkennung ist ein eigener, nicht klinisch validierter Algorithmus. Sie zieht einen lokalen Gleichspannungsanteil ab, glättet leicht und erkennt positive oder negative schmale Spitzen anhand einer adaptiven Schwelle. Kandidaten innerhalb 280 ms werden auf die stärkste Spitze reduziert. Kontaktlücken, länger als 80 ms zusammenhängende Werte außerhalb 20–2480 mV am ADC, mehr als 15 % übersteuerte Werte im Auswerteabschnitt, weniger als zwei Sekunden zusammenhängender Messung, zu kleine Signale oder zu uneinheitliche Abstände führen zur Anzeige **—**. Der technische Auswertebereich beträgt 35–210 /min; das sind keine Grenzen für einen medizinisch normalen Puls. Auch innerhalb dieses Bereichs sind Fehl- und Doppelerkennungen möglich, insbesondere bei Bewegungen oder starkem Rauschen. Die Hauptkurve bleibt unverändert.

Vor dem Wert steht der Trendpfeil:

- **↑ / ↓:** Der Median der letzten drei Abstände ergibt eine Herzfrequenz, die mehr als 2 /min beziehungsweise 3 % über/unter der vorherigen Dreiergruppe liegt (der größere Schwellwert gilt).
- **→:** Innerhalb dieser Schwelle ungefähr gleichbleibend.
- **—:** Noch keine sechs Abstände oder kein aktueller verwertbarer Wert.

Kontaktverlust und Netzwerkfehler blenden die Herzfrequenz aus. Wenn der Samplezähler länger als drei Sekunden unverändert bleibt, wird ein alter Wert ebenfalls ausgeblendet. Die Erkennung läuft unabhängig von Autozoom, Spannungsdarstellung und der Pause der Hauptkurve.

**Herzschläge überlagert:** Bis zu 100 zuletzt übernommene Schläge werden an der erkannten Spitze ausgerichtet, mit einem Zeitfenster von −0,25 bis +0,45 Sekunden. Alle verwenden dieselbe Zeit- und Amplitudenskala in geschätzten EKG-mV. Pro Schlag wird lediglich die Grundlinie aus dem vorderen Fenster abgezogen; es gibt keine individuelle Höhennormalisierung oder zeitliche Dehnung. Transparente Linien zeigen einzelne Schläge, die dunkle Linie deren arithmetischen Mittelwert. Nur vollständig verfügbare Fenster ohne Kontaktlücken werden übernommen, sobald die jüngste Schlagfolge die technischen Plausibilitätsprüfungen besteht. Das ist keine validierte Auswahl medizinisch normaler Herzschläge.

„Überlagerung leeren“ entfernt die bisherigen Schläge und übernimmt anschließend nur neue. Alte Überlagerungen bleiben bei Kontaktverlust als Historie sichtbar; ein ESP-Neustart löscht sie. Bei bloßer Übertragungslücke beginnt die Erkennung neu, während ältere Überlagerungen erhalten bleiben. Alle Daten liegen ausschließlich im RAM der Browserseite und gehen beim Neuladen verloren. Die Überlagerung wird separat von den unveränderten Archivabschnitten dargestellt.

Grundlagen: [PhysioNet zu RR-Abständen und Herzfrequenz](https://archive.physionet.org/tutorials/hrv/), [Analog Devices zu AD8232-Störungen und Filterung](https://www.analog.com/media/en/technical-documentation/data-sheets/AD8232.pdf). Diese Quellen beschreiben Grundlagen; der hier implementierte Detektor ist keine Übernahme eines validierten PhysioNet-Verfahrens.

Prüfung: `node tests/heart_analysis.cjs` testet künstliche EKG-ähnliche Signale mit 40, 60, 75, 120 und 180 /min in beiden Polaritäten, stabile/steigende/fallende Tendenz und die Ablehnung von Kontaktverlust, Übersteuerung, flachen Signalen und ausgewählter hochfrequenter Störung. Die vorhandenen Browserlogiktests prüfen zusätzlich Spitzenausrichtung, 100-Schlag-Limit, Deduplizierung, Veralten, Kontaktverlust und Rücksetzen. Die drei vom Nutzer bereitgestellten störungsbehafteten SVG-Abschnitte 108–110 wurden anhand der gerundeten Exportskala näherungsweise rekonstruiert; für alle drei unterdrückt die Erkennung einen Zahlenwert. Dies ist keine Validierung mit medizinischen Referenzdaten. Eine visuelle Browser-Vorschau war in dieser Umgebung nicht möglich; Hardware- und Darstellungstest stehen aus.

Firmware mit Herzfrequenz/Trend und Überlagerung erfolgreich für ESP32-C3 mit Arduino-ESP32 3.3.12 kompiliert: 1.055.453 Byte Flash (80 %), 39.488 Byte globale RAM-Nutzung (12 %). Die Auswertung läuft im Browser, der kompakte Sampletransport bleibt unverändert.

Kontaktmeldungen heißen nun eindeutig „Kontaktfehler gemeldet – Elektroden prüfen“ beziehungsweise „Keine Kontaktfehler gemeldet“. Neben der Anzeige steht, dass die RL-Elektrode nicht separat überwacht wird; beide LO-Ausgänge LOW sind keine Bestätigung für vollständigen Elektrodenkontakt.


## Hilfe zur Elektrodenplatzierung

Das Fragezeichen neben dem Elektrodenstatus öffnet eine lokale Hilfe als Dialog. Zwei SVG-Grafiken auf Basis einer frei verfügbaren anatomischen Vorlage zeigen Vorderansichten für die Platzierung an Armen/rechtem Bein oder an Brust/rechtem Unterbauch. **RA ist rot, LA gelb und RL grün**, entsprechend der vom Nutzer gewünschten Vorlage. Die dargestellte rechte Körperseite liegt links im Bild. Die Farbdarstellung ist keine universelle Kabelfarbzuordnung: Bei abweichenden Kabeln gelten die Beschriftungen RA/LA/RL. Die Platzierung orientiert sich an der [SparkFun-Anleitung](https://learn.sparkfun.com/tutorials/ad8232-heart-rate-monitor-hookup-guide). Die vollständige Hilfe inklusive Grafiken benötigt kein Internet.

Auf kleinen Displays werden die Varianten untereinander dargestellt. Der native Dialog kann per Schließen, Escape oder Klick außerhalb des Fensters beendet werden; der Fokus kehrt zum Hilfe-Knopf zurück. Messung, Auswertung und Archiv laufen weiter. Die barrierefreie Beschreibung enthält Hinweise zu EKG-Gelpads, Batteriebetrieb und der Bedeutung der Farbcodes; die Einschränkung der RL-Kontakterkennung steht weiterhin neben dem Kontaktstatus.

Editierbare Quellen: `assets/electrode-limbs.svg` und `assets/electrode-torso.svg`. Die Körperkontur ist einmal lokal in `web_page.h` eingebettet und wird von beiden Grafiken über SVG-Referenzen verwendet; die Browserlogiktests prüfen die Übereinstimmung und die drei gewünschten Farben. Die PNG-Vorschau `assets/electrode-placement-preview.png` ist nur für die Dokumentation, nicht Bestandteil der Firmware. Die SVGs wurden als PNG gerendert und visuell geprüft. Öffnen, Schließen, Hintergrundklick und Fokus-Rückgabe wurden mit simulierten DOM-Elementen geprüft; der Test im Zielbrowser steht aus.

Firmware einschließlich Elektroden-Hilfe erfolgreich für ESP32-C3 kompiliert: 1.066.853 Byte Flash (81 %), 39.488 Byte globale RAM-Nutzung (12 %).


Die Platzierungshilfe ist sichtbar sprachneutral: In beiden Grafiken stehen ausschließlich **RA**, **LA** und **RL** in Rot/Gelb/Grün. Weitere sichtbare Überschriften, Legenden und Beschreibungstexte im Hilfedialog fehlen; der Schließen-Knopf ist als × dargestellt. Nicht sichtbare Titel und Beschreibungen für Screenreader bleiben erhalten.

Die zuvor selbst gezeichnete Figur wurde durch die anatomische Vorderansicht aus [Human body with blank labels von Šlomo, Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Human_body_with_blank_labels.svg) ersetzt (CC0 1.0). Gesicht und ursprüngliche Pfadgeometrie bleiben erhalten; Rückansicht und Beschriftungslinien wurden entfernt, Darstellung und Elektrodenmarkierungen angepasst. Dies ist eine frei nutzbare anatomische Illustration, keine als ISO-Normfigur ausgewiesene Vorlage. Original und Quellenhinweise liegen in `assets/vendor/` und `assets/THIRD_PARTY.md`. Beide Varianten sowie die gemeinsam eingebettete Figur wurden gerendert und visuell geprüft.

Zusätzliche Browserlogiktests prüfen wiederholte kurze LOW-Impulse bei Kontaktfehlern, die Freigabe exakt nach einer Sekunde zusammenhängender gültiger Samples, die sofortige Fehlermeldung und ausbleibende Freigabe durch leere Pakete. Firmware einschließlich neuer Figur und Kontaktfreigabe erfolgreich für ESP32-C3 mit Arduino-ESP32 3.3.12 kompiliert: 1.138.893 Byte Flash (86 %), 39.488 Byte globale RAM-Nutzung (12 %). Hardwareprüfung steht aus.


## Kompakte Oberfläche

Die Livekurve nutzt die volle verfügbare Breite und eine an die Bildschirmhöhe angepasste Höhe. Herzfrequenz und Elektrodenstatus stehen kompakt darüber. GPIO 3 (LO−) heißt in der Oberfläche **Rot**, GPIO 1 (LO+) **Grün**, entsprechend der gewünschten Kabelbezeichnung; die Elektrodenplatzierungshilfe behält ihre RA/LA/RL-Farben. Auf schmalen Displays stehen die Statusbereiche untereinander.

Ansicht, Autozoom, Zentrieren und Pause bleiben direkt erreichbar. Spannung und manuelle Höhe liegen unter „Darstellung einstellen“. Die Schlagüberlagerung ist anfangs eingeklappt; sie sammelt weiter Schläge und zeichnet beim Öffnen neu. Das Archiv bleibt geöffnet und ordnet seine Karten abhängig vom Platz in Spalten an. Ausführliche Archiv- und Messhinweise sind aufklappbar. Die Kontaktfreigabe nach einer Sekunde und bestehende Cookie-Einstellungen bleiben erhalten.


Die Kontaktanzeige ergänzt **Gelb** als ausdrücklich **abgeleiteten** Status: Verbunden, sobald Rot oder Grün LOW meldet; nicht verbunden, wenn beide HIGH melden. Ohne Messung oder bei Verbindungsverlust wird kein Verbindungszustand für Gelb behauptet. Dies ergänzt keinen Messeingang, verändert weder die gemessenen LO-Bits noch die Kontaktfreigabe, Kurvenlücken oder Herzfrequenzanalyse und erlaubt keine Aussage über den tatsächlichen Kontakt einer dritten Elektrode.


## Fenster für Herzschlagsamples

Der Button „Herzschlagsamples“ neben Pause öffnet die bisherige Überlagerung als separates Dialogfenster. Die Messung und Sammlung laufen auch bei geschlossenem Fenster weiter. Bis zu 100 Schläge sind an der erkannten Spitze ausgerichtet (−0,25 bis +0,45 s), mit gemeinsamer Zeit- und Amplitudenskala und individuell abgezogener Grundlinie. Türkise Linien zeigen Einzelschläge, die dunkle Linie ihren Mittelwert. Das transparente Band zeigt an jedem Zeitpunkt ±1 Stichprobenstandardabweichung (Teiler n−1); bei einem Schlag ist die Streuung null. Die gemeinsame Skalierung berücksichtigt auch das Band. Dies beschreibt die Kurvenformstreuung, keine RR-basierte HRV-Auswertung und keine medizinische Klassifikation.

Schließen funktioniert über ×, Escape oder Hintergrundklick mit Fokus-Rückgabe. „Samples leeren“ beginnt die Sammlung neu. DOM-Simulationen prüfen Öffnen/Schließen/Fokus und Statistiktests den Mittelwert sowie die Standardabweichung für bekannte, einzelne und leere Datensätze. Der Test im Zielbrowser und am Gerät steht aus.

In der fließenden Ansicht laufen die senkrechten Rasterlinien synchron mit der Kurve nach links. Rasterphase und Signal verwenden denselben interpolierten Wiedergabecursor; Hauptlinien bleiben im Abstand von fünf kleinen Kästchen. Pause oder fehlende neue Daten halten beide an. Im Schreibstrahlmodus bleibt das Raster stationär.

Die Livekurve besitzt links eine mV-Achse mit zur tatsächlichen Skalierung passenden Zahlen. Autozoom, Zentrierung und Spannungsmodus werden berücksichtigt. „mV ≈“ bezeichnet geschätzte EKG-Spannungen; „mV“ die Modulausgangsspannung. Der Rand reserviert Platz für die Achse, die Rasterfläche bleibt rechts davon.

Die Anschlussanzeigen Rot, Grün und Gelb liegen in drei gleich breiten, festen Rasterspalten. Der Kontaktbereich erhält auf großen Bildschirmen eine feste Spaltenbreite und fällt auf kleinen Bildschirmen auf die volle Breite zurück. Wechselnde Statuslängen ändern dadurch weder die Position der Anzeigen noch die Breite des Herzfrequenzbereichs.


### Erkennung vor dem Kompilieren einstellen

In `HeartMonitor/config.h` legt `HEART_MIN_SIGNAL_SECONDS` die fehlerfreie Mindestdauer fest (Standard `2`, beispielsweise auf `1` änderbar). `HEART_MIN_BEATS` legt die Mindestzahl erkannter Spitzen fest (Standard `3`; zwei Abstände). Beide Bedingungen müssen erfüllt sein, deshalb kann es bei langsamem Herzschlag länger als die Mindestdauer dauern. Die Konfiguration wird beim Kompilieren direkt in das JavaScript eingebettet; anschließend Sketch hochladen und Webseite neu laden. Kurze Fenster liefern weniger stabile Schätzwerte. Kontaktfreigabe und Ablehnung übersteuerter Werte bleiben unverändert.


Die fließende Ansicht verwendet nun 550 ms Wiedergabepuffer zum Ausgleich kurzer WLAN-Verzögerungen. Die Zeichenroutine durchläuft nur den sichtbaren Kurvenabschnitt und schreibt unveränderte Beschriftungen nicht erneut ins DOM. Die Herzschlagerkennung verarbeitet höchstens die jüngsten zwanzig Sekunden, während der längere Verlauf erhalten bleibt. Die geschlossene Schlagüberlagerung sammelt weiter Samples, zeichnet aber nicht unnötig im Hintergrund; beim Öffnen wird sie aktualisiert. Dies reduziert Browserarbeit, ohne die gespeicherten Messwerte zu glätten. Die tatsächliche Flüssigkeit ist am Zielgerät zu prüfen.


## Kurze Übersteuerung bei der Schlagerkennung

Die Zeiterkennung toleriert zusammenhängende Grenzwertüberschreitungen bis 80 ms (bei 100 Hz acht Samples), sofern höchstens 15 % des zusammenhängenden Auswerteabschnitts außerhalb 20–2480 mV liegen. Längere Sättigung und Kontaktlücken starten die fehlerfreie Mindestdauer neu. Kurze Spitzen werden weder rekonstruiert noch in ihrer Amplitude geändert; der Detektor verwendet weiterhin die vorhandene Glättung und Plausibilitätsprüfung der Schlagabstände.

Vollständige Herzschlagsamples mit Grenzwertüberschreitungen werden nun ebenfalls gesammelt, als „abgeschnitten“ gezählt und orange gestrichelt gezeichnet. Sie tragen nicht zu Mittelwert oder Standardabweichung bei. Sind alle Samples abgeschnitten, bleiben Mittelwert und Streuungsband aus; die Einzelkurven werden trotzdem dargestellt.

Der Regressionstest `tests/fixtures/synthetic-75bpm.json` enthält ausschließlich synthetische Werte (75 BPM, 100 Hz, 30 Sekunden) mit kurzen Spitzen oberhalb der ADC-Messgrenze. Der Detektor liefert dafür 75 BPM und übernimmt markierte Samples. Die Tests prüfen das Softwareverhalten für diese Beispiele, keine medizinische Genauigkeit. Alle gesammelten Samples einschließlich abgeschnittener Kurven fließen in die Statistik ein.


## Glättung und Zeitraster der Herzschlagsamples

„Glätten (Anzeige)“ ist anfangs ausgeschaltet und wird mit den übrigen Einstellungen per Cookie gespeichert. Ein symmetrischer Fünf-Punkt-Filter mit Gewichten 1/4/6/4/1 dämpft schnelle Schwankungen ausschließlich in den angezeigten Samplekopien. Der Bereich ±40 ms um die erkannte Spitze bleibt unverändert; bis ±100 ms steigt die Filterwirkung sanft an. An den Rändern wird der jeweils äußerste Samplewert fortgesetzt. Dies ist eine Darstellungshilfe und kann die Kurvenform verändern. Rohsamples, Archive und BPM-Erkennung bleiben unverändert. Mittelwert und Streuungsband beziehen sich bei aktivierter Glättung auf die geglätteten Kopien; abgeschnittene Samples bleiben ausgeschlossen. Die vertikale Skalierung bleibt aus den ungeglätteten Daten berechnet, damit der Schalter keine zusätzliche Höhenskalierung auslöst.

Senkrechte Rasterlinien liegen alle 20 ms, kräftige Linien alle 100 ms, mit Null an der ausgerichteten Spitze. Die Zeitachse ist in Millisekunden beschriftet; auf schmalen Displays werden Zahlen alle 200 statt 100 ms gezeichnet. Tests prüfen Unterdrückung alternierenden Rauschens, konstante Werte, unveränderte Spitze und Rohdaten, Erhalt der Clipping-Markierung, Cookie-Wiederherstellung sowie Zeitbeschriftung.


## 250 Samples/s und unabhängige Erfassung

`Config::SAMPLE_INTERVAL_US` ist nun 4000 µs (250 Samples/s). Der Ringpuffer umfasst automatisch fünf Sekunden, derzeit 1250 Samplewörter. Ein periodischer ESP-Timer benachrichtigt eine eigene FreeRTOS-Messtask mit Priorität 3; ADC-Lesung und LO-Abfrage laufen unabhängig vom synchronen Webserver. Der Timer selbst liest keinen ADC. Ringzugriffe und Paket-Snapshots sind kurz gesperrt; HTTP-Übertragung, JSON-Aufbereitung und ADC-Aufruf liegen außerhalb der Sperre.

Versäumte Timertermine werden nicht durch künstliche Nachholmessungen ersetzt. Mehrere wartende Timertermine erzeugen ungültige Zeitschritte im vorhandenen Ringpuffer; die Messsitzung bleibt bestehen. Reiner Scheduling-Jitter setzt die Sitzung nicht zurück. Damit bleibt die nominelle Zeitachse erhalten, ohne nachträgliche Messwerte zu erfinden. `/api/samples` enthält unter `timing` die Zahl `missed` und minimale/maximale Task-Startabstände in µs. Dies sind Softwarediagnosen, kein Nachweis jitterfreier ADC-Abtastung. Gleichmäßigkeit bei realer WLAN-Last und elektrisches Verhalten müssen am Gerät geprüft werden.

Der Binärtransport bleibt HMS2 mit maximal 128 neuen Werten pro Paket; bei 200-ms-Abrufen entstehen nominal 50 Werte. Das Frontend hält weiterhin bis zu 30 Sekunden Verlauf. Herzschlagsamples verwenden jetzt 177 Punkte im Abstand von 4 ms (−252 bis +452 ms), mit der erkannten Spitze exakt auf Index 63. Die Grafik zeigt den bisherigen Ausschnitt −250 bis +450 ms; äußerste Punkte werden abgeschnitten. Mittelwert und Band benutzen dieselbe Zeitbasis. Der Glättungsfilter arbeitet nun zeitbezogen mit einem symmetrischen Gaußkern (10 ms Standardabweichung, Radius 20 ms); die Spitzenschutzzone ±40 ms und der Übergang bis ±100 ms bleiben erhalten.

Tests prüfen 250-Hz-Erkennung bei 40–180 BPM in beiden Polaritäten, 177-Punkt-Überlagerungen samt Mittelwert-Zeitbasis, Glättung, weiterhin eine Sekunde Kontaktfreigabe, 30 Sekunden Browserverlauf sowie das 1250-Werte-Ringformat.

## Schematische Beispielkurve

Im Samplefenster blendet „Beispielkurve“ eine blaugraue, synthetische PQRST-Kurve und illustrative Bereiche P / PR / QRS / ST / T ein. Die Höhe wird an die Ansicht angepasst. Die Abschnitte sind keine automatisch gemessenen Grenzen oder medizinischen Normbereiche; die Kurve wird nicht aus Messdaten rekonstruiert und geht nicht in die Statistik ein. Die Einstellung bleibt per Cookie erhalten. Die Bezeichnungen orientieren sich an [Clinical Methods: Electrocardiography](https://www.ncbi.nlm.nih.gov/books/NBK354/?report=printable).

Die dunkle durchgezogene Linie bleibt der Mittelwert ab mindestens einem nicht abgeschnittenen Sample. Orange gestrichelte Samples sind abgeschnitten und werden aus Mittelwert und Streuung ausgeschlossen. Sind alle Samples abgeschnitten, bleibt die dunkle Linie aus.


## Durchgehender Schreibstrahl bei verzögerter Erfassung

Die zuvor schon bei kurzem Task-Jitter ausgelösten Sitzungsneustarts entfallen. Ausgelassene Timertermine erhalten im HMS2-Samplewort den reservierten Wert `0x3fff` (16383 mV, kein tatsächlicher ADC-Wert). Die Webseite dekodiert ihn als ungültigen Zeitschritt: Kurve, Archiv und Schlagerkennung überbrücken diese Stelle nicht. LO-Bits und aktueller Elektrodenstatus werden dadurch nicht verändert. Eine bereits freigegebene Kontaktanzeige bleibt bei einer reinen Timinglücke bestehen; eine noch laufende Kontaktfreigabe verlangt weiterhin zusammenhängende gültige Samples. Archivtexte sprechen deshalb nun von „Messlücken“.

Im Schreibstrahlmodus wird bei mehr als zwei Sekunden Datenrückstand nicht mehr automatisch der Seitenanfang neu gesetzt. Die Animation arbeitet den Verlauf kontinuierlich ab, solange er im 30-Sekunden-Browserpuffer verfügbar ist. Echte Neustarts oder nicht mehr verfügbare Daten können weiterhin einen neuen Abschnitt erfordern. Native Tests prüfen Lücken im normalen/vollen Ring, unveränderte Sitzung und Sequenzüberlauf; Browsertests prüfen die Lückendekodierung ohne Kontaktfehler, unveränderten Seitenursprung bei Rückstand und den regulären Umbruch erst am rechten Rand. Nach dem Upload die Webseite neu laden, damit die neue Lückenmarkierung korrekt gelesen wird.


## Eine Sekunde Entprellzeit für Kontaktfehler

Ein gemeldeter LO-Fehler muss jetzt eine Sekunde durchgehend in den Messwerten anliegen, bevor er eine bereits freigegebene Live-Anzeige erneut sperrt. Kürzere HIGH-Impulse erzeugen nur an den betroffenen Messzeitpunkten Lücken; nach Rückkehr auf LOW wird sofort weitergezeichnet, ohne erneute Freigabewartezeit. Die einzelnen Rot/Grün-Anzeigen bleiben unveränderte Rohpegel. Die zusammengefasste Kontaktmeldung verwendet den bestätigten, entprellten Zustand.

Beim Start und nach einem bestätigten Fehler sind weiterhin eine Sekunde zusammenhängend fehlerfreie Werte erforderlich. Leere Pakete und Header-Pegel zählen nicht als Messzeit. Bei 250 Hz sind somit jeweils 250 Messungen nötig. Ungültige Werte werden nicht interpoliert oder als gültig archiviert; die BPM-Erkennung kann bei einer kurzen Lücke weiterhin vorübergehend aussetzen. Tests decken beide Wartezeiten bei 100 und 250 Hz, kurze Impulse, unmittelbare Weiterzeichnung und leere Pakete ab.


## Archiv-Großansicht und manuelle Zeitmessung

Ein Klick auf eine Archivvorschau öffnet dieselbe lokale SVG-Grafik in einem eigenen Dialog. Zoom ist über Slider oder ± von 100 bis 400 % verfügbar; „Einpassen“ stellt die Bildschirmbreite wieder her. Scrollen, Ziehen mit der Maus und Strg+Mausrad erlauben Navigation, auf Touchscreens lässt sich die Grafik scrollen. Schließen erfolgt per ×, Escape oder Hintergrundklick. Wird die angezeigte Grafik aus dem begrenzten Archiv entfernt, schließt sich die Ansicht vor Freigabe ihrer Blob-URL.

Im Samplefenster enthält „Zeitabschnitte an der Mittelkurve messen“ sechs manuell verschiebbare Marken: P-Anfang/P-Ende, QRS-Anfang/QRS-Ende und T-Anfang/T-Ende. Linien lassen sich mit Maus oder Finger ziehen; alternativ können Positionen numerisch in ms eingegeben werden. Die Marken bleiben zeitlich geordnet, mindestens 4 ms auseinander, und rasten auf 4 ms ein. Berechnet werden P-Dauer, PR-Intervall, PR-Strecke, QRS-Dauer, ST-Strecke, T-Dauer und QT-Intervall. Das sind ausschließlich Differenzen der vom Nutzer gesetzten Marken, keine automatische Wellenklassifikation oder diagnostische Bewertung. Die Startpositionen sind als Beispielpositionen gekennzeichnet.

Ohne nicht abgeschnittene Samples gibt es keine auswertbare Mittelkurve; dann sind die Marken gesperrt und keine Messzeiten ausgegeben. Die schematische Beispielkurve kann auch während der Zeitmessung eingeblendet bleiben; die Abschnittsflächen folgen den verschiebbaren Marken, während die Beispielkurve ihre ursprüngliche Form behält. Die Mittelkurve selbst wird weiterhin mit neuen Samples aktualisiert, daher müssen die Marken entsprechend geprüft werden. Markenpositionen bleiben nur im RAM dieser Browserseite. Tests prüfen Großansicht, Zoom, Ziehen, Fokus-Rückgabe und URL-Freigabe sowie Messformeln, Markengrenzen, Pointer-Ziehen und Sperre ohne Mittelwert. Der Test im echten Zielbrowser steht aus.


## Aktuell: 500 Samples/s, gemeinsame Sampledarstellung, Mittelwert und Median

Die Standardabtastrate beträgt jetzt **500 Samples/s** (`SAMPLE_INTERVAL_US = 2000`), der Firmware-Ring hält automatisch 2500 Werte für fünf Sekunden. Die unabhängige Messtask und die Markierung ausgelassener Timertermine bleiben bestehen. Ein nominales 200-ms-Paket enthält 100 Werte; größere Rückstände werden weiter in Paketen mit höchstens 128 Werten nachgeladen. Der Browser hält 30 Sekunden Verlauf. Tatsächlicher ADC-Jitter und Verhalten unter WLAN-Last müssen am Gerät überprüft werden.

Herzschlagsamples besitzen jetzt **351 Punkte im Abstand von 2 ms**, von −250 bis +450 ms; die Spitze liegt auf Index 125. Die Glättung bleibt zeitbezogen, und Messmarken rasten nun auf 2 ms. Alle Einzelkurven werden gleich türkis gestrichelt dargestellt, unabhängig von einer Grenzwertüberschreitung. Alle gesammelten Samples im Fenster (maximal die letzten 100) tragen zu Mittelwert, Standardabweichung und punktweisem Median bei – einschließlich abgeschnittener Kurven. Ungültige Messlücken erzeugen weiterhin keine vollständigen Samples; es findet keine Rekonstruktion statt.

„Mittelwert“ und „Median“ sind unabhängig schaltbar (dunkel beziehungsweise violett durchgezogen), anfangs beide aktiv und per Cookie gespeichert. Bei gerader Anzahl ist der Median der Mittelwert der zwei mittleren Werte. Bei aktiver Anzeige-Glättung beziehen sich beide Kurven auf die geglätteten Samplekopien; die Rohdaten bleiben erhalten. Das Streuungsband folgt dem Mittelwert-Schalter. Zeitmarken benötigen den eingeblendeten Mittelwert; Einschalten der Zeitmessung blendet ihn ein. Statistiken werden bis zum nächsten neuen Sample beziehungsweise einer Glättungsänderung zwischengespeichert, damit interaktive Messmarken keine wiederholten Medianberechnungen auslösen.

Die Tests umfassen 500-Hz-Streams, 2500-Werte-Ringpakete, 351-Punkt-Zeitbasis, eine Sekunde Kontaktfreigabe bei 500 Hz, BPM-Erkennung in beiden Polaritäten, Median bei gerader/ungerader Anzahl, Einbezug abgeschnittener Samples sowie Cookie-Wiederherstellung der unabhängigen Schalter. Die älteren Abschnitte dokumentieren frühere Entwicklungsstände; dieser Abschnitt beschreibt das aktuelle Samplefenster.


## Einzelne Timinglücken bei 500 Hz

Die Schlagerkennung erhält jetzt zusätzlich eine Kennzeichnung reiner Timinglücken (reserviertes Samplewort `0x3fff`, keine LO-Meldung). Isolierte, beidseitig von gültigen Werten begrenzte Timinglücken bis 8 ms dürfen ausschließlich in der internen Zeiterkennung linear überbrückt werden. Maximal 2 % der betrachteten Werte dürfen dabei ergänzt werden. Kontaktlücken, längere oder häufigere Ausfälle bleiben ungültig. Rohkurve und Archive werden nicht ergänzt; abgeschnittene Spitzen werden nicht rekonstruiert.

Ein Herzschlagsample wird nicht mehr wegen eines einzigen fehlenden Timingpunkts verworfen. Bis zu 2 % fehlende Punkte und höchstens 8 ms zusammenhängende Timinglücke sind erlaubt; die Punkte bleiben `null` und werden als echte Lücken gezeichnet. Kontaktlücken verwerfen weiterhin das Sample. Mittelwert, Median und Standardabweichung verwenden an jedem Zeitpunkt nur tatsächlich vorhandene Werte; auch die Anzeige-Glättung füllt diese Lücken nicht auf.

Regressionstests simulieren 30 Sekunden bei 500 Hz mit einem einzelnen fehlenden Timingpunkt pro Sekunde. Die Erkennung liefert weiterhin 60 BPM und sammelt über 25 Schläge mit sichtbaren Lücken. Zusätzliche Tests prüfen den Ausschluss von Kontaktlücken, längeren und häufigen Ausfällen sowie unveränderte Rohdaten und Statistik ohne Nullwert-Verfälschung. Die tatsächliche Fehlerursache im Nutzergerät muss bei Bedarf mit einer neuen Aufnahme oder den Timingdiagnosen überprüft werden.


### Einstellbare Toleranz für Timinglücken

Die aktuelle Toleranz wurde auf **40 ms am Stück und höchstens 10 % fehlende Punkte** angehoben. In `config.h` sind `HEART_MAX_TIMING_GAP_MS` und `HEART_MAX_TIMING_GAP_PERCENT` vor dem Kompilieren anpassbar. Bei 500 Hz entsprechen 40 ms zwanzig Punkten, bei 100 Hz vier Punkten. Beide Grenzen gelten sowohl für die interne BPM-Zeiterkennung als auch für die Annahme eines Herzschlagsamples. Fehlende Punkte bleiben im dargestellten Sample leer und werden nicht als Null in Mittelwert oder Median gezählt. Kontaktlücken werden weiterhin nicht überbrückt. Tests simulieren wiederholte 40-ms-Ausfälle bei 500 Hz und prüfen weiterhin 60 BPM sowie erfolgreiche Sample-Sammlung; längere oder zu häufige Lücken bleiben ausgeschlossen.


## Aktuell: 1.000 Samples/s

Die Sollrate beträgt jetzt **1.000 Samples/s** (`SAMPLE_INTERVAL_US = 1000`), der Ringpuffer weiterhin fünf Sekunden mit nun 5000 Werten. Die HTTP-Abrufpause wurde auf 100 ms verkürzt: nominal entstehen 100 neue Werte pro Abruf, bei Rückstand folgen unverändert sofort weitere Pakete mit maximal 128 Werten. Der Verlauf bleibt 30 Sekunden lang.

Herzschlagsamples besitzen jetzt **701 Punkte mit 1 ms Abstand**, von −250 bis +450 ms; die Spitze liegt auf Index 250. Messmarken rasten auf 1 ms ein. Die Glättung verwendet weiterhin dieselben Zeitparameter. 40 ms erlaubte Timinglücke entsprechen jetzt 40 fehlenden Rohpunkten; der maximale Lückenanteil bleibt konfigurierbar. Beim Anzeigen älterer/niedriger aufgelöster Daten berücksichtigt die Lückentoleranz zusätzlich den Rand einer linearen Resampling-Stützstelle; fehlende Werte selbst bleiben leer.

Native Tests prüfen das 5000-Werte-Ringformat und 1000-µs-Paketintervall. Browsertests prüfen 1000-Hz-Streams einschließlich wiederholter 40-ms-Timinglücken, erfolgreiche BPM-/Sample-Sammlung, 701-Punkt-Zeitbasis, Spitze und Kontaktfreigabe. Synthetische Detektortests umfassen 40–180 BPM bei 1000 Hz in beiden Polaritäten. Diese Prüfungen ersetzen keinen Lasttest am ESP: tatsächliche Erfassungsrate, ADC-Jitter und verlorene Timertermine müssen bei der höheren Sollrate über `timing` unter `/api/samples` am Gerät geprüft werden.


## Wiederherstellung nach leerer Anzeige bei 1.000 Hz

Die Standardrate wurde vorerst auf die am Nutzergerät zuvor funktionierenden **500 Hz** zurückgesetzt (fünf Sekunden / 2500 Werte, 200-ms-HTTP-Pause, 351 Punkte je Herzschlagsample). 1.000 Hz sind mit diesem Aufbau noch nicht als stabil bestätigt.

Ein konkreter Startfehler wurde korrigiert: Kurze ausdrücklich markierte Timinglücken setzen die bisher gesammelten LOW-Messungen der anfänglichen Kontaktfreigabe nicht mehr zurück. Sie zählen nicht als gültige Messzeit; erst nach insgesamt einer Sekunde tatsächlich gültiger LOW-Samples wird freigegeben. Lücken über der konfigurierten Toleranz und echte Kontaktfehler unterbrechen die Freigabe weiterhin. So können regelmäßig einzelne ausgelassene Timertermine die Anzeige nicht dauerhaft im Prüfzustand festhalten.

Zusätzlich blockiert die Messtask spätestens nach 16 Messungen für einen FreeRTOS-Tick. Damit erhalten Webserver und Idle-Task auch dann Rechenzeit, wenn wegen Rückstau ständig Timerbenachrichtigungen warten. Ein Test am Gerät bleibt erforderlich. Ein Regressionstest mit einem fehlenden Timingpunkt alle 50 Messungen zeigt nun die erfolgreiche Startfreigabe; längere Lücken bleiben ausgeschlossen.

Die einzelnen Anschlussanzeigen verwenden jetzt „Rot: verbunden/nicht verbunden“ und „Grün: verbunden/nicht verbunden“ statt LOW/HIGH. Sie geben weiterhin unmittelbar die jeweiligen LO-Pegel wieder (LOW → verbunden, HIGH → nicht verbunden); die zusammengefasste Meldung bleibt entprellt.


Nach ausdrücklichem Nutzerwunsch ist die Standardrate erneut auf **1.000 Samples/s** gesetzt. Die Korrektur der Startfreigabe bei kurzen Timinglücken und das regelmäßige Task-Yield bleiben aktiv. Übertragung wieder mit 100-ms-Abrufpause, Samplefenster mit 701 Punkten und Messmarken mit 1-ms-Raster. Die Anschlussbezeichnungen sind verbunden/nicht verbunden. Hardware-Stabilität nach diesem erneuten Versuch muss am Gerät geprüft werden.


## Optische Verbindungen über kurze Timinglücken

Kurze, ausdrücklich markierte Timinglücken werden in Livekurve, Herzschlagsamples und neu erzeugten SVG-Archiven mit **90 % Schwarz** verbunden. Die Verbindung ist eine gerade Linie zwischen den benachbarten gemessenen Punkten und keine rekonstruierte Messung. Die bestehende maximale Timinglänge aus `config.h` begrenzt diese Verbindungen. Kontaktlücken, längere Lücken und offene Enden werden nicht verbunden. In Samples bleiben die Verbindungsteile wie die Einzelkurve gestrichelt, bei Mittelwert/Median durchgezogen.

Rohwerte, Statistik und Detektor werden durch diese reine Zeichenänderung nicht verändert. Archive behalten ihre Timing-Maske, und die Sichtbarkeitsprüfung berücksichtigt dieselben eingezeichneten Verbindungen. SVG-Verbindungen tragen `data-timing-gap="true"` und `stroke-opacity="0.9"`. Ältere Archive enthalten diese zusätzliche Darstellungsmarkierung nicht.
