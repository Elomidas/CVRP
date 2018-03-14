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

int** Graph::getDistances() {return m_distances;}

int Graph::getDistance(Node start, Node end) {
    return m_distances[start.getId()][end.getId()];
}

Node* Graph::getNodes() {return m_nodes;}

vector<Truck> Graph::getTrucks() {return m_trucks;}

void Graph::setDistances(int **distances) {m_distances = distances;}

void Graph::setDistances(Node start, Node end, int value) {
    m_distances[start.getId()][end.getId()] = value;
    m_distances[end.getId()][start.getId()] = value;
}

void Graph::setNodes(Node *nodes) {m_nodes = nodes;}

void Graph::setTrucks(vector <Truck> trucks) {m_trucks = trucks;}