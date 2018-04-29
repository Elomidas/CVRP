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

Algorithm::~Algorithm() {
    delete m_graph;
    delete m_settings;
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
     //TODO à tester
    for(unsigned int i(0);i<m_graph.getNodeNb();i++){
        unsigned int capacity_left=Truck::getCapacity();
        int truck_nb_saved = -1;
        for(unsigned int id_truck(0);id_truck<m_graph.getTrucksNb();id_truck++){
            if(m_graph.getTruck(id_truck)->getCapacity() - m_graph.getTruck(id_truck)->getComputedLoad() - m_graph.getNodes()[i].getQuantity() < capacity_left){
                truck_nb_saved = id_truck;
                capacity_left = m_graph.getTruck(i)->getCapacity() - m_graph.getTruck(i)->getComputedLoad()- m_graph.getNodes()[i].getQuantity();
            }
        }
        if(truck_nb_saved != -1)
            m_graph.getTruck((unsigned int)truck_nb_saved)->addState(m_graph.getNodes()[i]);
    }
    return m_graph.getSolution();
}

const std::vector<Solution> Algorithm::getVoisinage(const Solution solution, const std::vector< std::pair<unsigned int,unsigned int> > listeTabou = std::vector< std::pair<unsigned int,unsigned int> >()) {
    //TODO fonction à faire

    return std::vector<Solution>();
}

const std::pair<unsigned int, unsigned int> Algorithm::getDifference(const Solution s1, const Solution s2) {
    //TODO définir la fonction
    return std::pair<unsigned int, unsigned int>();
}
