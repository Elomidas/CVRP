//
// Created by bastien on 14/03/2018.
//

#include <iostream>
#include <fstream>
#include <utility>
#include <cassert>
#include <random>

#include "../include/Graph.h"

using namespace graph;

/**
 * Constructor with just a nodes'number
 * @param nodeNb Number of Nodes in the Graph
 */
Graph::Graph(const unsigned int nodeNb) : m_nodeNb(nodeNb), m_distances(nodeNb), m_qTotal(nodeNb),
                                          m_nodes(), m_trucks() {
    //Nothing
}

/**
 * Constructor from a queue of Nodes
 * @param nodes vector of all the Nodes in the Graph
 */
Graph::Graph(std::vector<Node> &nodes) :
        m_trucks(), m_nodeNb(static_cast<unsigned int>(nodes.size())), m_nodes(),
        m_distances(static_cast<unsigned int>(nodes.size())), m_qTotal(0) {
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
        m_truckNbMin(g.m_truckNbMin), m_truckNb(g.m_truckNb), m_nodes(), m_trucks() {
    std::clog << std::endl << "Copy graph" << std::endl;
    //Nodes copy
    for(unsigned int i(0); i < m_nodeNb; i++) {
        m_nodes.emplace_back(g.m_nodes[i]);
    }
    //Trucks copy
    for(unsigned int i(0); i < m_truckNb; i++) {
        m_trucks.emplace_back(Truck(g.m_trucks[i], m_nodes));
    }
    std::clog << "Graph copied" << std::endl;
}

/**
 * Destructor
 */
Graph::~Graph() {
    if(!m_trucks.empty()) {
        m_trucks.clear();
    }
    if(!m_nodes.empty()) {
        m_nodes.clear();
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
        if(!m_trucks[i].isValid()) {
            return false;
        }
    }
    return true;
}

/**
 * Find the minimum amount of Trucks needed for this graph.
 */
void Graph::computeTruckNbMin() {
    /* In order to be sure to have enough space for any elementary transformation, we had enough Trucks to
     * handle all Nodes capacity plus the max Nodes'capacity. By doing this, we're sure to be able to move any Node.
     */
    unsigned long total(m_qTotal);
    unsigned int maxQtt(0);
    for(unsigned int i(0); i  < m_nodeNb; i++) {
        maxQtt = (m_nodes[i].getQuantity() > maxQtt) ? m_nodes[i].getQuantity() : maxQtt;
    }
    total += maxQtt;
    m_truckNbMin = static_cast<unsigned int>((total / Truck::getCapacity()) + ((total % Truck::getCapacity()) > 0));

    setTrucksNumber(m_truckNbMin);
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
    for(unsigned int i(0); i < m_trucks.size(); i++) {
        s.addPath(m_trucks[i].toVector());
        cost += m_trucks[i].getDistance(m_distances);
    }
    s.setCost(cost);
    return s;
}

/**
 * Set the number of Trucks we're going to use
 * @param number
 */
void Graph::setTrucksNumber(unsigned int number) {
    assert(number >= m_truckNbMin);
    m_truckNb = number;

    if(m_trucks.size() != number) {
        if (!m_trucks.empty()) {
            m_trucks.clear();
        }

        for (unsigned int i(0); i < m_truckNb; i++) {
            m_trucks.emplace_back(Truck(m_nodes[0], i + 1));
        }
    }
}

/**
 * Build a random solution
 */
void Graph::buildRandomSolution() {
    std::vector<unsigned int> truckIDs;
    std::vector< std::uniform_int_distribution<int> > ranges;
    unsigned int currentRangeIndex;

    std::srand(static_cast<unsigned int>(time(0)));

    for(unsigned int i(0); i < m_truckNb; i++) {
        truckIDs.emplace_back(i);
        ranges.emplace_back(std::uniform_int_distribution<int>(0, m_truckNb-i));
    }

    for(unsigned int i(1); i < m_nodeNb; i++) {
        unsigned int rand;
        bool stop(false);
        std::vector<unsigned int> ids(truckIDs);
        currentRangeIndex = 0;
        do {
            rand = static_cast<unsigned int>(std::rand() % ids.size());
            rand = ids[rand];
            if(m_trucks[rand].getAvailableCapacity() > m_nodes[i].getQuantity()) {
                stop = true;
            } else {
                unsigned int j(0);
                for(j = 0; (j < ids.size()) && (ids[j] != rand); j++);
                if(j < ids.size()) {
                    ids.erase(ids.begin() + j);
                    currentRangeIndex++;
                }
            }
        } while(!stop);
        m_trucks[rand].addState(m_nodes[i]);
    }

    assert(isSolution());

}

/**
 * Add a Node to a Truck path
 * @param node  Node id
 * @param truck Truck id (first is 0)
 */
void Graph::addNodeToTruck(unsigned int node, unsigned int truck) {
    assert(node < m_nodeNb);
    assert(truck > 0);
    assert(truck <= m_truckNb);
    m_trucks[truck-1].addState(m_nodes[node]);
}

/**
 * Add a Node to a Truck path at the given index
 * @param node  Node id
 * @param truck Truck id (first is 0)
 * @param index Index on which add the Node
 */
void Graph::addNodeToTruck(unsigned int node, unsigned int truck, unsigned int index) {
    assert(node < m_nodeNb);
    assert(index < m_nodes.size());
    assert(truck > 0);
    assert(truck <= m_truckNb);
    m_trucks[truck-1].addState(m_nodes[node]);
    m_trucks[truck-1].addStateByIndex(index,m_nodes[node]);
}

void Graph::deleteNodeToTruck(unsigned int node, unsigned int truck){
    assert(node < m_nodeNb);
    assert(truck > 0);
    assert(truck <= m_truckNb);
    m_trucks[truck-1].removeStateById(node);
}

void Graph::deleteNodeToTruckByIndex(unsigned int index, unsigned int truck){
    assert(index < m_nodes.size());
    assert(truck > 0);
    assert(truck <= m_truckNb);
    m_trucks[truck-1].removeStateByIndex(index);
}

void Graph::invertNodes(unsigned int node1, unsigned int node2) {
    assert(node1 < m_nodeNb);
    assert(node2 < m_nodeNb);
    if(m_nodes[node1].getUser() == m_nodes[node2].getUser()){
        assert(m_trucks[m_nodes[node1].getUser()-1].hasNode(node1) >= 0);
        assert(m_trucks[m_nodes[node2].getUser()-1].hasNode(node2) >= 0);
        invertNodesByIndex(node1, node2, (unsigned int)m_trucks[m_nodes[node1].getUser()-1].hasNode(node1), (unsigned int)m_trucks[m_nodes[node1].getUser()-1].hasNode(node2));
    }
    else{
        unsigned int tmp = m_nodes[node2].getUser();
        m_trucks[m_nodes[node1].getUser()-1].replaceStateById(node1, m_nodes[node2]);
        m_trucks[tmp-1].replaceStateById(node2, m_nodes[node1]);
    }
}

void Graph::invertNodesByIndex(unsigned int node1, unsigned int node2, unsigned int index1, unsigned int index2) {
    assert(node1 < m_nodes.size());
    assert(node2 < m_nodes.size());
    unsigned int truck2(m_nodes[node2].getUser());
    m_trucks[m_nodes[node1].getUser()-1].replaceStateByIndex(index1, m_nodes[node2]);
    m_trucks[truck2-1].replaceStateByIndex(index2, m_nodes[node1]);
}


void Graph::loadSolution(const Solution &solution) {
    if(!m_trucks.empty()) {
        m_trucks.clear();
    }
    for(unsigned int i(0); i < solution.getPathNumber(); i++) {
        std::vector<unsigned int> indices = solution.getPath(i);
        m_trucks.emplace_back(Truck(m_nodes[0], i+1));
        //We don't handle first and last indices because it's the origin
        for(unsigned int j(1); j < indices.size() - 1; j++) {
            addNodeToTruck(indices[j], i+1);
        }
    }
}

/**
 * Compute and return the cost of the graph
 * @return cost of Trucks path
 */
double Graph::getCost() const {
    assert(isSolution());
    double cost = 0;
    for(unsigned int i(0); i < m_trucks.size(); i++) {
        cost += m_trucks[i].getDistance(m_distances);
    }
    return cost;
}


