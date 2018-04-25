//
// Created by elomidas on 14/03/18.
//

#include "../include/Node.h"

/**
 * Default constructor
 */
Node::Node() : m_id(0), m_quantity(0), m_x(0), m_y(0) {
    m_used = nullptr;
}

/**
 * Constructor with parameters
 * @param id        Node's id
 * @param quantity  Quantity of products on this node
 */
Node::Node(const unsigned int id, const unsigned int quantity) : m_id(id), m_quantity(quantity), m_x(0), m_y(0) {
    m_used = nullptr;
}

/**
 * Constructor with more parameters
 * @param id        Node's id
 * @param quantity  Quantity of products on this node
 * @param x         Position X of the node
 * @param y         Position Y of the node
 */
Node::Node(const unsigned int id, const unsigned int quantity, const unsigned int x, const unsigned int y) :
        m_id(id), m_quantity(quantity), m_x(x), m_y(y) {
    m_used = nullptr;
}

unsigned int Node::getId() const {
    return m_id;
}

void Node::setId(const unsigned int id) {
    m_id = id;
}

unsigned int Node::getQuantity() const {
    return m_quantity;
}

void Node::setQuantity(const unsigned int quantity) {
    m_quantity = quantity;
}

bool Node::getUsed() const {
    return (m_used != nullptr);
}

void Node::setUsed(Truck *step) {
    m_used = step;
}

