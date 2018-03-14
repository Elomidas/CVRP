cmake_minimum_required(VERSION 3.9)
project(CVRP)

set(CMAKE_CXX_STANDARD 11)

add_executable(CVRP
        include/Node.h
        src/main.cpp
        src/Node.cpp)
