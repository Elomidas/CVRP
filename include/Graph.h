//
// Created by bastien on 14/03/2018.
//

#ifndef CVRP_GRAPH_H
#define CVRP_GRAPH_H

#include <queue>
#include <string>

#include "Node.h"
#include "Truck.h"
#include "DistancesMatrix.h"
#include "Solution.h"

class Truck;

namespace graph {
    class Graph {
    private:
        unsigned int m_nodeNb, m_truckNb, m_truckNbMin;
        unsigned long m_qTotal;
        std::vector<Node> m_nodes;
        DistancesMatrix m_distances;
        Truck **m_trucks;
        void computeTruckNbMin();

    public:
        Graph(const Graph &);

        explicit Graph(unsigned int);

        explicit Graph(std::vector<Node> &);

        ~Graph();

        const unsigned int getNodeNb() const;

        const std::vector<Node> getNodes() const;

        DistancesMatrix &getDistances();

        const double getDistance(unsigned int, unsigned int) const;

        Truck** getTrucks();
/*
        void setNodes(Node nodes[]);

        void setDistances(int **distances);
*/
        void setDistances(const Node &, const Node &, const unsigned long &);

        void setTrucks(Truck **trucks);

        bool isSolution() const;

        Solution getSolution() const;

    };
}


#endif //CVRP_GRAPH_H
