cmake_minimum_required(VERSION 3.9)
project(CUnit)

set(CMAKE_CXX_STANDARD 11)

add_executable(CUnit
        cunit.c
        cunit.h
        main.c)
