cmake_minimum_required(VERSION 3.6)
project(AutomataForStudentsV4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -static-libgcc -static-libstdc++")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(SOURCE_FILES
        CharSet.cpp
        CharSet.h
        DFA.cpp
        DFA.h
        DFATest.cpp
        FA.cpp
        FA.h
        Mappers.cpp
        Mappers.h
        NFA.cpp
        NFA.h
        NFATest.cpp
        ObjectCounter.h
        StateStuff.cpp
        StateStuff.h
        SymbolStuff.cpp
        SymbolStuff.h
        Grammar.h
        Grammar.cpp
        SequenceStuff.h
        SequenceStuff.cpp
        Vocabulary.h
        Vocabulary.cpp
        Mealy.hpp
        Mealy.cpp)

# Executable for Deterministic automats
add_executable(DFATest DFATest.cpp)
# Executable for Non-deterministic automats
add_executable(NFATest NFATest.cpp)