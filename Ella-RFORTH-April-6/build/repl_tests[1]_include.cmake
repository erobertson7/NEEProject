if(EXISTS "/Users/ellamckenney/Documents/ssh:/c-bootcamp-ellamckenney/R-FORTH/build/repl_tests[1]_tests.cmake")
  include("/Users/ellamckenney/Documents/ssh:/c-bootcamp-ellamckenney/R-FORTH/build/repl_tests[1]_tests.cmake")
else()
  add_test(repl_tests_NOT_BUILT repl_tests_NOT_BUILT)
endif()
