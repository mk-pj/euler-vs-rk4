cmake_minimum_required(VERSION 3.20)
project(3)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)

include_directories(include)
add_executable(3 src/main.cpp src/func.cpp)