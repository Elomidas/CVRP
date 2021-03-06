//
// Created by elomidas on 14/03/18.
//

#ifndef CVRP_NODE_H
#define CVRP_NODE_H

namespace graph {

    class Node {

    protected :
        unsigned int m_id;
        unsigned int m_quantity;
        unsigned int m_user;
        unsigned int m_x, m_y;

    public :
        Node();
        Node(const Node &);
        Node(unsigned int, unsigned int);
        Node(unsigned int, unsigned int, unsigned int, unsigned int);

        void setUsed(unsigned int);
        unsigned int getId() const;
        unsigned int getQuantity() const;
        bool getUsed() const;
        unsigned int getUser() const;
        unsigned int getX() const { return m_x; }
        unsigned int getY() const { return m_y; }
        void display() const;
    };
}

#endif //CVRP_NODE_H
