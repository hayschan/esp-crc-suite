#include "crc_suite.h"
#include "crc_tables_crc16.h"

uint16_t calculate_crc16_modbus(const uint8_t *data, size_t length) {
    uint16_t crc = 0xFFFF;  // Initial value for MODBUS
    for (size_t i = 0; i < length; ++i) {
        uint8_t index = (crc ^ data[i]) & 0xFF;
        crc = (crc >> 8) ^ crc16_modbus_table[index];
    }
    return crc;
}
