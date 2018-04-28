//
// Created by elomidas on 28/03/18.
//

#ifndef CVRP_DISTANCESMATRIX_H
#define CVRP_DISTANCESMATRIX_H


#include "DistanceNode.h"
#include "Node.h"

namespace graph {
    class DistancesMatrix {
    public:
        DistancesMatrix(const DistancesMatrix &);
        explicit DistancesMatrix(unsigned int numberOfNodes);
        ~DistancesMatrix();

        unsigned int getNumberOfNodes() const;
        void setDistance(unsigned int firstNodeIndex, unsigned int secondNodeIndex, const unsigned long &distance);
        const double getDistance(unsigned int firstNodeIndex, unsigned int secondNodeIndex) const;
        void generateDistanceFromCoordinates(const std::vector<Node> &);
        static bool test(unsigned long (*)(unsigned int, unsigned int), unsigned int);

    private:
        std::vector<DistanceNode> m_distancesNodes;
        unsigned int m_numberOfNodes;

        void sortIndices(unsigned int &first, unsigned int &second) const;

        static const double computeDistance(const Node &, const Node &);
    };
}


#endif //CVRP_DISTANCESMATRIX_H
