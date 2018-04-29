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
        std::vector<Truck> m_trucks;
        void computeTruckNbMin();

    public:
        Graph(const Graph &);
        explicit Graph(unsigned int);
        explicit Graph(std::vector<Node> &);
        ~Graph();

        const unsigned int getNodeNb() const;
        const double getDistance(unsigned int, unsigned int) const;
        void setTrucksNumber(unsigned int);
        bool isSolution() const;
        Solution getSolution() const;

    };
}


#endif //CVRP_GRAPH_H
