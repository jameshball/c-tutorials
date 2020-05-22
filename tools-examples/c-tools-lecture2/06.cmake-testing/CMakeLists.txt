cmake_minimum_required(VERSION 2.6)
project(list_example)

set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_BUILD_TYPE Debug)
enable_testing()

add_subdirectory(lib)
include_directories(lib)

add_executable(avgwordlen avgwordlen.c)
target_link_libraries(avgwordlen intlist)

add_test(tests lib/testlist)
set_tests_properties(tests PROPERTIES FAIL_REGULAR_EXPRESSION "FAIL")
#set_tests_properties(tests PROPERTIES PASS_REGULAR_EXPRESSION "OK")

# You can also define a macro to simplify adding many tests

# macro(do_test arg result)
# add_test(myTest${arg} testfunction ${arg})
# set_tests_properties(myTest${arg} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
# endmacro(do_test)
