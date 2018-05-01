//
// Created by bastien on 14/03/2018.
//

#include "../include/Algorithm.h"
#include "../include/GraphFactory.h"
#include "../include/Graphviz.h"
#include <iostream>
#include <math.h>

/**
 * Default constructor
 */
Algorithm::Algorithm() : m_graph(GraphFactory::readFile("../data/data01.txt")) {
    //Nothing
}

/**
 * Other constructor
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
void Algorithm::lancerAlgo() {
    //Nothing
}
