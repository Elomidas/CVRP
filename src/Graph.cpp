//
// Created by bastien on 14/03/2018.
//

#include "../include/Graph.h"

Graph::Graph(int nodeNb) : m_trucks(), m_nodeNb(nodeNb), m_distances(nodeNb) {
    m_nodes = new Node[nodeNb];
}
/*
Graph::Graph(int nodeNb, Node *nodes, int **distances) : m_trucks(), m_distances(distances), m_nodes(nodes), m_nodeNb(nodeNb) {
    //Nothing
}

Graph::Graph(int nodeNb, Node *nodes, int **distances, std::vector<Truck> trucks) : m_trucks(trucks), m_distances(distances), m_nodes(nodes), m_nodeNb(nodeNb) {
    //Nothing
}
*/
Graph::~Graph() {
    delete(m_nodes);
    m_trucks.clear();
    m_nodeNb = 0;
}

DistancesMatrix& Graph::getDistances() {return m_distances;}

unsigned long Graph::getDistance(Node start, Node end) {
    return m_distances.getDistance(start.getId(), end.getId());
}

Node* Graph::getNodes() {return m_nodes;}

std::vector<Truck> Graph::getTrucks() {return m_trucks;}
/*
void Graph::setDistances(int **distances) {m_distances = distances;}
*/
void Graph::setDistances(Node start, Node end, int value) {
    m_distances.setDistance(start.getId(), end.getId(), value);
}

void Graph::setNodes(Node *nodes) {m_nodes = nodes;}

void Graph::setTrucks(std::vector <Truck> trucks) {m_trucks = trucks;}