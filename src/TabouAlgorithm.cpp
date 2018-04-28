//
// Created by bastien on 26/04/18.
//

#include <iostream>
#include "../include/TabouAlgorithm.h"


TabouAlgorithm::TabouAlgorithm() : m_xmin(0), m_nmax(10), m_T(), m_fmin(0) {
    //Nothing
}

void TabouAlgorithm::lancerAlgo() {
    int i=0;
    Graph xo = getRandomSolution();
    m_xmin = xo;
    std::vector<Graph> C;
    do{
        C = getVoisinage(m_T);
        if(!C.empty()){

        }
        i++;
    }
    while(!C.empty() || (i = m_nmax));
    std::cout << m_xmin.getNodeNb() << std::endl;
}

TabouAlgorithm::~TabouAlgorithm() {
    // TODO vérifier de delete le contenu de la liste m_T (pas encore défini)
}

