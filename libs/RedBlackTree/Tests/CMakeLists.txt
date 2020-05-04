configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
  if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

enable_testing()

project(RedBlackTreeTests)

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

add_executable(RedBlackTreeTests Test.cpp main.cpp InsertTest.cpp RemoveTest.cpp RemoveBlackNodeWithRedBrotherTest.cpp RemoveBlackNodeWithRedParent.cpp Utils.cpp Utils.h RemoveBlackNodeWithBlackParentAndBlackBrother.cpp)
target_link_libraries(RedBlackTreeTests gtest_main RedBlackTree)

add_test(NAME RedBlackTreeTests COMMAND RedBlackTreeTests)