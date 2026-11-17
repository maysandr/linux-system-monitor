# Linux System Monitor

A lightweight terminal monitor written in **C** that reads Linux kernel-provided statistics from `/proc` to display CPU usage, memory usage, and system uptime. The application separates metric collection, formatting, and terminal display into small source modules.

## What it does

- **CPU usage:** samples the aggregate `cpu` counters in `/proc/stat` twice, about 100 ms apart, and calculates the share of sampled time that was not idle.
- **Memory usage:** reads `MemTotal` and `MemAvailable` from `/proc/meminfo` to estimate memory utilization.
- **Uptime:** reads `/proc/uptime` and formats elapsed time as hours, minutes, and seconds.
- **Live terminal view:** refreshes its output approximately once per second and exits on `Ctrl+C`.

## Example output

Illustrative values (actual readings depend on your system):

```text
Linux System Monitor
--------------------
CPU Usage:     12.35%
Memory Usage:  44.72%
Uptime:        38:14:09

Press Ctrl+C to exit.
```

## Build and run

**Requirements:** Linux or a Linux environment such as WSL, plus GCC. The program depends on the Linux `/proc` filesystem; running it with a Windows-native executable is not supported.

From the repository root, run:

```bash
gcc -std=gnu11 -O2 -Wall -Wextra -Iinclude src/*.c -o monitor
./monitor
```

Press `Ctrl+C` to stop. In WSL, metrics describe the Linux environment and may not match Windows-wide system metrics.

## Source organization

```text
include/       Function declarations
src/main.c     Main refresh loop and shutdown handling
src/cpu.c      CPU counters and usage calculation
src/memory.c   Memory statistics from /proc/meminfo
src/uptime.c   Uptime reading and formatting
src/display.c  Terminal output and screen clearing
```

## How the CPU reading works

`/proc/stat` provides cumulative CPU time counters. A single snapshot cannot tell us recent utilization, so the program takes two samples and compares their differences:

```text
usage (%) = 100 × (total_delta − idle_delta) / total_delta
```

For this small implementation, `total` is calculated from the first four aggregate fields (user, nice, system, idle). This is a simplified estimate, not a full accounting of every Linux CPU time category.

## Design choices and limitations

- Uses Linux's `/proc` pseudo-filesystem rather than external monitoring utilities.
- Reads and presents system-wide metrics, not per-process statistics.
- Uses ANSI escape sequences to redraw the terminal; your terminal must support them.
- CPU utilization is estimated from short sampling intervals and may fluctuate.
- Error handling checks whether kernel files can be opened and parsed, but this is a learning-scale tool rather than a production monitoring agent.

## Possible extensions

Per-core CPU statistics, a configurable refresh interval, structured metric output, and automated parser tests.
