#include "display.h"

#include <stdio.h>

void clear_screen(void)
{
    printf("\033[2J\033[H");
}

void print_system_stats(
    double cpu_usage_percent,
    double memory_usage_percent,
    const char *uptime_string)
{
    printf("Linux System Monitor\n");
    printf("--------------------\n");
    printf("CPU Usage:     %.2f%%\n", cpu_usage_percent);
    printf("Memory Usage:  %.2f%%\n", memory_usage_percent);
    printf("Uptime:        %s\n", uptime_string);
    printf("\nPress Ctrl+C to exit.\n");
}