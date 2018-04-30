//
// Created by bastien on 14/03/2018.
//

#include "../include/Algorithm.h"
#include "../include/GraphFactory.h"
#include <iostream>
#include <math.h>

#define _DEFAULT_INPUT "data/data01.txt"

Algorithm::Algorithm() : m_graph((unsigned int)0) {
    std::vector<graph::Node> vector = GraphFactory::readFile("../data/data01.txt");
    m_graph = graph::Graph(vector);
}

Algorithm::~Algorithm() = default;

void Algorithm::lancerAlgo() {
    //Nothing
}
