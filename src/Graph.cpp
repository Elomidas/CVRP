//
// Created by bastien on 14/03/2018.
//

#include "../include/Graph.h"

Graph::Graph(int nodesNb) : m_trucks() {
    m_distances = new int*[nodesNb];
    for(int i=0;i<nodesNb;i++) {
        m_distances[i] = new int[];
    }
    m_nodes = new Node[nodesNb];
}

Graph::Graph(Node *nodes, int **distances) : m_trucks(), m_distances(distances), m_nodes(nodes) {
    //Nothing
}

Graph::Graph(Node *nodes, int **distances, vector<Truck> trucks) : m_trucks(trucks), m_distances(distances), m_nodes(nodes) {
    //Nothing
}

