cmake_minimum_required(VERSION 3.25)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_OBJCXX_STANDARD_REQUIRED TRUE)

project(advent2022-1)
project(advent2022-2)
project(advent2022-3)
project(advent2022-4)
project(advent2022-5)
project(advent2022-6)
project(advent2022-7)
project(advent2022-8)
project(advent2022-9)
project(advent2022-10)
project(advent2022-11)
project(advent2022-12)

add_executable(advent2022-1 ./day1/main.cpp ../utils/file.h )
add_executable(advent2022-2 ./day2/main.cpp ./day2/action.h ./day2/rock.h ./day2/paper.h ./day2/scissors.h ../utils/file.h )
add_executable(advent2022-3 ./day3/main.cpp ../utils/file.h )
add_executable(advent2022-4 ./day4/main.cpp ../utils/file.h )
add_executable(advent2022-5 ./day5/main.cpp ../utils/file.h )
add_executable(advent2022-6 ./day6/main.cpp ../utils/file.h )
add_executable(advent2022-7 ./day7/main.cpp ../utils/file.h )
add_executable(advent2022-8 ./day8/main.cpp ../utils/file.h )
add_executable(advent2022-9 ./day9/main.cpp ../utils/file.h )
add_executable(advent2022-10 ./day10/main.cpp ../utils/file.h )
add_executable(advent2022-11 ./day11/main.cpp ../utils/file.h )
add_executable(advent2022-12 ./day12/main.cpp ../utils/file.h )
