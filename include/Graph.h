//
// Created by bastien on 14/03/2018.
//

#ifndef CVRP_GRAPH_H
#define CVRP_GRAPH_H

#include <queue>
#include <string>
#include <list>

#include "Node.h"
#include "Truck.h"
#include "DistancesMatrix.h"
#include "Solution.h"
#include "ElementaryTransformation.h"

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
        const bool isInTabou(const std::list<ElementaryTransformation>,
                             ElementaryTransformation pair_tabou1) const;
        void addNodeToTruck(unsigned int, unsigned int);
        void addNodeToTruck(unsigned int, unsigned int, unsigned int);
        void invertNodes(unsigned int, unsigned int);
        void deleteNodeToTruck(unsigned int node, unsigned int truck);
        void deleteNodeToTruckByIndex(unsigned int index, unsigned int truck);
        void invertNodesByIndex(unsigned int node1, unsigned int node2, unsigned int index1, unsigned int index2);
        void mooveNode(unsigned int node,unsigned int old_truck, unsigned int new_truck, unsigned int new_position);

    public:
        Graph(const Graph &);
        explicit Graph(unsigned int);
        explicit Graph(std::vector<Node>);
        ~Graph();

        void loadSolution(const Solution &);
        void loadGenetic(const std::vector<unsigned int> &);
        const unsigned int getTrucksNb() const { return m_truckNb; };
        const std::vector<Node> getNodes() const { return m_nodes; };
        const std::vector<Truck> getTrucks() const { return m_trucks; };
        const Truck getTruck(unsigned int i) const { return m_trucks[i]; };
        void setNode(unsigned int i, Node node) { m_nodes[i] = node; }
        const unsigned int getNodeNb() const;
        const Node& getNode(unsigned int) const;
        const double getDistance(unsigned int, unsigned int) const;
        void setTrucksNumber(unsigned int);
        bool isSolution() const;
        Solution getSolution() const;
        std::vector<unsigned int> getGenetic() const;
        double getCost() const;
        void buildRandomSolution();
        const std::vector<Graph> getVoisinage(std::list< ElementaryTransformation >, std::vector<ElementaryTransformation>&);
        const void testElementaryOp();
        static std::vector<unsigned int> splitLine(std::string &line);
        static unsigned int atoi(const std::string &number);
    };
}


#endif //CVRP_GRAPH_H
