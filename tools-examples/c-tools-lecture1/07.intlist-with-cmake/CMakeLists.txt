cmake_minimum_required(VERSION 2.6)
project(list_example)

set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(lib)
include_directories(lib)

add_executable(avgwordlen avgwordlen.c)
target_link_libraries(avgwordlen intlist)
