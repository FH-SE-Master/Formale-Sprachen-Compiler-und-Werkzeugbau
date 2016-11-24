cmake_minimum_required(VERSION 3.6)
project(Calc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES
    Calc.tab.c
    Calc.tab.h
    lex.yy.c)

add_executable(Calc ${SOURCE_FILES})