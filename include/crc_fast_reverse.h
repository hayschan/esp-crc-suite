#ifndef CRC_FAST_REVERSE_H
#define CRC_FAST_REVERSE_H

#include "crc_defines.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t reverse8bits(uint8_t in);
uint16_t reverse16bits(uint16_t in);
uint16_t reverse12bits(uint16_t in);
uint32_t reverse32bits(uint32_t in);
uint64_t reverse64bits(uint64_t in);

#ifdef __cplusplus
}
#endif

#endif // CRC_FAST_REVERSE_H
