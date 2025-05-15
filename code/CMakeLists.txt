cmake_minimum_required(VERSION 3.28)
project(DA2425_PRJ2_G21)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Debug")

get_filename_component(PROJECT_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" DIRECTORY)
set(ORTOOLS_PATH "${PROJECT_ROOT_DIR}/or-tools")
list(APPEND CMAKE_PREFIX_PATH "${ORTOOLS_PATH}")
find_package(ortools REQUIRED)

if(NOT ortools_FOUND)
    message(FATAL_ERROR "OR-Tools not installed. Check https://developers.google.com/optimization/install/cpp")
endif()

file(GLOB PROJECT2_SOURCES CONFIGURE_DEPENDS
    project2/*.cpp
)

add_executable(DA2425_PRJ2_G21 ${PROJECT2_SOURCES})

target_include_directories(DA2425_PRJ2_G21 PRIVATE
    project2
    data
    or-tools
)

target_link_libraries(DA2425_PRJ2_G21 PRIVATE ortools::ortools)
