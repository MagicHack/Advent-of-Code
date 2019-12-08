cmake_minimum_required(VERSION 3.10)
project(day5)

set(CMAKE_CXX_STANDARD 14)
find_package (Threads)
add_executable(day5 main.cpp)
target_link_libraries (day5 ${CMAKE_THREAD_LIBS_INIT})
