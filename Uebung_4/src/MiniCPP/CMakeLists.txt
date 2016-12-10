cmake_minimum_required(VERSION 3.6)
project(MiniCPP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(SOURCE_FILES
    minicpp-lex.yy.c
    minicpp.tab.h
    minicpp.tab.c)

add_executable(MiniCPP ${SOURCE_FILES})