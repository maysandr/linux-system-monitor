#include "uptime.h"

#include <stdio.h>

int main(void) {
    long uptime_seconds;
    char uptime_buffer[32];

    if (read_uptime_seconds(&uptime_seconds) != 0) {
        printf("Failed to read uptime\n");
        return 1;
    }

    format_uptime(uptime_seconds, uptime_buffer, sizeof(uptime_buffer));

    printf("System Uptime: %s\n", uptime_buffer);

    return 0;
}