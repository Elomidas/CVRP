//
// Created by bastien on 14/03/2018.
//

#include "../include/Algorithm.h"
#include "../include/GraphFactory.h"

#define _DEFAULT_INPUT "data/data01.txt"

Algorithm::Algorithm() : m_graph((unsigned int)0) {
    std::vector<graph::Node> vector = GraphFactory::readFile("data/data01.txt");
    m_graph = graph::Graph(vector);
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
    //TODO fonction à faire
}

const Graph Algorithm::getRandomSolution() {
    return Graph(0);
    //TODO fonction à faire
}

const std::vector<Graph> Algorithm::getVoisinage(const std::vector< std::pair<Node,Node> > listeTabou = std::vector< std::pair<Node,Node> >()) {
    return std::vector<Graph>();
    //TODO fonction à faire
}

const double Algorithm::funcFitness(const Graph) {
    return 0;
    //TODO définir la fonction fitness
}

const std::pair<Node, Node> Algorithm::getDifference(const Graph, const Graph) {
    return std::pair<Node, Node>();
    //TODO définir la fonction
}
