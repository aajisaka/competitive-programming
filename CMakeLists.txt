cmake_minimum_required(VERSION 3.12)
project(competitive_programming_cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -fsanitize=address,undefined -DLOCAL -g")

add_executable(a.out code/a.cpp)
add_executable(b.out code/b.cpp)
add_executable(c.out code/c.cpp)
add_executable(d.out code/d.cpp)
add_executable(e.out code/e.cpp)
add_executable(f.out code/f.cpp)
add_executable(g.out code/g.cpp)