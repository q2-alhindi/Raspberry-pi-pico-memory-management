#include "flash_ops.h"
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/flash.h"
#include "hardware/sync.h"

#define FLASH_TARGET_OFFSET (256 * 1024) // The starting address for user data storage in flash memory (256 KB offset)
#define FLASH_SIZE PICO_FLASH_SIZE_BYTES // The total available flash memory size


void flash_write_safe(uint32_t offset, const uint8_t *data, size_t data_len) {
    uint32_t flash_offset = FLASH_TARGET_OFFSET + offset;

    // Ensure that the write operation does not exceed the allocated flash memory space.
    if (flash_offset + sizeof(flash_data_t) > FLASH_TARGET_OFFSET + FLASH_SIZE) {
        printf("Error: Write operation exceeds flash memory limit.\n");
        return;
    }

    // Read existing flash data to retrieve the previous write count.
    // Suppress output to avoid unnecessary console logs.
    flash_data_t existing_data;
    flash_read_safe(offset, &existing_data, 1);

    // Prepare a new flash data structure to store the updated information.
    flash_data_t new_data;
    new_data.write_count = existing_data.write_count + 1; // Increment the write count.
    new_data.data_len = data_len;

    // Clear the data buffer before writing to prevent leftover data issues.
    memset(new_data.data, 0, sizeof(new_data.data));
    memcpy(new_data.data, data, data_len); // Copy the input data into the structure.

    // Disable interrupts to prevent conflicts during the flash write operation.
    uint32_t ints = save_and_disable_interrupts();

    // Erase the sector before writing to ensure that new data is properly stored.
    flash_range_erase(flash_offset, FLASH_SECTOR_SIZE);

    // Write the updated data, including the write count, to the flash memory.
    flash_range_program(flash_offset, (const uint8_t *)&new_data, sizeof(flash_data_t));

    // Re-enable interrupts after completing the flash operation.
    restore_interrupts(ints);

    // Print a confirmation message indicating successful data storage.
    printf("\nData written successfully to address %u\n", offset);
}

void flash_read_safe(uint32_t offset, flash_data_t *out_data, int suppress_output) {
    uint32_t flash_offset = FLASH_TARGET_OFFSET + offset;

    // Ensure the read operation does not go beyond the available flash memory space.
    if (flash_offset + sizeof(flash_data_t) > FLASH_TARGET_OFFSET + FLASH_SIZE) {
        if (!suppress_output) {
            printf("Error: Read operation exceeds flash memory limit.\n");
        }
        return;
    }

    // Clear the output buffer to avoid displaying junk data from memory.
    memset(out_data, 0, sizeof(flash_data_t));

    // Copy data from flash memory into the provided structure.
    memcpy(out_data, (void *)(XIP_BASE + flash_offset), sizeof(flash_data_t));

    // Check if the flash memory at this location is uninitialized (all bytes are 0xFF).
    uint8_t *byte_ptr = (uint8_t *)out_data;
    int is_empty = 1;
    for (size_t i = 0; i < sizeof(flash_data_t); i++) {
        if (byte_ptr[i] != 0xFF) {  // If any byte is different from 0xFF, memory is initialized.
            is_empty = 0;
            break;
        }
    }

    // If flash memory is empty, reset the structure to avoid returning corrupted data.
    if (is_empty) {
        memset(out_data, 0, sizeof(flash_data_t));
        if (!suppress_output) {
            printf("\nFlash sector is empty. No data available.\n");
        }
        return;
    }

    // Ensure that the stored data is properly null-terminated to prevent reading past its limits.
    out_data->data[sizeof(out_data->data) - 1] = '\0';

    // Print the retrieved data only if suppress_output is set to 0.
    if (!suppress_output) {
        printf("\nRead Data: %s\n", out_data->data);
        printf("Write Count: %u\n", out_data->write_count);
    }
}

void flash_erase_safe(uint32_t offset) {
    uint32_t flash_offset = FLASH_TARGET_OFFSET + offset;

    // Ensure that the erase operation stays within valid memory boundaries.
    if (flash_offset >= FLASH_TARGET_OFFSET + FLASH_SIZE) {
        printf("Error: Erase operation out of bounds.\n");
        return;
    }

    // Disable interrupts to prevent conflicts during the erase operation.
    uint32_t ints = save_and_disable_interrupts();

    // Erase the flash sector at the specified address.
    flash_range_erase(flash_offset, FLASH_SECTOR_SIZE);

    // Re-enable interrupts after completing the erase operation.
    restore_interrupts(ints);

    // Print a confirmation message indicating that the sector was successfully erased.
    printf("\nFlash sector erased successfully at address %u.\n", offset);
}
