cmake_minimum_required(VERSION 3.24)
project(sharedMemory)

set(CMAKE_CXX_STANDARD 14)

add_executable(Proc1 process1.cpp)
add_executable(Proc2 process2.cpp)
