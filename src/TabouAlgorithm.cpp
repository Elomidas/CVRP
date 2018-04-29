//
// Created by bastien on 26/04/18.
//

#include <iostream>
#include "../include/TabouAlgorithm.h"


TabouAlgorithm::TabouAlgorithm() : m_xmin(), m_nmax(10), m_T(), m_fmin(0) {
    //Nothing
}

void TabouAlgorithm::lancerAlgo() {
    Solution x = getRandomSolution();
    x.toString();
    m_xmin = Solution(x);
    m_fmin = m_xmin.getCost();
    int i=0;
    std::vector<Solution> C;
    do{
        C = getVoisinage(x, m_T);
        if(!C.empty()){
            Solution y(C.at(0));
            double f_y = y.getCost();
            for(int j=1;j<C.size();j++){
                if(C[j].getCost() < f_y){
                    y = C[j];
                    f_y = y.getCost();
                }
            }
            double delta_f = f_y - x.getCost();
            std::pair<Node,Node> diff = getDifference(y, x);
            if(delta_f >= 0)
                m_T.push_back(diff);
            if(f_y < m_fmin){
                m_fmin = f_y;
                m_xmin = Solution(y);
            }
        }
        i++;
    }
    while(!C.empty() && (i < m_nmax));
    //std::cout << m_xmin.getNodeNb() << std::endl;
}

TabouAlgorithm::~TabouAlgorithm() {
    for(std::pair<Node, Node> node : m_T){
        delete node.first;
        delete node.second;
        delete node;
    }
}

