#ifndef DISPLAY_H
#define DISPLAY_H

void clear_screen(void);

void print_system_stats(
    double cpu_usage_percent,
    double memory_usage_percent,
    const char *uptime_string);

#endif