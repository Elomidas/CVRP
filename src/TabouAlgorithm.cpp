//
// Created by bastien on 26/04/18.
//

#include <iostream>
#include "../include/TabouAlgorithm.h"


TabouAlgorithm::TabouAlgorithm() : m_xmin(0), m_nmax(10), m_T(), m_fmin(0) {
    //Nothing
}

void TabouAlgorithm::lancerAlgo() {
    Graph xo = getRandomSolution();
    m_xmin = xo.copyGraph();
    m_fmin = funcFitness(m_xmin);
    int i=0;
    std::vector<Graph> C;
    do{
        C = getVoisinage(m_T);
        if(!C.empty()){
            Graph y = C.at(0).copyGraph();
            double f_y = funcFitness(y);
            for(int j=1;j<C.size();j++){
                if(funcFitness(C.at(j)) < f_y){
                    y = C.at(j);
                    f_y = funcFitness(y);
                }
            }
            double delta_f = f_y - funcFitness(m_graph);
            std::pair<Node,Node> diff = getDifference(y, m_graph);
            if(delta_f >= 0)
                m_T.push_back(diff);
            if(f_y < m_fmin){
                m_fmin = f_y;
                m_xmin = y.copyGraph();
            }
        }
        i++;
    }
    while(!C.empty() && (i < m_nmax));
    //std::cout << m_xmin.getNodeNb() << std::endl;
}

TabouAlgorithm::~TabouAlgorithm() {
    // TODO vérifier de delete le contenu de la liste m_T (pas encore défini)
}

