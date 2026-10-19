#pragma once
#include <stddef.h>
#include <stdint.h>

namespace SamplePacket {
constexpr size_t HEADER_BYTES = 32;
constexpr size_t MAX_VALUES = 128;
constexpr uint32_t MAGIC = 0x32534d48; // Bytes: HMS2
// Statusbit 0: LO-; Statusbit 1: LO+. In den oberen zwei Samplebits.
constexpr uint16_t VALUE_MASK = 0x3fff;
// Reservierter, physikalisch unmöglicher mV-Wert: ausgelassener Messzeitpunkt.
constexpr uint16_t MISSING_SAMPLE = VALUE_MASK;
inline uint16_t packSample(uint16_t millivolts, uint8_t leadStatus) {
  return (millivolts & VALUE_MASK) | ((leadStatus & 3) << 14);
}
// Aufrufer schützt den Ring vor parallelen Zugriffen.
inline void insertMissing(uint16_t* ring, size_t capacity, size_t& writeIndex,
                          size_t& available, uint32_t& total, uint32_t& session, uint32_t count) {
  if (!count) return;
  if (total > UINT32_MAX - count) { ++session;total=0;writeIndex=0;available=0; }
  const size_t fillCount=count < capacity ? count : capacity;
  for (size_t i=0;i<fillCount;++i) ring[(writeIndex+i)%capacity]=MISSING_SAMPLE;
  writeIndex=(writeIndex+count)%capacity;
  available=count >= capacity-available ? capacity : available+count;
  total+=count;
}
struct Range {
  uint32_t first;
  uint16_t count;
  bool reset;
};

inline bool parseUint32(const char* value, uint32_t& result) {
  if (!value || !*value) return false;
  uint32_t parsed = 0;
  for (; *value; ++value) {
    if (*value < '0' || *value > '9') return false;
    const uint32_t digit = *value - '0';
    if (parsed > (UINT32_MAX - digit) / 10) return false;
    parsed = parsed * 10 + digit;
  }
  result = parsed;
  return true;
}

inline Range selectRange(uint32_t total, size_t available, uint32_t after, bool sameSession) {
  const uint32_t oldest = total - available;
  const bool reset = !sameSession || after < oldest || after > total;
  const uint32_t first = reset ? (available > MAX_VALUES ? total - MAX_VALUES : oldest) : after;
  const uint32_t remaining = total - first;
  return {first, static_cast<uint16_t>(remaining > MAX_VALUES ? MAX_VALUES : remaining), reset};
}
inline void put16(uint8_t* out, uint16_t value) {
  out[0] = value & 0xff; out[1] = value >> 8;
}
inline void put32(uint8_t* out, uint32_t value) {
  put16(out, value & 0xffff); put16(out + 2, value >> 16);
}
inline size_t encode(uint8_t* out, uint32_t session, const Range& range, uint32_t total,
                     uint32_t interval, uint16_t gain, uint16_t reference,
                     const uint16_t* ring, size_t capacity, size_t writeIndex, size_t available, uint8_t currentLeadStatus = 0) {
  put32(out, MAGIC);
  put32(out + 4, session);
  put32(out + 8, range.first);
  put32(out + 12, range.first + range.count);
  put32(out + 16, total);
  put32(out + 20, interval);
  put16(out + 24, gain);
  put16(out + 26, reference);
  put16(out + 28, range.count);
  put16(out + 30, (range.reset ? 1 : 0) | ((currentLeadStatus & 3) << 1));
  const size_t oldestIndex = (writeIndex + capacity - available) % capacity;
  const size_t offset = range.first - (total - available);
  for (size_t i = 0; i < range.count; ++i) {
    put16(out + HEADER_BYTES + i * 2, ring[(oldestIndex + offset + i) % capacity]);
  }
  return HEADER_BYTES + range.count * 2;
}
}
