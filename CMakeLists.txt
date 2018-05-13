cmake_minimum_required(VERSION 3.9)
project(CUnit)

set(CMAKE_C_STANDARD 99)
add_definitions(-g -Wall -x c99)


add_library(${PROJECT_NAME}
        src/cunit.c
        src/cunit.h)
