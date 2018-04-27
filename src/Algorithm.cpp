//
// Created by bastien on 14/03/2018.
//

#include "../include/Algorithm.h"
#include "../include/GraphFactory.h"

#define _DEFAULT_INPUT "data/data01.txt"

Algorithm::Algorithm() : m_graph(0) {
    std::queue<graph::Node> queue = GraphFactory::readFile("data/data01.txt");
    m_graph = graph::Graph(queue);
}

Algorithm::~Algorithm() {
    //Nothing ATM
}

void Algorithm::lancerAlgo() {
    //Nothing
}

/*
 *
 * ==== Transformations élémentaires
 *
 */

void Algorithm::reverse(Node n1, Node n2) {

}