#include "flash_ops.h"
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/flash.h"
#include "hardware/sync.h"

#define FLASH_TARGET_OFFSET (256 * 1024) // Offset where user data starts (256KB into flash)
#define FLASH_SIZE PICO_FLASH_SIZE_BYTES // Total flash size available

// Function: flash_write_safe
// Writes data to flash memory at a specified offset, ensuring safety checks.
//
// Parameters:
// - offset: The offset from FLASH_TARGET_OFFSET where data is to be written.
// - data: Pointer to the data to be written.
// - data_len: Length of the data to be written.
//
// Note: This function erases the flash sector before writing new data.
// This function safely writes raw data to the flash memory at a specified offset.
void flash_write_safe(uint32_t offset, const uint8_t *data, size_t data_len) {
    // Calculate the absolute address in flash by adding the offset to the base safe region.
    uint32_t flash_offset = FLASH_TARGET_OFFSET + offset;

    // Check if the write operation would exceed the allocated flash memory region.
    if (flash_offset + data_len > FLASH_TARGET_OFFSET + FLASH_SIZE) {
        printf("\nError: Write operation exceeds flash memory limit.\n");
        return;
    }

    // Disable interrupts before performing the flash operation to avoid conflicts.
    uint32_t ints = save_and_disable_interrupts();

    // Erase the flash sector to ensure it is ready for new data.
    flash_range_erase(flash_offset, FLASH_SECTOR_SIZE);

    // Write the specified data to flash memory.
    flash_range_program(flash_offset, data, data_len);

    // Re-enable interrupts after the operation is complete.
    restore_interrupts(ints);

    // Print a success message.
    printf("\nData written successfully.\n");
}

// This function safely reads raw data from the flash memory at a specified offset.
void flash_read_safe(uint32_t offset, uint8_t *buffer, size_t buffer_len) {
    // Calculate the absolute address in flash based on the given offset.
    uint32_t flash_offset = FLASH_TARGET_OFFSET + offset;

    // Check if the read operation would go beyond the flash memory bounds.
    if (flash_offset + buffer_len > FLASH_TARGET_OFFSET + FLASH_SIZE) {
        printf("\nError: Read operation exceeds flash memory limit.\n");
        return;
    }

    // Copy data from flash memory into the provided buffer.
    memcpy(buffer, (void *)(XIP_BASE + flash_offset), buffer_len);

    // Print a success message.
    printf("\nData read successfully.\n");
}


void flash_erase_safe(uint32_t offset) {
    uint32_t flash_offset = FLASH_TARGET_OFFSET + offset;

    // Ensure that the erase operation stays within valid memory boundaries.
    if (flash_offset >= FLASH_TARGET_OFFSET + FLASH_SIZE) {
        printf("\nError: Erase operation out of bounds.\n");
        return;
    }

    // Disable interrupts to prevent conflicts during the erase operation.
    uint32_t ints = save_and_disable_interrupts();

    // Erase the flash sector at the specified address.
    flash_range_erase(flash_offset, FLASH_SECTOR_SIZE);

    // Re-enable interrupts after completing the erase operation.
    restore_interrupts(ints);

    // Print a success message
    printf("\nFlash sector erased successfully at address %u.\n", offset);
}