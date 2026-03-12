#include "cpu.h"

#include <stdio.h>
#include <unistd.h>

static int read_cpu_times(
    long long *user,
    long long *nice,
    long long *system,
    long long *idle)
{
    FILE *file;

    file = fopen("/proc/stat", "r");
    if (!file)
    {
        return -1;
    }

    if (fscanf(file, "cpu %lld %lld %lld %lld",
               user, nice, system, idle) != 4)
    {
        fclose(file);
        return -1;
    }

    fclose(file);
    return 0;
}

int read_cpu_usage(double *cpu_usage_percent)
{
    long long user1, nice1, system1, idle1;
    long long user2, nice2, system2, idle2;

    if (read_cpu_times(&user1, &nice1, &system1, &idle1) != 0)
    {
        return -1;
    }

    usleep(100000); // 100 ms

    if (read_cpu_times(&user2, &nice2, &system2, &idle2) != 0)
    {
        return -1;
    }

    long long idle_delta = idle2 - idle1;

    long long total1 = user1 + nice1 + system1 + idle1;
    long long total2 = user2 + nice2 + system2 + idle2;

    long long total_delta = total2 - total1;

    if (total_delta == 0)
    {
        return -1;
    }

    *cpu_usage_percent =
        ((double)(total_delta - idle_delta) / (double)total_delta) * 100.0;

    return 0;
}