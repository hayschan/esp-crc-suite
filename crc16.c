#include "crc16.h"
#include "crc_fast_reverse.h"

void CRC16_init(CRC16_t *crc, uint16_t polynome, uint16_t initial, uint16_t xorOut, bool reverseIn, bool reverseOut) {
    crc->polynome = polynome;
    crc->initial = initial;
    crc->xorOut = xorOut;
    crc->reverseIn = reverseIn;
    crc->reverseOut = reverseOut;
    CRC16_restart(crc);
}

void CRC16_reset(CRC16_t *crc, uint16_t polynome, uint16_t initial, uint16_t xorOut, bool reverseIn, bool reverseOut) {
    CRC16_init(crc, polynome, initial, xorOut, reverseIn, reverseOut);
}

void CRC16_restart(CRC16_t *crc) {
    crc->crc = crc->initial;
    crc->count = 0;
}

uint16_t CRC16_calc(const CRC16_t *crc) {
    uint16_t rv = crc->crc;
    if (crc->reverseOut) rv = reverse16bits(rv);
    rv ^= crc->xorOut;
    return rv;
}

crc_size_t CRC16_count(const CRC16_t *crc) {
    return crc->count;
}

static void CRC16_add_byte(CRC16_t *crc, uint8_t value) {
    if (crc->reverseIn) value = reverse8bits(value);
    crc->crc ^= ((uint16_t)value) << 8;
    for (uint8_t i = 8; i; i--) {
        if (crc->crc & (1UL << 15)) {
            crc->crc = (crc->crc << 1) ^ crc->polynome;
        } else {
            crc->crc <<= 1;
        }
    }
}

void CRC16_add(CRC16_t *crc, uint8_t value) {
    crc->count++;
    CRC16_add_byte(crc, value);
}

void CRC16_add_array(CRC16_t *crc, const uint8_t *array, crc_size_t length) {
    crc->count += length;
    while (length--) {
        CRC16_add_byte(crc, *array++);
    }
}

void CRC16_add_array_yield(CRC16_t *crc, const uint8_t *array, crc_size_t length, crc_size_t yieldPeriod) {
    crc->count += length;
    crc_size_t period = yieldPeriod;
    while (length--) {
        CRC16_add_byte(crc, *array++);
        if (--period == 0) {
            // ESP32 yield equivalent
            vTaskDelay(1);
            period = yieldPeriod;
        }
    }
}

uint16_t CRC16_getCRC(const CRC16_t *crc) {
    return CRC16_calc(crc);
}

uint16_t calcCRC16(const uint8_t *array, crc_size_t length,
                   uint16_t polynome, uint16_t initial, uint16_t xorOut,
                   bool reverseIn, bool reverseOut, crc_size_t yieldPeriod) {
    CRC16_t crc;
    CRC16_init(&crc, polynome, initial, xorOut, reverseIn, reverseOut);
    yieldPeriod == CRC_YIELD_DISABLED ?
        CRC16_add_array(&crc, array, length) :
        CRC16_add_array_yield(&crc, array, length, yieldPeriod);
    return CRC16_calc(&crc);
}
