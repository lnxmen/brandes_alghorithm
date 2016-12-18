cmake_minimum_required(VERSION 3.6)
project(Brandes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

set(SOURCE_FILES main.cpp)
add_executable(Brandes ${SOURCE_FILES})