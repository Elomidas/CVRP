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
DistanceNode::DistanceNode() : m_nodeIndex(0), m_size(1), m_distances(nullptr) {
    m_distances = new double[1];
    deleted  = false;
}

DistanceNode::DistanceNode(unsigned int size) : m_nodeIndex(size - 1), m_size(size), m_distances(nullptr) {
    m_distances = new double[size];
    for(unsigned int i(0); i < size; i++) {
        m_distances[i] = 0;
    }
    deleted = false;
}

/**
 * Destructor
 */
DistanceNode::~DistanceNode() {
    if(m_distances != nullptr) {
        //TODO : Remove memory leak
        //delete[] m_distances;
        m_distances = nullptr;
    }
}

/**
 * Get a reference of a distance.
 * Regroup checks for accessor/mutator
 * @param nodeIndex Index of the node which one measure the distance
 * @return Distance between the nodes
 */
double& DistanceNode::getDistanceReference(const unsigned int nodeIndex) {
    assert(nodeIndex < m_nodeIndex);
    return m_distances[nodeIndex];
}
const double& DistanceNode::getDistanceReference(const unsigned int nodeIndex) const {
    assert(nodeIndex < m_nodeIndex);
    return m_distances[nodeIndex];
}

/**
 * Set the distance between two nodes
 * @param nodeIndex Index of the second nodes
 * @param distance Distance between the nodes
 */
void DistanceNode::setDistance(const unsigned int nodeIndex, const double &distance) {
    getDistanceReference(nodeIndex) = distance;
}

/**
 * Get the distance between two nodes
 * @param nodeIndex Index of the second Node
 * @return Distance between the nodes.
 */
const double& DistanceNode::getDistance(const unsigned int nodeIndex) const {
    return getDistanceReference(nodeIndex);
}
