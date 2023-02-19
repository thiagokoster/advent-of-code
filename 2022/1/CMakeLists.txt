cmake_minimum_required(VERSION 3.10)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_OBJCXX_STANDARD_REQUIRED TRUE)

project(Advent2022-1)
add_executable(Advent2022-1 main.cpp ../utils/file.h )
