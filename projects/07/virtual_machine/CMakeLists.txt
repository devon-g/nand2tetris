cmake_minimum_required(VERSION 3.5)

project(VMTranslator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    main.cpp
    CodeWriter.h
    CodeWriter.cpp
    Parser.h
    Parser.cpp
    COMMAND_TYPE.h
)
