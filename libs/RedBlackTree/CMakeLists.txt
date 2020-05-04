cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_C_COMPILER "/usr/bin/clang")

project(RedBlackTree)

add_library(RedBlackTree INTERFACE)

target_include_directories(RedBlackTree INTERFACE Headers)
target_compile_options(RedBlackTree INTERFACE $<$<COMPILE_LANGUAGE:CXX>:-Werror -Wall -Wextra -std=c++17>)

add_subdirectory(Tests)