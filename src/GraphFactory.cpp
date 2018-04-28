//
// Created by elomidas on 24/04/18.
//

#include <iostream>
#include <fstream>
#include <climits>
#include <cassert>
#include <queue>

#include "../include/GraphFactory.h"

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
            unsigned int parts[] = {0,0,0,0};
            splitLine(line, parts);
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
 * Retrieve informations from a file's line
 * @param line  Line from the file.
 * @param res   List of the intels retrieved.
 */
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

/**
 * Convert a string into an unsigned int.
 * @param number String to convert.
 * @return Unsigned int obtained.
 */
unsigned int GraphFactory::atoi(const std::string &number) {
    char *endptr;
    long val;

    errno = 0;
    val = strtol(number.c_str(), &endptr, 10);

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

/**
 * Function used to read a file, create the Graph and copy it to check new constructors.
 * @param path Path to the file to read.
 */
void GraphFactory::test(const std::string &path) {
    std::vector<graph::Node> vector = readFile(path);
    auto graph1 = new graph::Graph(vector);=
    for(unsigned int i(0); i < 5; i++) {
        for(unsigned int j(0); j < i; j++) {
            double d = graph1->getDistance(i, j);
            std::clog << d << ", ";
        }
        std::clog << std::endl;
    }

    graph::Graph graph2(*graph1);

    delete graph1;

    /* Read the copy after deleting the source
     * Check if all object are duplicate and assure there isn't any memory conflict.
     */

    for(unsigned int i(0); i < 5; i++) {
        for(unsigned int j(0); j < i; j++) {
            std::clog << graph2.getDistance(i, j) << ", ";
        }
        std::clog << std::endl;
    }
}


