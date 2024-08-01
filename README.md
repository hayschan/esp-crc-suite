# ESP CRC Suite

This project is an ESP component for performing CRC (Cyclic Redundancy Check) calculations in the ESP-IDF (Espressif IoT Development Framework). It includes implementations for various CRC16 algorithms with customizable parameters.

## Features

- CRC16 calculation with customizable parameters
- Support for reverse input and output
- Efficient CRC calculations with fast byte reversal
- Integration with ESP32's FreeRTOS for yielding during long calculations

## Installation

To include this component in your ESP-IDF project, follow these steps:

1. Clone the repository into the `components` directory of your ESP-IDF project:
    ```sh
    git clone https://github.com/hayschan/esp-crc-suite.git components/esp-crc-suite
    ```

2. Add the component to your project's `CMakeLists.txt`:
    ```cmake
    set(EXTRA_COMPONENT_DIRS components/esp-crc-suite)
    ```

3. Include the component's header files in your source code as needed:
    ```c
    #include "crc16.h"
    ```

## Usage

### Initialization

Initialize a CRC16 instance with desired parameters:
```c
#include "crc16.h"

CRC16_t crc;

CRC16_init(&crc, CRC16_POLYNOME, CRC16_INITIAL, CRC16_XOR_OUT, CRC16_REV_IN, CRC16_REV_OUT);
```

### Adding Data

You can add data to the CRC calculation using single bytes or arrays:
```c
uint8_t data = 0xAB;
CRC16_add(&crc, data);

uint8_t array[] = {0x01, 0x02, 0x03};
CRC16_add_array(&crc, array, sizeof(array));
```

For large arrays, you can use the yield function to prevent blocking:
```c
CRC16_add_array_yield(&crc, array, sizeof(array), 100);
```

### Getting the CRC Value

After adding data, retrieve the calculated CRC value:
```c
uint16_t crc_value = CRC16_getCRC(&crc);
```

### Example

Here is an example of how to use the component to calculate the CRC16 of an array:
```c
#include "crc16.h"

void app_main() {
    CRC16_t crc;
    CRC16_init(&crc, CRC16_POLYNOME, CRC16_INITIAL, CRC16_XOR_OUT, CRC16_REV_IN, CRC16_REV_OUT);
    
    uint8_t array[] = {0x01, 0x02, 0x03, 0x04};
    CRC16_add_array(&crc, array, sizeof(array));
    
    uint16_t crc_value = CRC16_getCRC(&crc);
    printf("CRC16 Value: 0x%04X\n", crc_value);
}
```

### Example Project

An example project demonstrating the use of the CRC component is included in the repository under `examples/default_example`. The example shows how to calculate CRC16 values using both the instance-based approach and the direct function call.

Example project file: `examples/default_example/main/crc16_example.c`

```c
#include <stdio.h>
#include "crc16.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// CRC16 parameters (example values for CRC-16/MODBUS algorithm)
#define CRC16_POLYNOME 0x8005
#define CRC16_INITIAL 0xFFFF
#define CRC16_XOR_OUT 0x0000
#define CRC16_REV_IN true
#define CRC16_REV_OUT true

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
```

## Project Structure

```
ESP-CRC-Suite
│   .editorconfig
│   .gitignore
│   CMakeLists.txt
│   crc16.c
│   crc_fast_reverse.c
│   Kconfig
│   LICENSE
│   README.md
│
├── .github
│   └── workflows
│       └── build_example.yml
│
├── docs
│   └── README.md
│
├── examples
│   ├── CMakeLists.txt
│   └── default_example
│       ├── .gitignore
│       ├── CMakeLists.txt
│       ├── README.md
│       ├── sdkconfig
│       └── main
│           ├── CMakeLists.txt
│           └── crc16_example.c
│
├── include
│   ├── crc16.h
│   ├── crc_defines.h
│   ├── crc_fast_reverse.h
│   ├── crc_parameters.h
│   └── README.md
│
└── tools
    └── precompute_crc_tables_crc16.py
```

## API Reference

### `crc16.h`

- `void CRC16_init(CRC16_t *crc, uint16_t polynome, uint16_t initial, uint16_t xorOut, bool reverseIn, bool reverseOut);`
  Initializes a CRC16 instance with the specified parameters.

- `void CRC16_reset(CRC16_t *crc, uint16_t polynome, uint16_t initial, uint16_t xorOut, bool reverseIn, bool reverseOut);`
  Resets a CRC16 instance with the specified parameters.

- `void CRC16_restart(CRC16_t *crc);`
  Restarts the CRC calculation with the initial value.

- `uint16_t CRC16_calc(const CRC16_t *crc);`
  Calculates and returns the current CRC value.

- `crc_size_t CRC16_count(const CRC16_t *crc);`
  Returns the number of bytes processed.

- `void CRC16_add(CRC16_t *crc, uint8_t value);`
  Adds a single byte to the CRC calculation.

- `void CRC16_add_array(CRC16_t *crc, const uint8_t *array, crc_size_t length);`
  Adds an array of bytes to the CRC calculation.

- `void CRC16_add_array_yield(CRC16_t *crc, const uint8_t *array, crc_size_t length, crc_size_t yieldPeriod);`
  Adds an array of bytes to the CRC calculation, yielding periodically to avoid blocking.

- `uint16_t CRC16_getCRC(const CRC16_t *crc);`
  Returns the current CRC value.

- `uint16_t calcCRC16(const uint8_t *array, crc_size_t length, uint16_t polynome, uint16_t initial, uint16_t xorOut, bool reverseIn, bool reverseOut, crc_size_t yieldPeriod);`
  Calculates the CRC16 of an array with the specified parameters.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributions

Contributions are welcome! Feel free to open issues or submit pull requests to improve the project.
