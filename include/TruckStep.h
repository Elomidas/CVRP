//
// Created by elomidas on 28/03/18.
//

#ifndef CVRP_TRUCKSTATE_H
#define CVRP_TRUCKSTATE_H


#include "Node.h"
#include "DistancesMatrix.h"

class TruckState {
public:
    explicit TruckState(const Node &node);
    ~TruckState();
    bool hasNext();
    TruckState* getNext();
    unsigned int getId();
    void setNext(TruckState *truckState);
    int hasNode(const Node &Node);
    unsigned long getProductNumber();
    unsigned long getDistance(const Node &origin, const DistancesMatrix &distancesMatrix);
    void add(const Node &node);
    void del();
    void replace(const Node &node);
    void delIndex(const unsigned int index);
    void addIndex(const unsigned int index, const Node &node);
    void replaceIndex(const unsigned int index, const Node &node);

private:
    const Node &m_node;
    TruckState *m_next;

};


#endif //CVRP_TRUCKSTATE_H
