cmake_minimum_required(VERSION 3.13)
project(day11)

set(CMAKE_CXX_STANDARD 14)
find_package (Threads)
add_executable(day11 main.cpp)
target_link_libraries (day11 ${CMAKE_THREAD_LIBS_INIT})