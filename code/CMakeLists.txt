cmake_minimum_required(VERSION 3.26)
project(DA2425_PRJ2_G21)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}")
set(CMAKE_BUILD_TYPE "Release")
include_directories(project2)
include_directories(data)

set( CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_TMP} )

add_executable(DA2425_PRJ2_G21
        project2/main.cpp
        project2/knapsack.h
        project2/knapsack.cpp
        project2/io.h
        project2/io.cpp
        project2/interface.h
        project2/interface.cpp
)
