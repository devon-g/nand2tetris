cmake_minimum_required(VERSION 3.5)

project(assembler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    main.cpp
    Code.h
    Code.cpp
    Parser.h
    Parser.cpp
    SymbolTable.h
    SymbolTable.cpp
)
