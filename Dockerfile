FROM aflplusplus/aflplusplus:latest

ENV LANG en_US.utf8

# system packages
RUN apt update
RUN apt-get install -y apt-utils

# essential
RUN apt-get install -y curl
RUN apt-get install -y build-essential git openssh-server pkg-config manpages-dev systemd-coredump htop

# Install C/ C++ related dependencies
RUN apt-get install -y cmake gdb clang lldb lld
# Static and Dynamic anaylsis tools 
RUN apt-get install -y cppcheck
RUN apt-get install -y valgrind 

# Address sanitizers:
# https://www.usenix.org/system/files/conference/atc12/atc12-final39.pdf
# https://github.com/google/sanitizers/wiki/AddressSanitizer
# - Use after free (dangling pointer reference)
# - Heap buffer overflow
# - Stack buffer overflow
# - Use after return
# - Use after scope
# - Initialization order bugs

# Memory sanitizers:
# https://static.googleusercontent.com/media/research.google.com/en//pubs/archive/43308.pdf
# https://github.com/google/sanitizers/wiki/MemorySanitizer 
# It can track uninitialized bits in a bitfield. It will tolerate copying of uninitialized memory, 
# and also simple logic and arithmetic operations with it. In general, 
# MSan silently tracks the spread of uninitialized data in memory, and reports a warning when a code 
# branch is taken (or not taken) depending on an uninitialized value.

ENV AOC = /home/aoc2022/

COPY . $AOC
WORKDIR $AOC

RUN mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug -DUSE_MSAN=ON .. && make -j$(nproc) && cd ..
