cmake_minimum_required(VERSION 3.10.2)

project(RedBlackTree)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_C_COMPILER "/usr/bin/clang")

file(GLOB SRC_FILES RELATIVE Src/ "*.cpp" "*.h")
file(GLOB HEADERS_FILES RELATIVE Headers/ "*.h")
add_executable(RedBlackTree Src/main.cpp Headers/RedBlackTree.h ${SRC_FILES} ${HEADERS_FILES})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(RedBlackTree
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/arch/debug"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/debug"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/debug"
    )
else()
    set_target_properties(RedBlackTree
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/arch/release"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/release"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/release"
    )
endif()


target_compile_options(RedBlackTree PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-Werror -Wall -Wextra -std=c++17>)