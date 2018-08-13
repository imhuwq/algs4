cmake_minimum_required(VERSION 3.5)
project(algs4)

set(CMAKE_CXX_STANDARD 11)
add_subdirectory(lib/googletest)

# things to be gathered
set(PRJ_INCLUDE_DIRS "")
set(PRJ_LIBRARIES "")
set(PRJ_SOURCES "")


# include dirs
list(APPEND PRJ_INCLUDE_DIRS includes)
list(APPEND PRJ_INCLUDE_DIRS tests)
list(REMOVE_DUPLICATES PRJ_INCLUDE_DIRS)
include_directories(${PRJ_INCLUDE_DIRS})

# libraries


add_executable(run_test test.cpp ${PRJ_SOURCES})
target_link_libraries(run_test ${PRJ_LIBRARIES} gtest_main)
add_test(NAME run_test COMMAND run_test)
