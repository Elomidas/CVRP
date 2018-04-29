//
// Created by elomidas on 28/03/18.
//

#include <cassert>
#include <iostream>
#include "../include/DistanceNode.h"

using namespace graph;

/**
 * Default constructor
 */
DistanceNode::DistanceNode() = default;

/**
 * Constructor with the number of Nodes in the graph
 * All distances will be set to 0
 * @param size Number of Nodes in the Graph
 */
DistanceNode::DistanceNode(unsigned int size) : m_size(size), m_nodeIndex(size - 1), m_distances() {
    for(unsigned int i(0); i < m_size; i++) {
        m_distances.emplace_back(0.0);
    }
}

/**
 * Copy constructor
 * @param old Graph to copy
 */
DistanceNode::DistanceNode(const DistanceNode &old) : m_size(old.m_size), m_nodeIndex(old.m_nodeIndex),
                                                      m_distances() {
    for(unsigned int i(0); i < m_size; i++) {
        m_distances.emplace_back(old.getDistance(i));
    }
}

/**
 * Destructor
 */
DistanceNode::~DistanceNode() {
    if(!m_distances.empty()) {
        m_distances.clear();
    }
}

/**
 * Get a reference of a distance.
 * Regroup checks for accessor/mutator
 * @param nodeIndex Index of the node which one measure the distance
 * @return Distance between the nodes
 */
const double DistanceNode::getDistance(const unsigned int nodeIndex) const {
    assert(nodeIndex <= m_nodeIndex);
    return m_distances[nodeIndex];
}

/**
 * Set the distance between two nodes
 * @param nodeIndex Index of the second nodes
 * @param distance Distance between the nodes
 */
void DistanceNode::setDistance(const unsigned int nodeIndex, const double &distance) {
    assert(nodeIndex <= m_nodeIndex);
    m_distances[nodeIndex] = distance;
}
