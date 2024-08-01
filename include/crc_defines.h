#ifndef CRC_DEFINES_H
#define CRC_DEFINES_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Use size_t for ESP32, which is typically 32-bit
typedef size_t crc_size_t;

#define CRC_YIELD_DISABLED 0

#ifdef __cplusplus
}
#endif

#endif // CRC_DEFINES_H
