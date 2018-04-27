//
// Created by bastien on 26/04/18.
//

#include <iostream>
#include "../include/TabouAlgorithm.h"

using namespace std;

TabouAlgorithm::TabouAlgorithm() : m_xmin(), m_nmax(0), m_T(), m_fmin(0) {
    //Nothing
}

void TabouAlgorithm::lancerAlgo() {
    int i=0;
    Node xo = m_graph.getNodes()[0];
    m_xmin = xo;
    vector<Node> C;
    do{
        for(unsigned int j=0;j<C.size();j++)
            C.push_back(C.at(j));
        if(!C.empty()){

        }
        i++;
    }
    while(!C.empty() || (i = m_nmax));
    cout << m_xmin.getId();
}

/**
 *
 * @param act noeud actuel
 * @return tous les noeuds appartenant au voisinage du noeud actuel
 */
vector<Node> TabouAlgorithm::getVoisinage(Node act) {
    vector<Node> ret;
    ret.push_back(act);
    return ret;
}

TabouAlgorithm::~TabouAlgorithm() {
    // TODO vérifier de delete le contenu de la liste m_T (pas encore défini)
}

