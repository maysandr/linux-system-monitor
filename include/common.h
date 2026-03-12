#ifndef COMMON_H
#define COMMON_H

#define MAX_LINE_LEN 256

typedef struct
{
    double cpu_usage_percent;
    double memory_usage_percent;
    long uptime_seconds;
} SystemStats;

#endif