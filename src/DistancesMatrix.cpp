//
// Created by elomidas on 28/03/18.
//

#include <cassert>
#include <cmath>

#include "../include/DistancesMatrix.h"

/**
 * Constructor
 * @param numberOfNodes Number of nodes in the graph
 */
DistancesMatrix::DistancesMatrix(const unsigned int numberOfNodes) : m_numberOfNodes(numberOfNodes) {
    DistanceNode::setQuantity(1);
    m_distances = new DistanceNode[numberOfNodes];
}

/**
 * Destructor
 */
DistancesMatrix::~DistancesMatrix() {
    delete[] m_distances;
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
    m_distances[first].setDistance(second, distance);
}

/**
 * Get distance between to nodes identified by index.
 * @param firstNodeIndex    First node's index
 * @param secondNodeIndex   Second node's index
 * @return Distance between the nodes
 */
const unsigned long DistancesMatrix::getDistance(const unsigned int firstNodeIndex,
                                                  const unsigned int secondNodeIndex) const {
    unsigned int first(firstNodeIndex), second(secondNodeIndex);
    sortIndices(first, second);
    return m_distances[first].getDistance(second);
}

/**
 * Compute the distances between all nodes, thanks to their coordinates.
 * @param nodes List of all the nodes
 */
void DistancesMatrix::generateDistanceFromCoordinates(const Node* nodes) {
    Node n1, n2;
    for(unsigned int i(0); i < m_numberOfNodes; i++) {
        n1 = nodes[i];
        for(unsigned int j(0); j < i; j++) {
            n2 = nodes[j];
            m_distances[i].setDistance(j, computeDistance(n1, n2));
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

const unsigned long DistancesMatrix::computeDistance(const Node& n1, const Node& n2) {
    return (unsigned long)(sqrt(pow(n1.getX() - n2.getX(), 2) + pow(n1.getY() - n2.getY(), 2)));
}
