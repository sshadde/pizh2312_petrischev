cmake_minimum_required(VERSION 3.10)
project(sandpile)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(lib)

add_executable(sandpile
    src/args_parser.cpp
    src/bmp_writer.cpp
    src/sandpile.cpp
    src/main.cpp
)
