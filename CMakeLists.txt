cmake_minimum_required(VERSION 3.5.1)
project(Brandes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

set(SOURCE_FILES brandes.cpp)
add_executable(brandes ${SOURCE_FILES})