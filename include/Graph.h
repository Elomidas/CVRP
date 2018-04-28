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

class Truck;

namespace graph {
    class Graph {
    private:
        unsigned int m_nodeNb;
        Node *m_nodes;
        DistancesMatrix m_distances;
        std::vector<Truck> m_trucks;

    public:
        explicit Graph(unsigned int);

        explicit Graph(std::queue<Node> &);

        explicit Graph(const Graph&); // pour faire une copie

        ~Graph();

        unsigned int getNodeNb()const;

        Node *getNodes() const;

        DistancesMatrix &getDistances();

        const double& getDistance(const Node &, const Node &) const;

        const double& getDistance(unsigned int, unsigned int) const;

        std::vector<Truck> getTrucks();

        void setNodes(Node nodes[]);

        void setDistances(int **distances);

        void setDistances(const Node &, const Node &, const unsigned long &);

        void setTrucks(std::vector<Truck> trucks);

        Graph copyGraph();

    };
}


#endif //CVRP_GRAPH_H
