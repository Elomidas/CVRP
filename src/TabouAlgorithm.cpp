//
// Created by bastien on 26/04/18.
//

#include <iostream>
#include <cfloat>
#include "../include/TabouAlgorithm.h"
#include "../include/Graphviz.h"

/**
 * Default constructor
 */
TabouAlgorithm::TabouAlgorithm() : m_xmin(), m_T(), m_fmin(0) {
    //Nothing
}

/**
 * launching Tabou algorithm
 */
void TabouAlgorithm::lancerAlgo() {
    m_graph.buildRandomSolution();
    m_xmin = m_graph.getSolution();
    m_fmin = m_xmin.getCost();
    std::cout << "Graphe de base" << std::endl << m_xmin.toString() << std::endl << std::endl;

    unsigned int i(0);
    std::vector<Graph> V; // voisinage
    std::vector<ElementaryTransformation> transfos; // liste des transformations élementaires
    bool end = false;

    do{
        V = m_graph.getVoisinage(m_T, transfos);
        if(!V.empty()){
            double y_fmin(DBL_MAX); // valeur de y
            unsigned int y_jmin(0); // indice où se trouve y dans la liste C

            for(unsigned int j(0); j < V.size(); j++) {
                double cost(V[j].getCost());
                if(cost < y_fmin) {
                    y_fmin = cost;
                    y_jmin = j;
                }
            }

            double delta_f = y_fmin - m_graph.getCost();
            if(delta_f >= 0)
                addList(transfos[y_jmin]);
            if(y_fmin < m_fmin){
                m_fmin = y_fmin;
                m_xmin = V[y_jmin].getSolution();
            }

            m_graph.loadSolution(V[y_jmin].getSolution());
            std::cout << "passage : " << i <<std::endl << m_graph.getSolution().toString() << std::endl <<std::endl;
        }
        i++;
        if(V.empty()) {
            end = true;
        } else {
            V.clear();
        }
        transfos.clear();
    }
    while(!end && (i < m_nmax));
}

/**
 * Add a transformation into Tabou list
 * @param transformation
 */
void TabouAlgorithm::addList(ElementaryTransformation transformation){
    if(m_T.size() == M_TAILLE){
        m_T.pop_back();
    }
    m_T.push_front(transformation);
}

/**
 * Destructor
 */
TabouAlgorithm::~TabouAlgorithm() {
    if(!m_T.empty()) {
        m_T.clear();
    }
}

Solution TabouAlgorithm::getMini() const {
    return m_xmin;
}

void TabouAlgorithm::display() {
    m_graph.loadSolution(m_xmin);
    Graphviz::getImg(m_graph);
}

