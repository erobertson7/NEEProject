cmake_minimum_required(VERSION 3.12)
project(EXTENDING_int_stack_t)

set(CMAKE_CXX_STANDARD 11)

add_executable(int_stack
        int_stack.c)

add_subdirectory(googletest)

add_executable(int_stack_tests
        int_stack_tests.cc
        int_stack.c)

target_link_libraries(int_stack_tests gtest_main)

include(GoogleTest)
gtest_discover_tests(int_stack_tests)