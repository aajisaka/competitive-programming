cmake_minimum_required(VERSION 3.10)
project(AtCoder)

set(CMAKE_CXX_STANDARD 14)

add_executable(AtCoder main.cpp tool.cpp dijkstra.cpp dfs.cpp mod_inverse.cpp bit_max.cpp)