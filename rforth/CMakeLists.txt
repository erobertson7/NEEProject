FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
	rforth
	rforth.c
	rforth_functions.c
	rforth_functions.h
	int_stack_operators.c
	int_stack_operators.h
  )

add_executable(
	int_stack_operations_Tests
	int_stack_operations_Tests.cc
	int_stack_operators.c
)
target_link_libraries(
	int_stack_operations_Tests
	gtest_main
    -lpthread
)
include(GoogleTest)
gtest_discover_tests(int_stack_operations_Tests)