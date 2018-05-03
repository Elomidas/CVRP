//
// Created by elomidas on 24/04/18.
//

#include <iostream>
#include <fstream>
#include <climits>
#include <cassert>
#include <queue>

#include "../include/GraphFactory.h"
#include "../include/TabouAlgorithm.h"

/**
 * Create a Graph from a source file
 * @param path  Path to the file (example : "../data/data01.txt")
 * @return      Graph corresponding to the given file
 */
std::vector<graph::Node> GraphFactory::readFile(const std::string &path) {
    std::ifstream file(path);
    if(file) {
        std::vector<graph::Node> nodes;
        std::string line;
        getline(file, line);
        while(getline(file, line)) {
            std::vector<unsigned int> parts = Graph::splitLine(line);
            nodes.emplace_back(graph::Node(parts[0], parts[3], parts[1], parts[2]));
        }
        file.close();
        std::clog << std::endl << "File size : " << nodes.size() << std::endl;
        return nodes;
    }
    else {
        std::cerr << "Unable to open file " << path << " !" << std::endl;
        assert(false);
    }
}

/**
 * Function used to read a file, create the Graph and copy it to check new constructors.
 * @param path Path to the file to read.
 */
void GraphFactory::test(const std::string &path) {
    auto graph1 = new graph::Graph(readFile(path));

    std::clog << std::endl << "Distances in first graph" << std::endl;

    for(unsigned int i(0); i < 5; i++) {
        for(unsigned int j(0); j < i; j++) {
            double d = graph1->getDistance(i, j);
            std::clog << d << ", ";
        }
        std::clog << std::endl;
    }

    graph::Graph graph2(*graph1);

    std::clog << std::endl << "Delete first graph" << std::endl << std::endl;

    delete graph1;


    std::clog << "Distances in second graph" << std::endl;

    /* Read the copy after deleting the source
     * Check if all object are duplicate and assure there isn't any memory conflict.
     */

    for(unsigned int i(0); i < 5; i++) {
        for(unsigned int j(0); j < i; j++) {
            std::clog << graph2.getDistance(i, j) << ", ";
        }
        std::clog << std::endl;
    }

    std::clog << std::endl << "Test passed" << std::endl << std::endl;
}


