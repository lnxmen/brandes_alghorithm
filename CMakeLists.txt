cmake_minimum_required(VERSION 3.5.1)
project(Brandes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -g")

include_directories(./include)

set(SOURCE_FILES src/graph.cpp src/counters.cpp src/manager.cpp src/brandes.cpp src/main.cpp)
add_executable(brandes ${SOURCE_FILES})