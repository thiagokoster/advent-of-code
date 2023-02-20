cmake_minimum_required(VERSION 3.26)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_OBJCXX_STANDARD_REQUIRED TRUE)

project(Advent2022-1)
project(Advent2022-2)
add_executable(Advent2022-1 ./day1/main.cpp ../utils/file.h )
add_executable(Advent2022-2 ./day2/main.cpp ../utils/file.h )
