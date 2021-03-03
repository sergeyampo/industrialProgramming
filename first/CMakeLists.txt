cmake_minimum_required(VERSION 3.17)
project(industrialProgramming)

set(CMAKE_CXX_STANDARD 20)

add_executable(industrialProgramming main.cpp)

target_include_directories(industrialProgramming PUBLIC ./lib)