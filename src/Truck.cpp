//
// Created by elomidas on 28/03/18.
//

#include <cassert>
#include "../include/Truck.h"

/**
 * Constructor
 * @param origin Node used as truck's path's origin
 * @param index  Truck's index
 */
Truck::Truck(graph::Node &origin, const unsigned int index) : m_currentLoad(0), m_size(0), m_index(index),
                                                              m_origin(nullptr)
{
    //Make sure that origin isn't mark as used in order to allow TruckStep's construction
    origin.setUsed(0);
    m_origin = new TruckStep(origin, m_index);
}

/**
 * Copy constructor
 * @param old   Old Truck to copy
 * @param nodes New Nodes
 */
Truck::Truck(const Truck &old, std::vector<graph::Node> &nodes) :
        m_currentLoad(old.m_currentLoad), m_size(old.m_size), m_index(old.m_index) {
    m_origin = new TruckStep(*(old.m_origin), nodes, m_index);
}

/**
 * Copy constructor
 * @param old Truck to copy
 */
Truck::Truck(const Truck &old) :
        m_currentLoad(old.m_currentLoad), m_size(old.m_size), m_index(old.m_index) {
    m_origin = new TruckStep(*(old.m_origin));
}

/**
 * Destructor
 */
Truck::~Truck() {
    //Make sure that origin is always marked as used
    if(m_origin != nullptr) {
        graph::Node origin = m_origin->getNode();
        unsigned int user = origin.getUser();
        delete m_origin;
        m_origin = nullptr;
        origin.setUsed(user);
    }
}

/**
 * Get the truck's path length (starts and ends at origin node).
 * @param distancesMatrix Matrix containing distances between all nodes
 * @return Truck's path's distance
 */
double Truck::getDistance(const graph::DistancesMatrix &distancesMatrix) const {
    return m_origin->getDistance(m_origin->getNode(), distancesMatrix);
}

/**
 * Get the load needed by the truck to deliver every client on its path.
 * @return Load needed to deliver all clients on truck's path.
 */
unsigned int Truck::getTruckLoad() const {
    return m_currentLoad;
}

/**
 * Force to compute again the load needed to the truck and return it.
 * @return Load needed to deliver all clients on truck's path
 */
unsigned int Truck::getComputedLoad() {
    m_currentLoad = m_origin->getLoad();
    return getTruckLoad();
}

/**
 * Add a new node at the end of truck's path
 * @param node Node to add
 */
void Truck::addState(graph::Node &node) {
    m_origin->add(node);
    m_currentLoad += node.getQuantity();
    m_size++;
}

/**
 * Add a new node at the specified index on truck's path.
 * @param index Index at which adding the node
 * @param node  Node to add on truck's path
 */
void Truck::addStateByIndex(const unsigned int index, graph::Node &node) {
    m_origin->addByIndex(index, node);
    m_currentLoad += node.getQuantity();
    m_size++;
}

/**
 * Remove the node with the specified id from truck's path
 * @param id Id of the node to remove from truck's path
 */
void Truck::removeStateById(const unsigned int id) {
    m_currentLoad -= m_origin->delById(id);
    m_size--;
}

/**
 * Remove the node at the specified index from truck's path.
 * @param index Index of the node to remove from truck's path
 */
void Truck::removeStateByIndex(const unsigned int index) {
    m_currentLoad -= m_origin->delIndex(index);
    m_size--;
}

/**
 * Replace the node with the specified id from truck's path by the given node.
 * If there isn't any node with specified id on truck's path, it doesn't add the node.
 * @param id    Id of the node to replace
 * @param node  Node to add onto truck's path
 */
void Truck::replaceStateById(const unsigned int id, graph::Node &node) {
    unsigned int delta(m_origin->replaceById(id, node));
    if(delta != 0) {
        m_currentLoad -= delta;
        m_currentLoad += node.getQuantity();
    }
}

/**
 * Replace the node at the specified index from truck's path by the given node.
 * @param index Index of the node to delete.
 * @param node  Node to add to the path.
 */
void Truck::replaceStateByIndex(const unsigned int index, graph::Node &node) {
    assert(index > 0);
    assert(index <= m_size);
    m_currentLoad -= m_origin->replaceByIndex(index, node);
    m_currentLoad += node.getQuantity();
}

/**
 * Check if node with the specified id is on truck's path.
 * @param id Id of the node to search
 * @return -1 if node isn't on the path, its index else
 */
int Truck::hasNode(const unsigned int id) const {
    return m_origin->hasNode(id);
}

/**
 * Check if node with the specified id is on truck's path.
 * @param node Node to search
 * @return -1 if node isn't on the path, its index else
 */
int Truck::hasNode(const graph::Node &node) const {
    return hasNode(node.getId());
}

/**
 * Get truck's capacity
 * @return Truck's capacity
 */
unsigned int Truck::getCapacity() {
    return m_capacity;
}

/**
 * Check that this Truck doesn't have more items than it should.
 * @return true if this Truck is valid, false else.
 */
bool Truck::isValid() const {
    return (getTruckLoad() <= m_capacity);
}

/**
 * Get the number of steps on this Truck's path (without the last, that is the same as the first)
 * @return Number of steps on the Truck's path.
 */
unsigned int Truck::getSize() const {
    return m_origin->getSize();
}

/**
 * Get a vector representing the Truck's path
 * @return Vector representing the Truck's path
 */
std::vector<unsigned int> Truck::toVector() const {
    std::vector<unsigned int> result;
    if(m_origin != nullptr) {
        m_origin->toVector(result);
    }
    result.push_back(m_origin->getId());
    return result;
}

unsigned int Truck::getAvailableCapacity() const {
    return m_capacity - m_currentLoad;
}

