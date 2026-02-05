cmake_minimum_required(VERSION 3.16)

project(mathcalculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(calculator
	src/main.cpp
	src/lexer.cpp
	src/parser.cpp
)

target_include_directories(calculator PRIVATE include)
