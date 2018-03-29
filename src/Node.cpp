//
// Created by elomidas on 14/03/18.
//

#include "../include/Node.h"

/**
 * Default constructor
 */
Node::Node() : m_id(0), m_quantity(0), m_used(false){
    //Nothing
}

/**
 * Constructor with parameters
 * @param id        Node's id
 * @param quantity  Quantity of products on this node
 */
Node::Node(const unsigned int id, const unsigned int quantity) : m_id(id), m_quantity(quantity) {
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

bool Node::getUsed() const {
    return m_used;
}

void Node::setUsed(const bool used) {
    m_used = used;
}

