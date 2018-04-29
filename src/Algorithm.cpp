//
// Created by bastien on 14/03/2018.
//

#include "../include/Algorithm.h"
#include "../include/GraphFactory.h"
#include <iostream>

#define _DEFAULT_INPUT "data/data01.txt"

Algorithm::Algorithm() : m_graph((unsigned int)0) {
    std::vector<graph::Node> vector = GraphFactory::readFile("../data/data01.txt");
    m_graph = graph::Graph(vector);
}

Algorithm::~Algorithm() = default;

void Algorithm::lancerAlgo() {
    //Nothing
}

/*
 *
 * ==== Transformations élémentaires
 *
 */

void Algorithm::reverse(Node n1, Node n2) {
    //TODO fonction à faire
}




/*
 *
 * ==== Fuctions used in algorithms
 *
 */

const std::vector<Solution> Algorithm::getVoisinage(const Solution solution, const std::vector< std::pair<unsigned int,unsigned int> > listeTabou = std::vector< std::pair<unsigned int,unsigned int> >()) {
    //TODO fonction à faire

    return std::vector<Solution>();
}

const std::pair<unsigned int, unsigned int> Algorithm::getDifference(const Solution s1, const Solution s2) {
    //TODO définir la fonction
    return std::pair<unsigned int, unsigned int>();
}
