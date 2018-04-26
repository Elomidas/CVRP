//
// Created by bastien on 14/03/2018.
//

#include <iostream>
#include <fstream>
#include <utility>
#include "../include/Graph.h"

using namespace graph;

Graph::Graph(const unsigned int nodeNb) : m_trucks(), m_nodeNb(nodeNb), m_distances(m_nodeNb) {
    m_nodes = new Node[nodeNb];
}

Graph::Graph(std::queue<Node> &nodes) :
        m_trucks(), m_nodeNb(static_cast<unsigned int>(nodes.size())), m_distances(m_nodeNb) {
    std::clog << "Create Graph from a " << m_nodeNb << " Node queue" << std::endl;
    m_nodes = new Node[m_nodeNb];
    for(unsigned int i(0); i < m_nodeNb; i++) {
        Node n(nodes.front());
        m_nodes[i] = n;
        nodes.pop();
    }
    m_distances.generateDistanceFromCoordinates(m_nodes);
}

Graph::~Graph() {
    if(m_nodes != nullptr) {
        delete[] m_nodes;
        m_nodes = nullptr;
    }
    if(!m_trucks.empty()) {
        m_trucks.clear();
    }
    m_nodeNb = 0;
}

DistancesMatrix& Graph::getDistances() {return m_distances;}

const double& Graph::getDistance(const Node &start, const Node &end) const {
    return getDistance(start.getId(), end.getId());
}

const double& Graph::getDistance(const unsigned int start, const unsigned int end) const {
    return m_distances.getDistance(start, end);
}

Node* Graph::getNodes() {return m_nodes;}

std::vector<Truck> Graph::getTrucks() {return m_trucks;}

void Graph::setDistances(const Node& start, const Node& end, const unsigned long &value) {
    m_distances.setDistance(start.getId(), end.getId(), value);
}

void Graph::setNodes(Node *nodes) {m_nodes = nodes;}

void Graph::setTrucks(std::vector <Truck> trucks) {
    m_trucks = std::move(trucks);
}
