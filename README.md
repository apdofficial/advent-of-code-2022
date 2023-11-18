# Advent of Code 2022 in C++20

[https://adventofcode.com/2022](https://adventofcode.com/2022)
 
### External dependencies
- [fmt](https://github.com/fmtlib/fmt) 
- [Catch2](https://github.com/catchorg/Catch2)

###  Usage

1.  The repository contains a Docker file using which you can build a docker image **aoc2022cpp**:
    ```shell
    docker build --pull --rm -f "Dockerfile" -t aoc2022cpp:latest "." 
    ```
2. Run your image as an interactive container using:
    ```shell
    docker run -i -t aoc2022cpp:latest
    ```