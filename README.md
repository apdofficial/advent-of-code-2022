# Advent of Code 2022 in C++20

[https://adventofcode.com/2022](https://adventofcode.com/2022)
 
### External dependencies
- [fmt](https://github.com/fmtlib/fmt) 
- [Catch2](https://github.com/catchorg/Catch2)
- [boost](https://www.boost.org/) // due to the size of the library we require the lib using CMakeList.txt instead of a git submodule

###  Usage

1.  **Build** a docker **image** aoc2022cpp:
    ```shell
    docker build --pull --rm -f "Dockerfile" -t aoc2022cpp:latest "." 
    ```
2. **Run** your **image** as an interactive container using:
    ```shell
    docker run -i -t aoc2022cpp:latest
    ```
3. **Compile** the code using the following commands:
    ```shell
    mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug -DUSE_MSAN=ON .. && make -j$(nproc) && cd ..
    ```
4. Static check with **cppcheck**:
     ```shell
    cppcheck --enable=all --suppress=unusedFunction --std=c++20 -I src/include/ src/
    ```
5. Dynamic check with **Catch2** and **valgrind**:
    ```shell
   cd build/test/ && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./tests && cd ../..
   ```
6. Run the tests with **Catch2**:
    ```shell
    cd build/test/ && ./tests && cd ../..
    ```