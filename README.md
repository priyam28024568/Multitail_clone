# tailclone

A lightweight, real-time log monitoring utility for POSIX-compliant systems written in C++. Inspired by `tail -f`, `tailclone` uses raw POSIX system calls to stream live updates appended to a file with minimal CPU overhead.

## Features

* **Event-Driven Monitoring:** Uses `poll()` with non-blocking file descriptors (`O_NONBLOCK`) to wait for incoming data without busy-waiting or wasting CPU cycles.
* **Live-Only Streaming:** Utilizes `lseek()` to jump directly to the end of the file upon startup, avoiding historical log clutter.
* **Unbuffered Output:** Streams new bytes directly to standard output (`STDOUT_FILENO`) using low-level `write()` calls.
* **Graceful Shutdown:** Intercepts `SIGINT` (`Ctrl + C`) to cleanly close open file descriptors and exit safely.

## Prerequisites

* **Operating System:** Linux, macOS, or BSD (requires POSIX headers such as `<unistd.h>`, `<fcntl.h>`, and `<poll.h>`).
* **Compiler:** A C++17-compatible compiler (`g++` or `clang++`).
* **Build Tool:** CMake (version 3.10 or higher).

## Building and Installation

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/YOUR_USERNAME/tailclone.git](https://github.com/priyam28024568/tailclone.git)
   cd tailclone

2. **Create a Build directory and compile**
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build . 
   ```
3. **Install system-wide(optional)**
   ```bash
   sudo cmake --install .
   ```
once installed 
**Usage**
```
tailclone filepath
```
**Uninstallation**
```
sudo rm /usr/local/bin/tailclone
```


   
   
