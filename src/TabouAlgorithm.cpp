//
// Created by bastien on 26/04/18.
//

#include <iostream>
#include "../include/TabouAlgorithm.h"


TabouAlgorithm::TabouAlgorithm() : m_xmin(), m_nmax(10), m_T(), m_fmin(0) {
    //Nothing
}

const std::pair<unsigned int, unsigned int> TabouAlgorithm::getDifference(const Solution s1, const Solution s2) {
    //TODO définir la fonction
    return std::pair<unsigned int, unsigned int>();
}

void TabouAlgorithm::lancerAlgo() {
    m_graph.buildRandomSolution();
    Graph x(m_graph);
    m_xmin = x.getSolution();
    m_fmin = m_xmin.getCost();
    std::cout << m_xmin.toString() << std::endl << std::endl;
    std::cout << m_fmin << std::endl;

    unsigned int i(0);
    std::vector<Graph> C;
    //C = x.getVoisinage();
    /*
    do{
        C = getVoisinage(x);
        if(!C.empty()){
            Graph y(C.at(0));
            double f_y = y.getCost();
            for(unsigned int j(1);j<C.size();j++){
                if(C[j].getCost() < f_y){
                    y = C.at(j);
                    f_y = y.getCost();
                }
            }
            double delta_f = f_y - x.getCost();
            std::pair<unsigned int, unsigned int> diff = getDifference(y, x);
            if(delta_f >= 0)
                m_T.push_back(diff);
            if(f_y < m_fmin){
                m_fmin = f_y;
                m_xmin = y.getSolution();
            }
            x = y;
        }
        i++;
    }
    while(!C.empty() && (i < m_nmax));
     */
    //std::cout << m_xmin.getNodeNb() << std::endl;

}

TabouAlgorithm::~TabouAlgorithm() {

    if(!m_T.empty()) {
        m_T.clear();
    }

}

