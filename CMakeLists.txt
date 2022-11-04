cmake_minimum_required(VERSION 3.16)
project(Project_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project_1
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h Parameter.cpp Parameter.h Rule.cpp Rule.h Database.cpp Database.h Relation.cpp Relation.h Header.cpp Header.h Tuple.cpp Tuple.h Interpreter.cpp Interpreter.h)
