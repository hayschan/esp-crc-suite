#ifndef CRC_PARAMETERS_H
#define CRC_PARAMETERS_H

#include "crc_defines.h"

#ifdef __cplusplus
extern "C" {
#endif

// CRC16 parameters (example for MODBUS)
#define CRC16_POLYNOME 0xA001
#define CRC16_INITIAL 0xFFFF
#define CRC16_XOR_OUT 0x0000
#define CRC16_REV_IN true
#define CRC16_REV_OUT true

// Add other CRC parameters as needed (CRC8, CRC32, etc.)

#ifdef __cplusplus
}
#endif

#endif // CRC_PARAMETERS_H
