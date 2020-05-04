cmake_minimum_required(VERSION 3.10.2)

project(RedBlackTree_run)

add_subdirectory(libs/RedBlackTree)

add_executable(RedBlackTree_run main.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(RedBlackTree_run
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/arch/debug"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/debug"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/debug"
    )
else()
    set_target_properties(RedBlackTree_run
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/arch/release"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/release"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/release"
    )
endif()

target_link_libraries(RedBlackTree_run PRIVATE RedBlackTree)