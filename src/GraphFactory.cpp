//
// Created by elomidas on 24/04/18.
//

#include <iostream>
#include <fstream>
#include <climits>
#include <cassert>
#include <queue>

#include "../include/GraphFactory.h"

std::vector<graph::Node> GraphFactory::readFile(const std::string &path) {
    std::ifstream file(path);
    if(file) {
        std::vector<graph::Node> nodes;
        std::string line;
        getline(file, line);
        while(getline(file, line)) {
            unsigned int parts[] = {0,0,0,0};
            splitLine(line, parts);
            //std::cout << "Node : " << parts[0] << "," << parts[3] << "," << parts[1] << "," << parts[2] << std::endl;
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


void GraphFactory::splitLine(std::string &line, unsigned int *res) {
    std::string delimiter = ";";
    unsigned int i;
    size_t pos = 0;
    for(i = 0; ((pos = line.find(delimiter)) != std::string::npos); i++) {
        res[i] = atoi(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());
    }
    res[i] = atoi(line);
}

unsigned int GraphFactory::atoi(const std::string &number) {
    char *endptr;
    long val;

    errno = 0;
    val = strtol(number.c_str(), &endptr, 10);

    /* Check for various possible errors */

    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
        || (errno != 0 && val == 0)) {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    if (endptr == number) {
        std::cerr << "No digits were found in '" << number << "'." << std::endl;
        exit(EXIT_FAILURE);
    }
    return static_cast<unsigned int>(val);
}

void GraphFactory::test(const std::string &path) {
    std::vector<graph::Node> vector = readFile(path);
    auto graph1 = new graph::Graph(vector);
    std::clog << std::endl << "Tests phase" << std::endl;
    for(unsigned int i(0); i < 5; i++) {
        std::clog << "i = " << i << std::endl;
        for(unsigned int j(0); j < i; j++) {
            double d = graph1->getDistance(i, j);
            std::clog << d << ", ";
        }
        std::clog << std::endl;
    }

    std::clog << std::endl << "Copy phase" << std::endl;

    graph::Graph graph2(*graph1);

    std::clog << std::endl << "First deletion" << std::endl;

    delete graph1;

    std::clog << "Tests phase 2" << std::endl;
    for(unsigned int i(0); i < 5; i++) {
        std::clog << "i = " << i << std::endl;
        for(unsigned int j(0); j < i; j++) {
            std::clog << graph2.getDistance(i, j) << ", ";
        }
        std::clog << std::endl;
    }
}


