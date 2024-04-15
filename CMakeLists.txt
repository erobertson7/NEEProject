cmake_minimum_required(VERSION 3.12)
project(NEEProject)

set(CMAKE_CXX_STANDARD 11)

add_executable(
  rforth_functions
  rforth_functions.c
  rforth_functions.h
)

add_subdirectory(googletest)

target_link_libraries(rforth_functions gtest_main)

include(GoogleTest)
gtest_discover_tests(rforth_functions)