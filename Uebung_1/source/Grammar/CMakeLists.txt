cmake_minimum_required(VERSION 3.6)
project(Grammar)

set(INCLUDE_DIRECTORIES C:/MinGW)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES
    Grammar.cpp
    Grammar.h
    Main.cpp
    ObjectCounter.h
    SequenceStuff.cpp
    SequenceStuff.h
    SymbolPool.cpp
    SymbolPool.h
    Vocabulary.cpp
    Vocabulary.h)

add_executable(Grammar ${SOURCE_FILES})