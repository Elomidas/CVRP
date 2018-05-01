//
// Created by bastien on 14/03/2018.
//

#include "../include/Algorithm.h"
#include "../include/GraphFactory.h"
#include <iostream>
#include <math.h>

#define _DEFAULT_INPUT "data/data01.txt"

Algorithm::Algorithm() : m_graph(GraphFactory::readFile("../data/data01.txt")) {
    //Nothing
}

Algorithm::Algorithm(const std::string &str) : m_graph(GraphFactory::readFile(str)) {
    //Nothing
}

Algorithm::~Algorithm() = default;

void Algorithm::lancerAlgo() {
    //Nothing
}
