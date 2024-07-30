cmake_minimum_required(VERSION 3.28)

project(Deque_tests)

set(CMAKE_CXX_STANDARD 17)

add_executable(Deque_tests main.cpp)


#add_subdirectory(Test)

target_include_directories(Deque_tests PUBLIC includes)

