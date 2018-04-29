//
// Created by elomidas on 28/03/18.
//

#include <cassert>
#include <cmath>
#include <iostream>

#include "../include/DistancesMatrix.h"

using namespace graph;

/**
 * Constructor
 * @param numberOfNodes Number of nodes in the graph
 */
DistancesMatrix::DistancesMatrix(const unsigned int numberOfNodes) :
        m_numberOfNodes(numberOfNodes), m_distancesNodes() {
    for(unsigned int i(0); i < m_numberOfNodes; i++) {
        DistanceNode d(i+1);
        m_distancesNodes.emplace_back(d);
    }
}

/**
 * Copy constructor
 * @param old DistanceMatrix to copy
 */
DistancesMatrix::DistancesMatrix(const DistancesMatrix &old) :
        m_numberOfNodes(old.m_numberOfNodes), m_distancesNodes() {
    for(unsigned int i(0); i < m_numberOfNodes; i++) {
        m_distancesNodes.emplace_back(DistanceNode(old.m_distancesNodes[i]));
    }
}

/**
 * Destructor
 */
DistancesMatrix::~DistancesMatrix() {
    if(!m_distancesNodes.empty()) {
        m_distancesNodes.clear();
    }
}

/**
 * Sort indices to have 'first' greater than 'second'
 * @param first     First index
 * @param second    Second index
 */
void DistancesMatrix::sortIndices(unsigned int &first, unsigned int &second) const {
    if(first < second) {
        unsigned int tmp(first);
        first = second;
        second = tmp;
    }
}

/**
 * Explicit
 * @return Number of nodes in the graph
 */
unsigned int DistancesMatrix::getNumberOfNodes() const {
    return m_numberOfNodes;
}

/**
 * Set the distance between two nodes identified by index
 * @param firstNodeIndex    First node's index
 * @param secondNodeIndex   Second node's index
 * @param distance Distance between the nodes
 */
void DistancesMatrix::setDistance(const unsigned int firstNodeIndex,
                                  const unsigned int secondNodeIndex,
                                  const unsigned long &distance) {
    unsigned int first(firstNodeIndex), second(secondNodeIndex);
    sortIndices(first, second);
    m_distancesNodes[first].setDistance(second, distance);
}

/**
 * Get distance between to nodes identified by index.
 * @param firstNodeIndex    First node's index
 * @param secondNodeIndex   Second node's index
 * @return Distance between the nodes
 */
const double DistancesMatrix::getDistance(const unsigned int firstNodeIndex,
                                                  const unsigned int secondNodeIndex) const {
    unsigned int first(firstNodeIndex), second(secondNodeIndex);
    sortIndices(first, second);
    double v = m_distancesNodes[first].getDistance(second);
    return v;
}

/**
 * Compute the distances between all nodes, thanks to their coordinates.
 * @param nodes List of all the nodes
 */
void DistancesMatrix::generateDistanceFromCoordinates(const std::vector<Node> &nodes) {
    Node n1, n2;
    double d;
    for(unsigned int i(0); i < m_numberOfNodes; i++) {
        n1 = nodes[i];
        for(unsigned int j(0); j < i; j++) {
            n2 = nodes[j];
            d = computeDistance(n1, n2);
            std::clog << "=> [" << i << "," << j << "] : " << d << std::endl;
            m_distancesNodes[i].setDistance(j, d);
            assert(d == m_distancesNodes[i].getDistance(j));
        }
    }
}

/**
 * Check that each function of this class is correctly running. Shall be launch with valgrind.
 * Check all functions from this class and all functions from class DistanceNode.
 * @param computeDistance   Pointer on a function that compute distance between two nodes. 
 *                          Function has to take two unsigned int as parameters and return an unsigned long.
 *                          Function has to be determinist.
 *                          You must have f(i,j)=f(j,i).
 * @param numberOfNodes     Number of nodes in the graph
 * @return true if function ends without error
 */
bool DistancesMatrix::test(unsigned long (*computeDistance)(const unsigned int, const unsigned int),
                          const unsigned int size) {
    auto *matrix = new DistancesMatrix(size);
    assert(matrix->getNumberOfNodes() == size);
    //Matrix filling
    for(unsigned int i(0); i < size; i++) {
        for(unsigned int j(0); j < i; j++) {
            matrix->setDistance(j, i, computeDistance(i, j));
        }
    }
    //Data retrieving check
    for(unsigned int i(0); i < size; i++) {
        for(unsigned int j(0); j < i; j++) {
            assert(matrix->getDistance(i, j) == matrix->getDistance(j, i));
            assert(matrix->getDistance(i, j) == computeDistance(i, j));
        }
    }
    delete matrix;
    return true;
}

/**
 * Compute the cartesian distance between two Nodes
 * @param n1 First Node
 * @param n2 Second Node
 * @return Cartesian distance between the Nodes
 */
const double DistancesMatrix::computeDistance(const Node& n1, const Node& n2) {
    double x1(n1.getX()),
            x2(n2.getX()),
            y1(n1.getY()),
            y2(n2.getY());
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
