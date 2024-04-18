cmake_minimum_required(VERSION 3.12)
project(rforth)

set(CMAKE_CXX_STANDARD 11)

add_executable(
	rforth_functions
	rforth_functions.c
	rforth_functions.h)

add_executable(
  int_stack_operators
  int_stack_operators.c
  int_stack_operators.h
)

add_subdirectory(googletest)

target_link_libraries(repl_tests gtest_main)

include(GoogleTest)
gtest_discover_tests(repl_tests)