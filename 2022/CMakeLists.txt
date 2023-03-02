cmake_minimum_required(VERSION 3.25)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_OBJCXX_STANDARD_REQUIRED TRUE)

project(advent2022-1)
project(advent2022-2)

add_executable(advent2022-1 ./day1/main.cpp ../utils/file.h )
add_executable(advent2022-2 ./day2/main.cpp ./day2/action.h ./day2/rock.h ./day2/paper.h ./day2/scissors.h ../utils/file.h )
