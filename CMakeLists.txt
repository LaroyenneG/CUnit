cmake_minimum_required(VERSION 3.9)
project(CUnit)

set(CMAKE_C_STANDARD 99)
add_definitions(-g -Wall -x c)


add_library(CUnit
        cunit.c
        cunit.h
        )
