cmake_minimum_required(VERSION 3.10)
project(competitive_programming_cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -fsanitize=address,undefined -DLOCAL -g")

add_executable(output out/main.cpp)
add_executable(testrunner testrun/main.cpp)
file(GLOB TASKS "tasks/*.cpp")
file(GLOB_RECURSE HEADERS "library/*hpp")

add_executable(tester ${TASKS} ${HEADERS})