cmake_minimum_required(VERSION 3.12)
project(ELLA-RFORTH-APRIL-6)

set(CMAKE_CXX_STANDARD 11)

add_executable(
  token
  token.c
  token.h
)

add_subdirectory(googletest)

add_executable(
  repl_tests
  repl_tests.cc
  repl_support.c
  repl_support.h
  )

target_link_libraries(repl_tests gtest_main)

include(GoogleTest)
gtest_discover_tests(repl_tests)