//
// Created by elomidas on 14/03/18.
//

#include "../include/Node.h"

using namespace graph;

/**
 * Default constructor
 */
Node::Node() : m_id(0), m_quantity(0), m_x(0), m_y(0) {
    //m_used = nullptr;
}

/**
 * Constructor with parameters
 * @param id        Node's id
 * @param quantity  Quantity of products on this node
 */
Node::Node(const unsigned int id, const unsigned int quantity) : m_id(id), m_quantity(quantity), m_x(0), m_y(0) {
    //m_used = nullptr;
}

/**
 * Constructor with more parameters
 * @param id        Node's id
 * @param quantity  Quantity of products on this node
 * @param x         Position X of the node
 * @param y         Position Y of the node
 */
Node::Node(const unsigned int id, const unsigned int quantity, const unsigned int x, const unsigned int y) :
        m_id(id), m_quantity(quantity), m_x(x), m_y(y), m_used(0) {
    //Nothing
}

Node::Node(const graph::Node &old) :
        m_id(old.getId()), m_quantity(old.getQuantity()), m_x(old.getX()), m_y(old.getY()), m_used(old.getUser()) {
    //Nothing
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

/**
 *
 * @return booléen indiquant si le noeud est récolté par un camion ou non
 */
bool Node::getUsed() const {
    return (m_used != 0);
}

/**
 *
 * @return numéro du camion le récoltant, 0 si non utilisé
 */
unsigned int Node::getUser() const {
    return  m_used;
}

/**
 *
 * @param step camion assigné au noeud
 */
void Node::setUsed(const unsigned int step) {
    m_used = step;
}