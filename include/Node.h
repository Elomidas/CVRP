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
    Node(const unsigned int id, const unsigned int quantity);
    void setId(const unsigned int id);
    void setQuantity(const unsigned int quantity);
    void setUsed(const bool used);
    unsigned int getId();
    unsigned int getQuantity();
    bool getUsed();

};


#endif //CVRP_NODE_H
