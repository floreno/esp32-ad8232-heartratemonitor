#pragma once
#include <WiFi.h>

// Browser heartbeat detection: adjust before compiling.
// Minimum duration without contact gaps or prolonged clipping, in seconds (e.g. 1 or 2).
#define HEART_MIN_SIGNAL_SECONDS 2
// Minimum detected peaks; 3 beats provide 2 beat intervals.
#define HEART_MIN_BEATS 3
// Tolerance for timing gaps only, excluding electrode contact faults.
#define HEART_MAX_TIMING_GAP_MS 40
#define HEART_MAX_TIMING_GAP_PERCENT 10
static_assert(HEART_MAX_TIMING_GAP_MS >= 0 && HEART_MAX_TIMING_GAP_MS <= 100, "Timing gap: 0 to 100 ms");
static_assert(HEART_MAX_TIMING_GAP_PERCENT >= 0 && HEART_MAX_TIMING_GAP_PERCENT <= 25, "Gap fraction: 0 to 25 percent");
static_assert(HEART_MIN_SIGNAL_SECONDS >= 0.5 && HEART_MIN_SIGNAL_SECONDS <= 10, "HEART_MIN_SIGNAL_SECONDS: 0.5 to 10 seconds");
static_assert(HEART_MIN_BEATS >= 2 && HEART_MIN_BEATS <= 10, "HEART_MIN_BEATS: 2 to 10");

namespace Config {
constexpr char AP_SSID[] = "HeartMonitor";
// Reduced maximum transmit power: 8.5 dBm (approximately 7 mW RF power).
// For shorter distances consider WIFI_POWER_5dBm; for more range: WIFI_POWER_11dBm.
constexpr wifi_power_t WIFI_TX_POWER = WIFI_POWER_8_5dBm;
constexpr char AP_PASSWORD[] = "herzkurve123"; // At least 8 characters
// Check your specific board's pinout before connecting.
constexpr unsigned char SENSOR_PIN = 4;
constexpr unsigned char LEAD_OFF_MINUS_PIN = 3;
constexpr unsigned char LEAD_OFF_PLUS_PIN = 1;
constexpr unsigned long SAMPLE_INTERVAL_US = 1000; // 1000 Hz target sampling rate
// SparkFun AD8232: 100 * (1 + 1 MOhm / 100 kOhm), nominal.
constexpr unsigned int ECG_GAIN = 1100;
// REFOUT is nominally supply / 2. Measure and adjust for greater accuracy.
constexpr unsigned int ECG_REFERENCE_MV = 1650;
constexpr unsigned int SAMPLE_COUNT = 5UL * 1000000UL / SAMPLE_INTERVAL_US; // Five seconds
}
