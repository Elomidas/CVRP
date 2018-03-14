//
// Created by elomidas on 14/03/18.
//

#include "../include/Node.h"

Node::Node() : m_id(0), m_quantity(0), m_used(false){
    //Nothing
}

/**
 *
 * @param id
 * @param quantity
 */
Node::Node(const unsigned int id, const unsigned int quantity) : m_id(id), m_quantity(quantity) {
    //Nothing
}

