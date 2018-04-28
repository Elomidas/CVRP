//
// Created by elomidas on 28/03/18.
//

#ifndef CVRP_DISTANCENODE_H
#define CVRP_DISTANCENODE_H

#include <vector>

namespace graph {
    class DistanceNode {
    private:
        std::vector<double> m_distances;
        unsigned int m_nodeIndex;
        unsigned int m_size;
        unsigned long m_count;
        static unsigned long m_compteur;

    public:
        DistanceNode();
        DistanceNode(const DistanceNode &);
        explicit DistanceNode(unsigned int size);
        ~DistanceNode();

        const double getDistance(unsigned int nodeIndex) const;
        void setDistance(unsigned int nodeIndex, const double &distance);
        unsigned int getIndex() const {return m_nodeIndex;};
    };
}


#endif //CVRP_DISTANCENODE_H
