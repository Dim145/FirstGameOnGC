cmake_minimum_required(VERSION 3.17)
project(WallBreak C)

set(CMAKE_C_STANDARD 99)

add_executable(WallBreak src/main.c)

include_directories(include)

add_custom_target (myTest COMMAND "./MakeGB.bat" )
add_dependencies (WallBreak myTest)