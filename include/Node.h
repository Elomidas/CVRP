//
// Created by elomidas on 14/03/18.
//

#ifndef CVRP_NODE_H
#define CVRP_NODE_H


class Node {
protected :
    unsigned int m_id;
    unsigned int m_quantity;
    bool m_used;

public :
    Node();
    Node(unsigned int, unsigned int);
    void setId(unsigned int);
    void setQuantity(unsigned int);
    void setUsed(bool);
    unsigned int getId() const;
    unsigned int getQuantity() const;
    bool getUsed() const;

};


#endif //CVRP_NODE_H
