cmake_minimum_required(VERSION 2.8)

project(life)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS "-std=c99")

include_directories(unity/include)

add_executable(unit_tests unit_tests.c logic.c fileHandling.c unity/src/unity.c)