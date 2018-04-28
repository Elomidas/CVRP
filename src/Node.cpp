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

Node::Node(const graph::Node &old) = default;

/**
 * Constructor with parameters
 * @param id        Node's id
 * @param quantity  Quantity of products on this node
 */
Node::Node(const unsigned int id, const unsigned int quantity) : m_id(id), m_quantity(quantity), m_x(0), m_y(0) {
    //m_user = nullptr;
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

void Node::display() const {
    std::clog << "Node details : {"
              << m_id << ","
              << m_quantity << ","
              << m_x << ","
              << m_y << ","
              << m_user << "}" << std::endl;
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
    return (m_user != 0);
}

/**
 *
 * @return numéro du camion le récoltant, 0 si non utilisé
 */
unsigned int Node::getUser() const {
    return  m_user;
}

/**
 *
 * @param step camion assigné au noeud
 */
void Node::setUsed(const unsigned int step) {
    m_user = step;
}