//
// Created by elomidas on 28/03/18.
//

#include <cassert>
#include "../include/DistanceNode.h"

unsigned int DistanceNode::m_quantity = 0;

/**
 * Default constructor
 */
DistanceNode::DistanceNode() : m_nodeIndex(m_quantity) {
    m_distances = new unsigned long[m_quantity];
    for(unsigned int i(0); i < m_quantity; i++) {
        m_distances[i] = 0;
    }
    m_quantity++;
}

/**
 * Destructor
 */
DistanceNode::~DistanceNode() {
    delete[] m_distances;
}

/**
 * Get a reference of a distance.
 * Regroup checks for accessor/mutator
 * @param nodeIndex Index of the node which one measure the distance
 * @return Distance between the nodes
 */
unsigned long& DistanceNode::getDistanceReference(const unsigned int nodeIndex) {
    assert(nodeIndex < m_nodeIndex);
    return m_distances[nodeIndex];
}

/**
 * Set the distance between two nodes
 * @param nodeIndex Index of the second nodes
 * @param distance Distance between the nodes
 */
void DistanceNode::setDistance(const unsigned int nodeIndex, const unsigned long distance) {
    getDistanceReference(nodeIndex) = distance;
}

/**
 * Get the distance between two nodes
 * @param nodeIndex Index of the second Node
 * @return Distance between the nodes.
 */
unsigned long DistanceNode::getDistance(const unsigned int nodeIndex) {
    return getDistanceReference(nodeIndex);
}