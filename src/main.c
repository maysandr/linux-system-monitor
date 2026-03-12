#include "uptime.h"
#include "memory.h"
#include "cpu.h"

#include <stdio.h>

int main(void)
{
    long uptime_seconds;
    char uptime_buffer[32];

    double memory_usage_percent;
    double cpu_usage_percent;

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

    if (read_cpu_usage(&cpu_usage_percent) != 0)
    {
        printf("Failed to read CPU usage\n");
        return 1;
    }

    format_uptime(uptime_seconds, uptime_buffer, sizeof(uptime_buffer));

    printf("Linux System Monitor\n");
    printf("--------------------\n");
    printf("CPU Usage:     %.2f%%\n", cpu_usage_percent);
    printf("Memory Usage:  %.2f%%\n", memory_usage_percent);
    printf("Uptime:        %s\n", uptime_buffer);

    return 0;
}