cmake_minimum_required(VERSION 3.9)
project(CUnit)

set(CMAKE_C_STANDARD 99)
add_definitions(-Wall)


add_library(${PROJECT_NAME} src/cunit.c src/cunit.h)

#add_executable(test src/cunit.c src/cunit.h main.c)