add_library(intlist intlist.c)

add_executable(testlist testlist.c)
target_link_libraries(testlist intlist)
