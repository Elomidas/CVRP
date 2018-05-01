//
// Created by bastien on 14/03/2018.
//

#include "../include/Algorithm.h"
#include "../include/GraphFactory.h"
#include "../include/Graphviz.h"
#include <iostream>

/**
 * Constructor
 * @param str
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

void Algorithm::display() {
    display("");
}

void Algorithm::getMini() {
    //Nothing
}

void Algorithm::display(const std::string &out) {
    getMini();
    Graphviz::getImg(m_graph, (out.empty() ? "noName" : out));
}
