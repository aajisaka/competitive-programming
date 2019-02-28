cmake_minimum_required(VERSION 3.10)
project(CompetitiveProgramming)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -fsanitize=address,fuzzer-no-link -fsanitize-coverage=edge,indirect-calls")

add_executable(program main.cpp)