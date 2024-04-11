FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    stack_tests
    stack_tests.cc
    stack.c
    stack.hh
    stack.h
)
add_executable(
    main 
    main.c)
add_executable(
    token
    token.c
    token.h)
target_link_libraries(
        stack_tests
        gtest_main
        -lpthread
)


include(GoogleTest)
gtest_discover_tests(stack_tests)
