//
// Created by bastien on 14/03/2018.
//

#include "../include/Algorithm.h"
#include "../include/GraphFactory.h"
#include "../include/Graphviz.h"
#include <iostream>

/**
 * Constructor
 * @param str Source file
 */
Algorithm::Algorithm(const std::string &str) : m_graph(GraphFactory::readFile(str)) {
    //Nothing
}


/**
 * Destructor
 */
Algorithm::~Algorithm() = default;

/**
 * To launch one algorithm (tabou or genetic)
 */
void Algorithm::launchAlgo() {
    //Nothing
}

/**
 * Set the graph to match the best solution
 */
void Algorithm::getMini() {
    //Nothing
}

/**
 * Create a .svg file of the graph representing the best solution
 */
void Algorithm::display() {
    display("");
}

/**
 * Create a .svg file of the graph representing the best solution
 * @param out Image's name (without the .svg)
 */
void Algorithm::display(const std::string &out) {
    getMini();
    Graphviz::getImg(m_graph, (out.empty() ? "noName" : out));
}
