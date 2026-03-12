#include "uptime.h"
#include "memory.h"
#include "cpu.h"
#include "display.h"

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static volatile int running = 1;

static void handle_signal(int sig)
{
    (void)sig;
    running = 0;
}

int main(void)
{
    signal(SIGINT, handle_signal);

    while (running)
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

        clear_screen();
        print_system_stats(
            cpu_usage_percent,
            memory_usage_percent,
            uptime_buffer);

        sleep(1);
    }

    printf("\nMonitor stopped.\n");
    return 0;
}