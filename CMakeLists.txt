cmake_minimum_required(VERSION 3.9)
project(CVRP)

set(CMAKE_CXX_STANDARD 11)

add_executable(CVRP src/main.cpp src/Node.cpp include/Node.h src/Graph.cpp include/Graph.h src/Algorithm.cpp include/Algorithm.h)