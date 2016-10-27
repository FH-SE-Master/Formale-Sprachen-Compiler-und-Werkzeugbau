cmake_minimum_required(VERSION 3.6)
project(Grammar)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -static-libgcc -static-libstdc++")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(SOURCE_FILES
    Grammar.cpp
    Grammar.h
    ObjectCounter.h
    SequenceStuff.cpp
    SequenceStuff.h
    SymbolPool.cpp
    SymbolPool.h
    Vocabulary.cpp
    Vocabulary.h
    Language.hpp
    Language.cpp
    GrammarUtil.cpp
    GrammarUtil.hpp
        LanguageUtil.cpp
        LanguageUtil.hpp
    Main.cpp)

add_executable(Grammar ${SOURCE_FILES})