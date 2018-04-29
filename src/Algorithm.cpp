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

void Algorithm::reverse(Solution &solution, unsigned int n1, unsigned int n2) {
    //TODO à tester
    int tmp_value = -1;
    unsigned int tmp_num_path = 0;
    unsigned int tmp_index = 0;
    unsigned int i =0 ,j = 0;
    for(std::vector<unsigned int> path : solution.getPaths()){
        for(unsigned int node : path){
            if(node == n1){
                if(tmp_value == -1){
                    tmp_value = n1;
                    tmp_num_path = i;
                    tmp_index = j;
                }
                else{
                    solution.getPaths()[i][j] = n1;
                    solution.getPaths()[tmp_num_path][tmp_index] = (unsigned int)tmp_value;
                    return;
                }
            }
            else if(node == n2){
                if(tmp_value == -1){
                    tmp_value =n2;
                    tmp_num_path = i;
                    tmp_index = j;
                }
                else{
                    solution.getPaths()[i][j] = n2;
                    solution.getPaths()[tmp_num_path][tmp_index] = (unsigned int)tmp_value;
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

const std::vector<Solution> Algorithm::getVoisinage(const Solution solution, const std::vector< std::pair<unsigned int,unsigned int> > listeTabou = std::vector< std::pair<unsigned int,unsigned int> >()) {
    //TODO fonction à faire
    std::vector<Solution> voisinage = std::vector<Solution>();
    for(unsigned int i(0); i<=solution.getPaths().size()/2;i++){
        for(unsigned int j(0); j<=solution.getPaths()[i].size()/2;j++){
            std::pair<unsigned int,unsigned int> test_tabou = std::make_pair(i ,j);
            /*
            if(std::find(listeTabou.begin(), listeTabou.end(), test_tabou) != test_tabou){
                Solution tmp = Solution(solution);
                reverse(tmp, i, j);
                voisinage.push_back(tmp);
            }
             */
        }
    }
    return std::vector<Solution>();
}

const std::pair<unsigned int, unsigned int> Algorithm::getDifference(const Solution s1, const Solution s2) {
    //TODO définir la fonction
    return std::pair<unsigned int, unsigned int>();
}
