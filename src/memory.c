#include "memory.h"

#include <stdio.h>
#include <string.h>

int read_memory_usage(double *memory_usage_percent)
{
    FILE *file;
    char key[64];
    long value;
    char unit[32];

    long mem_total = 0;
    long mem_available = 0;

    file = fopen("/proc/meminfo", "r");
    if (!file)
    {
        return -1;
    }

    while (fscanf(file, "%63s %ld %31s", key, &value, unit) == 3)
    {
        if (strcmp(key, "MemTotal:") == 0)
        {
            mem_total = value;
        }
        else if (strcmp(key, "MemAvailable:") == 0)
        {
            mem_available = value;
        }

        if (mem_total > 0 && mem_available > 0)
        {
            break;
        }
    }

    fclose(file);

    if (mem_total == 0)
    {
        return -1;
    }

    *memory_usage_percent =
        ((double)(mem_total - mem_available) / (double)mem_total) * 100.0;

    return 0;
}