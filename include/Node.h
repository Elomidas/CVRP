//
// Created by elomidas on 14/03/18.
//

#ifndef CVRP_NODE_H
#define CVRP_NODE_H


#include "Truck.h"

class Node {
protected :
    unsigned int m_id;
    unsigned int m_quantity;
    Truck *m_used;
    unsigned int m_x, m_y;

public :
    Node();
    Node(unsigned int, unsigned int);
    Node(unsigned int, unsigned int, unsigned int, unsigned int);
    void setId(unsigned int);
    void setQuantity(unsigned int);
    void setUsed(Truck*);
    unsigned int getId() const;
    unsigned int getQuantity() const;
    bool getUsed() const;
    unsigned int getX() const {return m_x;}
    unsigned int getY() const {return m_y;}

    void setX(unsigned int i);

    void SetY(unsigned int i);
};


#endif //CVRP_NODE_H
