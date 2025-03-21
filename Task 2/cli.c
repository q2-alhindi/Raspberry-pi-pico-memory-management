#include "cli.h"
#include "flash_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "custom_fgets.h"

// Each command expects specific arguments following the command name.
void execute_command(char *command) {
    // Split the command string into tokens
    char *token = strtok(command, " ");

    // Check for an empty or invalid command
    if (token == NULL) {
        printf("\nInvalid command\n");
        return;
    }

    // Handle the FLASH_WRITE command
    if (strcmp(token, "FLASH_WRITE") == 0) {
        // Parse the address
        token = strtok(NULL, " ");
        if (token == NULL) {
            printf("\nFLASH_WRITE requires an address and data\n");
            return;
        }
        uint32_t address = atoi(token);

        // Parse the data, assuming it's enclosed in quotes
        token = strtok(NULL, "\"");
        if (token == NULL) {
            printf("\nInvalid data format for FLASH_WRITE\n");
            return;
        }

        // Execute the write operation (structured data)
        flash_write_safe(address, (uint8_t *)token, strlen(token) + 1);
    }
    // Handle the FLASH_READ command
    else if (strcmp(token, "FLASH_READ") == 0) {
        // Parse the address
        token = strtok(NULL, " ");
        if (token == NULL) {
            printf("\nFLASH_READ requires an address\n");
            return;
        }
        uint32_t address = atoi(token);

        // Prepare a structure to store the read data
        int suppress_output = 0;  // Default to 0 
        flash_data_t read_data;
        flash_read_safe(address, &read_data, suppress_output);
    }
    // Handle the FLASH_ERASE command
    else if (strcmp(token, "FLASH_ERASE") == 0) {
        // Parse the address
        token = strtok(NULL, " ");
        if (token == NULL) {
            printf("\nFLASH_ERASE requires an address\n");
            return;
        }
        uint32_t address = atoi(token);

        // Execute the erase operation
        flash_erase_safe(address);
    }
    // Handle unknown commands
    else {
        printf("\nUnknown command: %s\n", token);
    }
}
