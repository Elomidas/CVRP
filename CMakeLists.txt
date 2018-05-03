cmake_minimum_required(VERSION 3.9)
project(CVRP)

set(CMAKE_CXX_STANDARD 11)


add_executable(CVRP src/main.cpp src/Node.cpp include/Node.h src/Graph.cpp include/Graph.h src/Algorithm.cpp include/Algorithm.h src/Truck.cpp include/Truck.h src/TruckStep.cpp include/TruckStep.h src/DistancesMatrix.cpp include/DistancesMatrix.h src/DistanceNode.cpp include/DistanceNode.h src/GeneticAlgorithm.cpp include/GeneticAlgorithm.h src/GraphFactory.cpp include/GraphFactory.h src/TabouAlgorithm.cpp include/TabouAlgorithm.h src/Solution.cpp include/Solution.h src/ElementaryTransformation.cpp include/ElementaryTransformation.h src/Graphviz.cpp include/Graphviz.h)
