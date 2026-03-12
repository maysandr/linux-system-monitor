#ifndef UPTIME_H
#define UPTIME_H

int read_uptime_seconds(long *uptime_seconds);
void format_uptime(long uptime_seconds, char *buffer, int buffer_size);

#endif