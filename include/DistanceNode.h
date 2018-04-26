//
// Created by elomidas on 28/03/18.
//

#ifndef CVRP_DISTANCENODE_H
#define CVRP_DISTANCENODE_H

namespace graph {
    class DistanceNode {
    private:
        double &getDistanceReference(unsigned int nodeIndex);

        const double &getDistanceReference(unsigned int nodeIndex) const;

        double *m_distances;
        unsigned int m_nodeIndex;
        unsigned int m_size;

    public:
        DistanceNode();

        explicit DistanceNode(unsigned int size);

        ~DistanceNode();

        const double &getDistance(unsigned int nodeIndex) const;

        void setDistance(unsigned int nodeIndex, const double &distance);
    };
}


#endif //CVRP_DISTANCENODE_H
