FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    stack_tests
    stack_tests.cc
    stack.c
    stack.hh
    stack.h
)
target_link_libraries(
        stack_tests
        gtest_main
        -lpthread
)


include(GoogleTest)
gtest_discover_tests(stack_tests)