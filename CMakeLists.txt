cmake_minimum_required(VERSION 3.22)
project(prack-numbers-system)

set(CMAKE_CXX_STANDARD 20)

add_executable(prack-numbers-system main.cpp big_int.cpp
        fraction.cpp
        fraction.h)
