cmake_minimum_required(VERSION 3.9)
project(CVRP)

set(CMAKE_CXX_STANDARD 11)
set(GRAPHVIZ_INCLUDE_DIR "/usr/local/include/")
set(GRAPHVIZ_LIBS "/usr/local/lib/libgvc.so;/usr/local/lib/libcgraph.so;/usr/local/lib/graphviz/libgvplugin_core.so;/usr/local/lib/graphviz/libgvplugin_dot_layout.so")

message(STATUS "start running cmake...")

find_package(Boost 1.58.0 COMPONENTS graph REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

include_directories("${GRAPHVIZ_INCLUDE_DIR}")

add_executable(CVRP src/main.cpp src/Node.cpp include/Node.h src/Graph.cpp include/Graph.h src/Algorithm.cpp include/Algorithm.h src/Truck.cpp include/Truck.h src/TruckStep.cpp include/TruckStep.h src/DistancesMatrix.cpp include/DistancesMatrix.h src/DistanceNode.cpp include/DistanceNode.h src/GeneticAlgorithm.cpp include/GeneticAlgorithm.h src/AlgorithmSettings.cpp include/AlgorithmSettings.h src/GraphFactory.cpp include/GraphFactory.h src/TabouAlgorithm.cpp include/TabouAlgorithm.h src/Solution.cpp include/Solution.h src/ElementaryTransformation.cpp include/ElementaryTransformation.h src/Graphviz.cpp include/Graphviz.h)

target_link_libraries(CVRP ${GRAPHVIZ_LIBS})

target_link_libraries(CVRP ${Boost_LIBRARIES})
