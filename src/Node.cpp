//
// Created by elomidas on 14/03/18.
//

#include <iostream>
#include "../include/Node.h"

using namespace graph;

/**
 * Default constructor
 */
Node::Node() = default;

/**
 * Copy constructor
 * @param old
 */
Node::Node(const graph::Node &old) = default;

/**
 * Constructor with parameters
 * @param id        Node's id
 * @param quantity  Quantity of products on this node
 */
Node::Node(const unsigned int id, const unsigned int quantity) : m_id(id), m_quantity(quantity), m_x(0), m_y(0),
                                                                 m_user(0) {
    //Nothing
}

/**
 * Constructor with more parameters
 * @param id        Node's id
 * @param quantity  Quantity of products on this node
 * @param x         Position X of the node
 * @param y         Position Y of the node
 */
Node::Node(const unsigned int id, const unsigned int quantity, const unsigned int x, const unsigned int y) :
        m_id(id), m_quantity(quantity), m_x(x), m_y(y), m_user(0) {
    //Nothing
}

/**
 * Display Node's details.
 */
void Node::display() const {
    std::clog << "Node details : {"
              << m_id << ","
              << m_quantity << ","
              << m_x << ","
              << m_y << ","
              << m_user << "}" << std::endl;
}

/**
 * Get Node's ID.
 * @return ID of this Node.
 */
unsigned int Node::getId() const {
    return m_id;
}

/**
 * Get the quantity associated with this Node.
 * @return Get Node's quantity
 */
unsigned int Node::getQuantity() const {
    return m_quantity;
}

/**
 * Check if this Node is already on a Truck's path
 * @return true if the Node is on a Truck's path, false else.
 */
bool Node::getUsed() const {
    return (m_user != 0);
}

/**
 * Return the ID of the Truck on which path is this Node (ID >= 1)
 * @return ID of the Truck going through this node, 0 if there isn't any.
 */
unsigned int Node::getUser() const {
    return  m_user;
}

/**
 * Assign a Truck ID or 0 to this Node
 * @param step Truck's ID
 */
void Node::setUsed(const unsigned int step) {
    m_user = step;
}
