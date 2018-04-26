//
// Created by bastien on 26/04/18.
//

#include "../include/TabouAlgorithm.h"

using namespace std;

TabouAlgorithm::TabouAlgorithm() : m_xmin(), m_nmax(0) {
    m_x = vector<Node>();
    //TODO chargement des noeuds dans cette liste
    m_T = vector<int>();
    /*
    m_xmin.setId(m_x[0].getId());
    m_xmin.setQuantity(m_xo.getQuantity());
    m_xmin.setX(m_xo.getX());
    m_xmin.SetY(m_xo.getY());
    */
    //TODO ajouter calcul fmin=f(xmin)
    //this->f_min =
}

void TabouAlgorithm::lancerAlgo() {
    int i=0;
    vector<Node> C;
    do{

        i++;
    }
    while(!C.empty() || (i = m_nmax));
}

