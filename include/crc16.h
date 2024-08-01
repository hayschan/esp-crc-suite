#ifndef CRC16_H
#define CRC16_H


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "crc_defines.h"
#include "crc_parameters.h"
#include "crc_fast_reverse.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint16_t polynome;
    uint16_t initial;
    uint16_t xorOut;
    bool reverseIn;
    bool reverseOut;
    uint16_t crc;
    crc_size_t count;
} CRC16_t;

void CRC16_init(CRC16_t *crc, uint16_t polynome, uint16_t initial, uint16_t xorOut, bool reverseIn, bool reverseOut);
void CRC16_reset(CRC16_t *crc, uint16_t polynome, uint16_t initial, uint16_t xorOut, bool reverseIn, bool reverseOut);
void CRC16_restart(CRC16_t *crc);
uint16_t CRC16_calc(const CRC16_t *crc);
crc_size_t CRC16_count(const CRC16_t *crc);
void CRC16_add(CRC16_t *crc, uint8_t value);
void CRC16_add_array(CRC16_t *crc, const uint8_t *array, crc_size_t length);
void CRC16_add_array_yield(CRC16_t *crc, const uint8_t *array, crc_size_t length, crc_size_t yieldPeriod);
uint16_t CRC16_getCRC(const CRC16_t *crc);

uint16_t calcCRC16(const uint8_t *array, crc_size_t length,
                   uint16_t polynome, uint16_t initial, uint16_t xorOut,
                   bool reverseIn, bool reverseOut, crc_size_t yieldPeriod);

#ifdef __cplusplus
}
#endif

#endif // CRC16_H
