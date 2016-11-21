cmake_minimum_required(VERSION 3.6)
project(AutomataForStudentsV4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -static-libgcc -static-libstdc++")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(SOURCE_FILES
        CharSet.cpp
        SymbolStuff.cpp
        StateStuff.cpp
        Mappers.cpp
        FA.cpp
        DFA.cpp
        NFA.cpp
        Grammar.cpp
        SequenceStuff.cpp
        AutomateUtil.cpp
        Test.cpp)

# Executable for Deterministic automats
#add_executable(DFATest DFATest.cpp)
# Executable for Non-deterministic automats
#add_executable(NFATest NFATest.cpp)
# Executable for AutomateUtil test
add_executable(Test ${SOURCE_FILES})