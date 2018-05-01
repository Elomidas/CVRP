//
// Created by bastien on 14/03/2018.
//

#include <iostream>
#include <fstream>
#include <utility>
#include <cassert>
#include <random>
#include <cstdlib>
#include <climits>

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
Graph::Graph(std::vector<Node> nodes) :
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
    for(Truck t : m_trucks) {
        if(!t.isValid()) {
            std::clog << "Truck " << t.getIndex() << " isn't valid." << std::endl;
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
    for(unsigned int i(0); i < m_truckNb; i++) {
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
    bool fail(false);

    do {
        fail = false;
        if (!m_trucks.empty()) {
            m_trucks.clear();
        }

        for (unsigned int i(0); i < m_truckNb; i++) {
            truckIDs.emplace_back(i);
            ranges.emplace_back(std::uniform_int_distribution<int>(0, m_truckNb - i));
            m_trucks.emplace_back(Truck(m_nodes[0], (i + 1)));
        }


        for (unsigned int i(1); (i < m_nodeNb) && !fail; i++) {
            unsigned int rand;
            bool stop(false);
            std::vector<unsigned int> ids(truckIDs);
            currentRangeIndex = 0;
            do {
                int irand(std::rand());
                rand = static_cast<unsigned int>(irand % ids.size());
                rand = ids[rand];
                m_trucks[rand].computeLoad();
                if (m_trucks[rand].getAvailableCapacity() > m_nodes[i].getQuantity()) {
                    stop = true;
                    fail = false;
                } else {
                    unsigned int j(0);
                    for (j = 0; (j < ids.size()) && (ids[j] != rand); j++);
                    if (j < ids.size()) {
                        if (ids.size() > 1) {
                            ids.erase(ids.begin() + j);
                            currentRangeIndex++;
                        } else {
                            stop = true;
                            fail = true;
                        }
                    }
                }
            } while (!stop);
            if(!fail) {
                m_trucks[rand].addState(m_nodes[i]);
            }
        }
    } while(fail);

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
    assert(truck <= m_trucks.size());
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
    assert(truck > 0);
    assert(truck <= m_truckNb);
    m_trucks[truck-1].addState(m_nodes[node]);
    m_trucks[truck-1].addStateByIndex(index,m_nodes[node]);
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

void Graph::loadGenetic(const std::vector<unsigned int> &vector) {
    if(!m_trucks.empty()) {
        m_trucks.clear();
    }
    m_trucks.emplace_back(Truck(m_nodes[0], 1));
    unsigned int currentTruck(0);
    for (unsigned int step : vector) {
        if(m_trucks[currentTruck].getAvailableCapacity() < m_nodes[step].getQuantity()) {
            m_trucks.emplace_back(Truck(m_nodes[0], currentTruck + 2));
            currentTruck++;
        }
        addNodeToTruck(step, currentTruck+1);
    }
}

/**
 * Retrieve informations from a file's line
 * @param line  Line from the file.
 * @param res   List of the intels retrieved.
 */
std::vector<unsigned int> Graph::splitLine(std::string &line) {
    std::vector<unsigned int> res;
    std::string delimiter = ";";
    unsigned int i;
    size_t pos = 0;
    for(i = 0; ((pos = line.find(delimiter)) != std::string::npos); i++) {
        res.emplace_back(atoi(line.substr(0, pos).c_str()));
        line.erase(0, pos + delimiter.length());
    }
    res.emplace_back(atoi(line.c_str()));
    return res;
}

/**
 * Convert a string into an unsigned int.
 * @param number String to convert.
 * @return Unsigned int obtained.
 */
unsigned int Graph::atoi(const std::string &number) {
    char *endptr;
    long val;

    errno = 0;
    val = strtol(number.c_str(), &endptr, 10);

    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
        || (errno != 0 && val == 0)) {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    if (endptr == number) {
        std::cerr << "No digits were found in '" << number << "'." << std::endl;
        exit(EXIT_FAILURE);
    }
    return static_cast<unsigned int>(val);
}

std::vector<unsigned int> Graph::getGenetic() const {
    std::vector<unsigned int> res;
    for (const auto &m_truck : m_trucks) {
        std::vector<unsigned int> vect = m_truck.toVector();
        for(unsigned int j(1); j < vect.size() - 1; j++) {
            res.emplace_back(vect[j]);
        }
    }
    return res;
}

double Graph::getCost() const {
    double cost(0);
    for(Truck t : m_trucks) {
        cost += t.getDistance(m_distances);
    }
    return cost;
}
