//
// Created by bastien on 26/04/18.
//

#include <iostream>
#include "../include/TabouAlgorithm.h"


TabouAlgorithm::TabouAlgorithm() : m_xmin(), m_nmax(10), m_T(), m_fmin(0) {
    //Nothing
}

const std::vector<Graph> TabouAlgorithm::getVoisinage(Graph &graph) {
    //TODO fonction à tester
    //TODO ajouter liste tabou
    std::vector<Graph> voisinage = std::vector<Graph>();
    unsigned int node_nb, truck_nb;
    //int id_node1, id_node2;
    //bool next_line = false;
    for(unsigned int i(0); i<graph.getTrucksNb();i++){
        for(unsigned int j(1); j<graph.getTruck(i).getSize()-1;j++){
            std::vector<unsigned int> path1 = graph.getTruck(i).toVector();
            unsigned int node1 = path1.at(j);
            if(j == graph.getTruck(i).getSize()-2){
                node_nb = 1;
                truck_nb = i+1;
            }
            else{
                node_nb = j+1;
                truck_nb = i;
            }
            while(truck_nb<graph.getTrucksNb()){
                while(node_nb<graph.getTruck(truck_nb).getSize()-1){
                    std::vector<unsigned int> path2 = graph.getTruck(truck_nb).toVector();
                    unsigned int node2 = path2.at(node_nb);
                    voisinage.push_back(Graph(graph));
                    voisinage.at(voisinage.size()-1).invertNodes(node1, node2);
                    node_nb++;
                }
                node_nb=1;
                truck_nb++;
            }



            /*
            std::pair<unsigned int,unsigned int> test_tabou = std::make_pair(i ,j);

            if(std::find(listeTabou.begin(), listeTabou.end(), test_tabou) != test_tabou){
                Solution tmp = Solution(solution);
                reverse(tmp, i, j);
                voisinage.push_back(tmp);
            }
             */
        }
    }
    return std::vector<Graph>();
}

const std::pair<unsigned int, unsigned int> TabouAlgorithm::getDifference(const Solution s1, const Solution s2) {
    //TODO définir la fonction
    return std::pair<unsigned int, unsigned int>();
}

void TabouAlgorithm::lancerAlgo() {
    //m_graph.buildRandomSolution();
    //Graph x(m_graph);
    //m_xmin = x.getSolution();
    //m_fmin = m_xmin.getCost();
    //std::cout << m_xmin.toString() << std::endl << std::endl;
    //std::cout << m_fmin << std::endl;
    /*
    unsigned int i(0);
    std::vector<Graph> C;
    C = getVoisinage(x, m_T);

    do{
        C = getVoisinage(x, m_T);
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

