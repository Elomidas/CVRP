//
// Created by elomidas on 28/03/18.
//

#ifndef CVRP_DISTANCESMATRIX_H
#define CVRP_DISTANCESMATRIX_H


#include "DistanceNode.h"

class DistancesMatrix {
public:
    explicit DistancesMatrix(unsigned int numberOfNodes);
    ~DistancesMatrix();
    unsigned int getNumberOfNodes() const;
    void setDistance(unsigned int firstNodeIndex, unsigned int secondNodeIndex, const unsigned long &distance);
    const unsigned long getDistance(unsigned int firstNodeIndex, unsigned int secondNodeIndex) const;

    static bool test(unsigned long (*)(unsigned int, unsigned int), unsigned int);

private:
    void sortIndices(unsigned int &first, unsigned int &second) const;
    DistanceNode *m_distances;
    unsigned int m_numberOfNodes;
};


#endif //CVRP_DISTANCESMATRIX_H
