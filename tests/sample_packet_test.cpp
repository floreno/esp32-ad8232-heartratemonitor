#include "../HeartMonitor/sample_packet.h"
#include <assert.h>
#include <stdio.h>
#include <initializer_list>

int main(int argc, char** argv) {
  using namespace SamplePacket;
  uint32_t parsed = 0;
  assert(parseUint32("0", parsed) && parsed == 0);
  assert(parseUint32("4294967295", parsed) && parsed == UINT32_MAX);
  for (const char* invalid : {"", "-1", "1x", "4294967296", " 12", "+1"})
    assert(!parseUint32(invalid, parsed));
  for (uint8_t status = 0; status < 4; ++status) {
    const uint16_t word = packSample(1650, status);
    assert((word & VALUE_MASK) == 1650 && (word >> 14) == status);
  }
  auto r = selectRange(1500, 500, 0, false);
  assert(r.reset && r.first == 1372 && r.count == 128);
  r = selectRange(1500, 500, 1000, true);
  assert(!r.reset && r.first == 1000 && r.count == 128);
  r = selectRange(1500, 500, 999, true);
  assert(r.reset && r.first == 1372);
  r = selectRange(1500, 500, 1501, true);
  assert(r.reset);
  r = selectRange(1500, 500, 1500, true);
  assert(!r.reset && r.count == 0);
  r = selectRange(0, 0, 0, false);
  assert(r.reset && r.first == 0 && r.count == 0);
  uint8_t bytes[HEADER_BYTES + MAX_VALUES * 2] = {};
  const uint16_t wrapped[] = {105, 106, 107, 103, 104};
  r = selectRange(8, 5, 5, true);
  assert(encode(bytes, 1, r, 8, 10000, 1100, 1650, wrapped, 5, 3, 5) == 38);
  assert(bytes[32] == 105 && bytes[34] == 106 && bytes[36] == 107);
  encode(bytes, 1, r, 8, 10000, 1100, 1650, wrapped, 5, 3, 5, 3);
  assert(bytes[30] == 6);
  uint16_t gapRing[5]={100,101,102,0,0};size_t gapWrite=3,gapAvailable=3;
  uint32_t gapTotal=3,gapSession=9;
  insertMissing(gapRing,5,gapWrite,gapAvailable,gapTotal,gapSession,2);
  assert(gapWrite==0 && gapAvailable==5 && gapTotal==5 && gapSession==9);
  assert(gapRing[3]==MISSING_SAMPLE && gapRing[4]==MISSING_SAMPLE);
  r=selectRange(5,5,3,true);
  encode(bytes,gapSession,r,gapTotal,4000,1100,1650,gapRing,5,gapWrite,gapAvailable);
  assert(bytes[32]==0xff && bytes[33]==0x3f && bytes[30]==0);
  insertMissing(gapRing,5,gapWrite,gapAvailable,gapTotal,gapSession,7);
  assert(gapWrite==2 && gapAvailable==5 && gapTotal==12 && gapSession==9);
  for (const auto word:gapRing) assert(word==MISSING_SAMPLE);
  gapTotal=UINT32_MAX-1;
  insertMissing(gapRing,5,gapWrite,gapAvailable,gapTotal,gapSession,3);
  assert(gapTotal==3 && gapSession==10 && gapWrite==3 && gapAvailable==3);
  puts("PASS: missing-time slots preserve session, wrapped/full ring and sequence overflow");
  uint16_t highRateRing[1250];
  for (size_t seq=0;seq<2500;++seq) highRateRing[seq%1250]=seq;
  r=selectRange(2500,1250,2450,true);
  assert(r.count==50 && !r.reset);
  assert(encode(bytes,2,r,2500,4000,1100,1650,highRateRing,1250,0,1250)==132);
  assert(bytes[20]==0xa0 && bytes[21]==0x0f);
  assert((bytes[32] | bytes[33]<<8)==2450);
  assert((bytes[130] | bytes[131]<<8)==2499);
  puts("PASS: 250 Hz packet, 1250-value wrapped ring and 50-value polling batch");
  uint16_t rate500Ring[2500];
  for(size_t seq=0;seq<5000;++seq) rate500Ring[seq%2500]=seq;
  r=selectRange(5000,2500,4900,true);
  assert(r.count==100 && !r.reset);
  assert(encode(bytes,3,r,5000,2000,1100,1650,rate500Ring,2500,0,2500)==232);
  assert(bytes[20]==0xd0 && bytes[21]==0x07);
  assert((bytes[32] | bytes[33]<<8)==4900);
  assert((bytes[230] | bytes[231]<<8)==4999);
  puts("PASS: 500 Hz packet, 2500-value wrapped ring and 100-value polling batch");
  uint16_t rate1000Ring[5000];
  for(size_t seq=0;seq<10000;++seq) rate1000Ring[seq%5000]=seq;
  r=selectRange(10000,5000,9900,true);
  assert(r.count==100 && !r.reset);
  assert(encode(bytes,4,r,10000,1000,1100,1650,rate1000Ring,5000,0,5000)==232);
  assert(bytes[20]==0xe8 && bytes[21]==0x03);
  assert((bytes[32] | bytes[33]<<8)==9900);
  assert((bytes[230] | bytes[231]<<8)==9999);
  puts("PASS: 1000 Hz packet, 5000-value wrapped ring and 100-value polling batch");
  uint16_t ring[500];
  for (size_t i = 0; i < 500; ++i) ring[i] = 1000 + i;
  r = selectRange(1500, 500, 1490, true);
  const size_t length = encode(bytes, 0x12345678, r, 1500, 10000, 1100, 1650, ring, 500, 0, 500);
  assert(length == 52 && bytes[0] == 'H' && bytes[3] == '2');
  if (argc > 1) {
    FILE* out = fopen(argv[1], "wb"); assert(out);
    assert(fwrite(bytes, 1, length, out) == length); fclose(out);
  }
  puts("PASS: cursor validation, initial/backlog/expired/future/empty ranges, ring wrap, binary encoding");
}
