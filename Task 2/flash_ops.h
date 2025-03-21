#ifndef FLASH_OPS_H
#define FLASH_OPS_H

#include <stdint.h>
#include <stddef.h>

// Define structured flash storage format
typedef struct __attribute__((packed)){
    uint32_t write_count; // Number of times the sector has been written
    size_t data_len;      // Length of stored data
    uint8_t data[256];    // Fixed-size buffer for stored data
} flash_data_t;

void flash_write_safe(uint32_t offset, const uint8_t *data, size_t data_len);
void flash_read_safe(uint32_t offset, flash_data_t *out_data, int suppress_output);
void flash_erase_safe(uint32_t offset);

#endif // FLASH_OPS_H
