//
// Created by bastien on 14/03/2018.
//

#include <iostream>
#include <fstream>
#include <utility>
#include <cassert>
#include "../include/Graph.h"

using namespace graph;

/**
 * Constructor with just a nodes'number
 * @param nodeNb Number of Nodes in the Graph
 */
Graph::Graph(const unsigned int nodeNb) : m_nodeNb(nodeNb), m_distances(nodeNb), m_qTotal(nodeNb), m_nodes() {
    m_trucks = nullptr;
}

/**
 * Constructor from a queue of Nodes
 * @param nodes vector of all the Nodes in the Graph
 */
Graph::Graph(std::vector<Node> &nodes) :
        m_trucks(), m_nodeNb(static_cast<unsigned int>(nodes.size())), m_nodes(),
        m_distances(static_cast<unsigned int>(nodes.size())), m_qTotal(0) {
    m_trucks = nullptr;
    std::clog << "Create Graph from a " << m_nodeNb << " Node queue" << std::endl;
    for(unsigned int i(0); i < m_nodeNb; i++) {
        m_nodes.emplace_back(nodes[i]);
        m_qTotal += m_nodes.back().getQuantity();
    }
    computeTruckNbMin();
    m_distances.generateDistanceFromCoordinates(m_nodes);
}

/**
 * Copy constructor
 * @param g Graph to copy
 */
Graph::Graph(const Graph &g) :
        m_nodeNb(g.m_nodeNb), m_qTotal(g.m_qTotal), m_distances(g.m_distances),
        m_truckNbMin(g.m_truckNbMin), m_truckNb(g.m_truckNb), m_nodes() {
    std::clog << std::endl << "Copy graph" << std::endl;
    //Nodes copy
    for(unsigned int i(0); i < m_nodeNb; i++) {
        m_nodes.emplace_back(g.m_nodes[i]);
    }
    //Trucks copy
    //TODO
    m_trucks = new Truck*[m_truckNb];
    for(unsigned int i(0); i < m_truckNb; i++) {
        m_trucks[i] = new Truck(*g.m_trucks[i], m_nodes);
    }
    std::clog << "Graph copied" << std::endl;
}

/**
 * Destructor
 */
Graph::~Graph() {
    if(!m_nodes.empty()) {
        m_nodes.clear();
    }
    if(m_trucks != nullptr) {
        for(unsigned int i(0); i < m_truckNb; i++) {
            delete m_trucks[i];
            m_trucks[i] = nullptr;
        }
        delete[] m_trucks;
        m_trucks = nullptr;
        m_truckNb = 0;
    }
}

const double Graph::getDistance(const unsigned int start, const unsigned int end) const {
    return m_distances.getDistance(start, end);
}

/**
 * Check if the graph can be a solution (all Nodes are on a Truck's path and none of the Trucks overcome its capacity.
 * @return true if this graph is a solution, false else.
 */
bool Graph::isSolution() const {
    //Check if all nodes are used
    for(unsigned int i(0); i < m_nodeNb; i++) {
        if(!m_nodes[i].getUsed()) {
            return false;
        }
    }
    //Check that all trucks are correct
    for(unsigned int i(0); i < m_truckNb; i++) {
        if(!m_trucks[i]->isValid()) {
            return false;
        }
    }
    return true;
}

/**
 * Find the minimum amount of Trucks needed for this graph.
 */
void Graph::computeTruckNbMin() {
    //Add one truck to be sure to be able to operate some changes
    m_truckNbMin = static_cast<unsigned int>((m_qTotal / Truck::getCapacity()) + 1);
    m_truckNb = m_truckNbMin;
    m_trucks = new Truck*[m_truckNb];
    for(unsigned int i(0); i < m_truckNb; i++) {
        //Trucks have id >= 1
        m_trucks[i] = new Truck(m_nodes[0], i+1);
    }
}

/**
 * Get the number of Nodes in the Graph
 * @return Number of Nodes in the Graph
 */
const unsigned int Graph::getNodeNb() const {
    return m_nodeNb;
}

/**
 * Return a Solution object representing the Graph if it's a possible Solution.
 * @return Solution object representing the Graph.
 */
Solution Graph::getSolution() const {
    assert(isSolution());
    Solution s;
    unsigned long cost(0);
    for(unsigned int i(0); i < m_truckNb; i++) {
        s.addPath(m_trucks[i]->toVector());
        cost += m_trucks[i]->getDistance(m_distances);
    }
    s.setCost(cost);
    return s;
}


