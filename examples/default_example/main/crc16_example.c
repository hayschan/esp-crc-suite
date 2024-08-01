#include <stdio.h>
#include "crc16.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void) {
    CRC16_t crc;

    // Initialize for CRC-16/MODBUS
    CRC16_init(&crc, CRC16_POLYNOME, CRC16_INITIAL, CRC16_XOR_OUT, CRC16_REV_IN, CRC16_REV_OUT);

    uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
    CRC16_add_array(&crc, data, sizeof(data));

    uint16_t result = CRC16_getCRC(&crc);
    printf("CRC-16 result: 0x%04X\n", result);

    // Using the calcCRC16 function
    result = calcCRC16(data, sizeof(data), CRC16_POLYNOME, CRC16_INITIAL, CRC16_XOR_OUT, CRC16_REV_IN, CRC16_REV_OUT, CRC_YIELD_DISABLED);
    printf("CRC-16 result (using calcCRC16): 0x%04X\n", result);
}
