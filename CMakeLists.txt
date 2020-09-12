cmake_minimum_required(VERSION 3.10)
project(competitive_programming_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -fsanitize=address,undefined -DLOCAL -g")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test")

file(GLOB TASKS "tasks/*.cpp")
file(GLOB_RECURSE HEADERS "library/*hpp")

add_executable(output output/main.cpp ${HEADERS})
add_executable(testrunner testrunner/main.cpp)
add_executable(test ${TASKS} ${HEADERS})
