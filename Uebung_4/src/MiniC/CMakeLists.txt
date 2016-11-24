cmake_minimum_required(VERSION 3.6)
project(MiniC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES
    lex.yy.c
    minic.tab.c
    minic.tab.h)

add_executable(MiniC ${SOURCE_FILES})