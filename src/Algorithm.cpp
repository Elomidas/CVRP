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

void Algorithm::reverse(Solution solution, unsigned int n1, unsigned int n2) {
    //TODO à tester
    unsigned int tmp_value = NULL;
    unsigned int tmp_num_path = 0;
    unsigned int tmp_index = 0;
    unsigned int i =0 ,j = 0;
    for(std::vector<unsigned int> path : solution.getPaths()){
        for(unsigned int node : path){
            if(node == n1){
                if(tmp_value == NULL){
                    tmp_value = n1;
                    tmp_num_path = i;
                    tmp_index = j;
                }
                else{
                    solution.getPaths()[i][j] = n1;
                    solution.getPaths()[tmp_num_path][tmp_index] = tmp_value;
                    return;
                }
            }
            else if(node == n2){
                if(tmp_value == NULL){
                    tmp_value =n2;
                    tmp_num_path = i;
                    tmp_index = j;
                }
                else{
                    solution.getPaths()[i][j] = n2;
                    solution.getPaths()[tmp_num_path][tmp_index] = tmp_value;
                    return;
                }
            }
            j++;
        }
        i++;
    }
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
