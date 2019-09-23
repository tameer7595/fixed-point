cmake_minimum_required(VERSION 3.14)
project(fixed_point)

set(CMAKE_CXX_STANDARD 98)

add_executable(fixed_point main.cpp fixed_point.cpp fixed_point.h test.cpp test.h)