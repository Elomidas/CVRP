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
        const bool isInTabou(const std::vector<std::pair<unsigned int, unsigned int>>,
                             const std::pair<unsigned int, unsigned int> pair_tabou1) const;

    public:
        Graph(const Graph &);
        explicit Graph(unsigned int);
        explicit Graph(std::vector<Node>);
        ~Graph();

        void loadSolution(const Solution &);
        const unsigned int getTrucksNb() const { return m_truckNb; };
        const std::vector<Node> getNodes() const { return m_nodes; };
        const std::vector<Truck> getTrucks() const { return m_trucks; };
        const Truck getTruck(unsigned int i) const { return m_trucks[i]; };
        void setNode(unsigned int i, Node node) { m_nodes[i] = node; }
        const unsigned int getNodeNb() const;
        const double getDistance(unsigned int, unsigned int) const;
        void setTrucksNumber(unsigned int);
        bool isSolution() const;
        Solution getSolution() const;
        void buildRandomSolution();
        void addNodeToTruck(unsigned int, unsigned int);
        void addNodeToTruck(unsigned int, unsigned int, unsigned int);
        void invertNodes(unsigned int, unsigned int);

        void deleteNodeToTruck(unsigned int node, unsigned int truck);

        void deleteNodeToTruckByIndex(unsigned int index, unsigned int truck);

        void invertNodesByIndex(unsigned int node1, unsigned int node2, unsigned int index1, unsigned int index2);

        double getCost() const;

        const std::vector<Graph> getVoisinage(std::vector< std::pair<unsigned int, unsigned int> >);

        const std::pair<unsigned int, unsigned int> getDifference(const Graph graph);
    };
}


#endif //CVRP_GRAPH_H
