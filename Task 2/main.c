#include <stdio.h>
#include "pico/stdlib.h"
#include "cli.h"
#include "custom_fgets.h"

int main() {
    stdio_init_all();
    char command[256];

    // Wait for USB connection
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }

    printf("Pico Flash Storage CLI\n");
    printf("Available commands:\n");
    printf("  FLASH_WRITE <offset> \"data\"\n");
    printf("  FLASH_READ <offset>\n");
    printf("  FLASH_ERASE <offset>\n");

    // Command loop
    while (1) {
        printf("\nEnter command: ");
        custom_fgets(command, sizeof(command), stdin);
        execute_command(command);
    }

    return 0;
}
