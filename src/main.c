#include "uptime.h"
#include "memory.h"

#include <stdio.h>

int main(void)
{
    long uptime_seconds;
    char uptime_buffer[32];
    double memory_usage_percent;

    if (read_uptime_seconds(&uptime_seconds) != 0)
    {
        printf("Failed to read uptime\n");
        return 1;
    }

    if (read_memory_usage(&memory_usage_percent) != 0)
    {
        printf("Failed to read memory usage\n");
        return 1;
    }

    format_uptime(uptime_seconds, uptime_buffer, sizeof(uptime_buffer));

    printf("Linux System Monitor\n");
    printf("--------------------\n");
    printf("Uptime:        %s\n", uptime_buffer);
    printf("Memory Usage:  %.2f%%\n", memory_usage_percent);

    return 0;
}