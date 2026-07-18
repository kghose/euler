cmake_minimum_required(VERSION 3.31)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Euler1005)

add_executable(tests tests.cpp lib.cpp lib_test.cpp)
add_executable(main main.cpp lib.cpp)

include_directories("../../")
