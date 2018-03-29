//
// Created by elomidas on 28/03/18.
//

#include "../include/TruckStep.h"

/**
 * Constructor
 * @param node Node on the truck's path
 */
TruckStep::TruckStep(const Node &node) : m_next(nullptr), m_node(node) {
    //Nothing
}

/**
 * Destructor
 */
TruckStep::~TruckStep() {
    if(m_next != nullptr) {
        delete m_next;
    }
}

/**
 * Get node's dd.
 * @return node's id
 */
unsigned int TruckStep::getId() {
    return m_node.getId();
}

/**
 * Add a node at the end of the truck's path.
 * @param node Node's to add
 */
void TruckStep::add(const Node &node) {
    if(hasNext()) {
        m_next->add(node);
    } else {
        m_next = new TruckStep(node);
    }
}

/**
 * Add a node at the specific index on truck's path.
 * If specified index is higher than truck's path's length, add the node at the end.
 * @param index Index of where to add the node
 * @param node  Node to add
 */
void TruckStep::addIndex(const unsigned int index, const Node &node) {
    if(hasNext() && (index > 0)) {
        m_next->addIndex(index-1, node);
    } else {
        setNext(new TruckStep(node));
    }
}

/**
 * Set the state coming just after this one on truck's path.
 * @param truckState Next state
 */
void TruckStep::setNext(TruckStep *truckState) {
    if(hasNext()) {
        truckState->setNext(m_next);
    }
    m_next = truckState;
}

/**
 * Get the state coming just after this one on truck's path.
 * @return Next state (nullptr if there isn't any)
 */
TruckStep* TruckStep::getNext() {
    return m_next;
}

/**
 * Check if there is a next state.
 * @return true if there is a next state, false else
 */
bool TruckStep::hasNext() {
    return m_next != nullptr;
}

/**
 * Get the distance the truck has to drive to hit the road from this node to the end of his path.
 * Count the distance between the last step and truck's origin.
 * @param origin 
 * @param distancesMatrix 
 * @return 
 */
unsigned long TruckStep::getDistance(const Node &origin, const DistancesMatrix &distancesMatrix) {
    if(hasNext()) {
        return distancesMatrix.getDistance(getId(), m_next->getId()) + m_next->getDistance(origin, distancesMatrix);
    }
    return distancesMatrix.getDistance(getId(), origin.getId());
}

