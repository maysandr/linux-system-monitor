#include "uptime.h"

#include <stdio.h>

int read_uptime_seconds(long *uptime_seconds) {
    FILE *file;
    double uptime;

    file = fopen("/proc/uptime", "r");
    if (!file) {
        return -1;
    }

    if (fscanf(file, "%lf", &uptime) != 1) {
        fclose(file);
        return -1;
    }

    fclose(file);

    *uptime_seconds = (long)uptime;
    return 0;
}

void format_uptime(long uptime_seconds, char *buffer, int buffer_size) {
    long hours;
    long minutes;
    long seconds;

    hours = uptime_seconds / 3600;
    minutes = (uptime_seconds % 3600) / 60;
    seconds = uptime_seconds % 60;

    snprintf(buffer, buffer_size, "%02ld:%02ld:%02ld", hours, minutes, seconds);
}