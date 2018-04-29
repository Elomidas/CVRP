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




/*
 *
 * ==== Fuctions used in algorithms
 *
 */
Solution Algorithm::getRandomSolution() {
     return m_graph.getSolution();
}

const std::vector<Solution> Algorithm::getVoisinage(const Solution solution, const std::vector< std::pair<Node,Node> > listeTabou = std::vector< std::pair<Node,Node> >()) {
    return std::vector<Solution>();
    //TODO fonction à faire
}

const double Algorithm::funcFitness(const Solution solution) {
    return 0;
    //TODO définir la fonction fitness
}

const std::pair<Node, Node> Algorithm::getDifference(const Solution s1, const Solution s2) {
    return std::pair<Node, Node>();
    //TODO définir la fonction
}
