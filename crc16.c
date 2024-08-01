#include "crc16.h"

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

size_t CRC16_count(const CRC16_t *crc) {
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

void CRC16_add_array(CRC16_t *crc, const uint8_t *array, size_t length) {
    crc->count += length;
    while (length--) {
        CRC16_add_byte(crc, *array++);
    }
}

uint16_t CRC16_getCRC(const CRC16_t *crc) {
    return CRC16_calc(crc);
}
