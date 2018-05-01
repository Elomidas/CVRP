//
// Created by bastien on 01/05/18.
//

#include "../include/ElementaryTransformation.h"

/**
 * Default constructor
 */
ElementaryTransformation::ElementaryTransformation() : m_type(0), m_firstNode(0), m_secondNode(0), m_Index(0), m_Truck(0) {
    // Nothing
}

/**
 * Destructor
 */
ElementaryTransformation::~ElementaryTransformation() {
    // Nothing
}

/**
 * Set ElementaryTransformation object when inverting two nodes
 * @param type
 * @param firstNode
 * @param secondNode
 */
void ElementaryTransformation::setTransfo(unsigned int type, unsigned int firstNode, unsigned int secondNode) {
    m_type = type;
    m_firstNode = firstNode;
    m_secondNode = secondNode;
}

/**
 * Set ElementaryTransformation when mooving a node
 * @param type
 * @param firstNode
 * @param truck
 * @param index
 */
void ElementaryTransformation::setTransfo(unsigned int type, unsigned int firstNode, unsigned int truck,
                                          unsigned int index) {
    m_type = type;
    m_firstNode = firstNode;
    m_Truck = truck;
    m_Index = index;
}
