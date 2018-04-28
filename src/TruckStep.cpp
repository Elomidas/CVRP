//
// Created by elomidas on 28/03/18.
//

#include <cassert>
#include "../include/TruckStep.h"

/**
 * Constructor
 * @param node Node on the truck's path
 */
TruckStep::TruckStep(graph::Node &node) : m_next(nullptr), m_node(node) {
    assert(!m_node.getUsed());
    //m_node.setUsed(nullptr);
}

TruckStep::TruckStep(const TruckStep &source) : m_node(source.m_node) {
    m_next = new TruckStep(source.m_next->m_node);
}


/**
 * Destructor
 */
TruckStep::~TruckStep() {
    delete m_next;
    //m_node.setUsed(nullptr);
}

/**
 * Get node's id.
 * @return node's id
 */
unsigned int TruckStep::getId() const {
    return m_node.getId();
}

/**
 * Add a node at the end of the truck's path.
 * @param node Node's to add
 */
void TruckStep::add(graph::Node &node) {
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
void TruckStep::addByIndex(unsigned int index, graph::Node &node) {
    if(hasNext() && (index > 0)) {
        m_next->addByIndex(index - 1, node);
    } else {
        setNext(new TruckStep(node));
    }
}

/**
 * Set the state coming just after this one on truck's path.
 * If this step already add a next step, put the new one between this one and the old one.
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
TruckStep* TruckStep::getNext() const {
    return m_next;
}

graph::Node& TruckStep::getNode() {
    return m_node;
}

/**
 * Check if there is a next state.
 * @return true if there is a next state, false else
 */
bool TruckStep::hasNext() const {
    return m_next != nullptr;
}

/**
 * Get the distance the truck has to drive to hit the road from this node to the end of his path.
 * Count the distance between the last step and truck's origin.
 * @param origin            Truck's path origin
 * @param distancesMatrix   Matrix containing the distances between nodes
 * @return Distance the truck has to drive from this step to the end of its path.
 */
unsigned long TruckStep::getDistance(const graph::Node &origin, const graph::DistancesMatrix &distancesMatrix) const {
    if(hasNext()) {
        return distancesMatrix.getDistance(getId(), m_next->getId()) + m_next->getDistance(origin, distancesMatrix);
    }
    return distancesMatrix.getDistance(getId(), origin.getId());
}

/**
 * Check if a node is in the truck's path.
 * @param id Id of the node to search
 * @return Index of the node if it's in the path, -1 else
 */
int TruckStep::hasNode(const unsigned int id) const {
    if(id == m_node.getId()) {
        return 0;
    }
    if(hasNext()) {
        int res(m_next->hasNode(id));
        if(res == -1) {
            return res;
        }
        return res + 1;
    }
    return -1;
}

/**
 * Return the number of products the truck has to carry from this step to the end of its path.
 * @return Number of products to carry.
 */
unsigned int TruckStep::getLoad() const {
    if(hasNext()) {
        return m_node.getQuantity() + m_next->getLoad();
    }
    return m_node.getQuantity();
}

/**
 * Delete next node from truck's path.
 * @return Deleted node's capacity
 */
unsigned int TruckStep::delNext() {
    TruckStep *truckStep = m_next;
    unsigned int load(m_next->getLoad());
    m_next = m_next->getNext();
    delete truckStep;
    return load;
}

/**
 * Remove node with specified id from truck's path.
 * @param id Id of the node to remove from path
 * @return Deleted node's capacity
 */
unsigned int TruckStep::delById(const unsigned int id) {
    if(hasNext()) {
        if(m_next->getId() == id) {
            return delNext();
        }
        return m_next->delById(id);
    }
    return 0;
}

/**
 * Remove node at specified index from truck's path.
 * @param index Index of the node to delete.
 * @return Deleted node's capacity
 */
unsigned int TruckStep::delIndex(const unsigned int index) {
    if(hasNext()) {
        if(index == 1) {
            return delNext();
        }
        return m_next->delIndex(index-1);
    }
}

/**
 * Replace next node on truck's path by the specified one.
 * @param node Node that will replace the old one
 * @return Deleted node's capacity
 */
unsigned int TruckStep::replaceNext(graph::Node &node) {
    TruckStep *old = m_next;
    unsigned int load(m_next->getLoad());
    m_next = new TruckStep(node);
    m_next->setNext(old->getNext());
    old->m_next = nullptr;
    delete old;
    return load;
}

/**
 * Replace node with the specified id on truck's path by the specified one.
 * If there isn't any node matching the given id, do nothing.
 * @param id    Id of the node to replace
 * @param node  Node to add on the truck's path
 * @return Deleted node's capacity
 */
unsigned int TruckStep::replaceById(const unsigned int id, graph::Node &node) {
    if(hasNext()){
        if(m_next->getId() == id) {
            return replaceNext(node);
        }
        return m_next->replaceById(id, node);
    }
    return 0;
}

/**
 * Replace node at the specified index on truck's path by the specified one.
 * If index is greater than path's length, do nothing.
 * @param index Index of the node to replace
 * @param node  Node to add on the truck's path
 * @return Deleted node's capacity
 */
unsigned int TruckStep::replaceByIndex(unsigned int index, graph::Node &node) {
    if(hasNext()){
        if(index == 1) {
            return replaceNext(node);
        }
        return m_next->replaceByIndex(index-1, node);
    }
    return 0;
}
