//
// Created by elomidas on 28/03/18.
//

#ifndef CVRP_DISTANCENODE_H
#define CVRP_DISTANCENODE_H


class DistanceNode {
private:
    unsigned long& getDistanceReference(unsigned int nodeIndex);
    unsigned long *m_distances;
    unsigned int m_nodeIndex;
    static unsigned int m_quantity;

public:
    static void setQuantity(unsigned int quantity) {m_quantity = quantity;};
    DistanceNode();
    ~DistanceNode();
    unsigned long getDistance(unsigned int nodeIndex);
    void setDistance(unsigned int nodeIndex, unsigned long distance);
};


#endif //CVRP_DISTANCENODE_H
