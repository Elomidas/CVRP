//
// Created by bastien on 14/03/2018.
//

#ifndef CVRP_GRAPH_H
#define CVRP_GRAPH_H

#include <vector>
#include <string>

#include "Node.h"
#include "Truck.h"
#include "DistancesMatrix.h"

class Truck;

class Graph {
    private:
        int m_nodeNb;
        Node* m_nodes;
        DistancesMatrix m_distances;
        std::vector<Truck> m_trucks;
        static void splitLine(std::string&, unsigned int[]) const;

    public:
        static Graph getGraph(const std::string&);
        Graph(unsigned int);
        Graph(const unsigned int, const Node[], const int**);
        Graph(const unsigned int, const Node[], const int**, const std::vector<Truck>&);
        ~Graph();

        int getNodeNb();
        Node* getNodes();
        DistancesMatrix& getDistances();
        unsigned long getDistance(Node start, Node end);
        std::vector<Truck> getTrucks();
        void setNodeNb(int nodeNb);
        void setNodes(Node nodes[]);
        void setDistances(int** distances);
        void setDistances(const Node&, const Node&, const unsigned long&);
        void setTrucks(std::vector<Truck> trucks);

};


#endif //CVRP_GRAPH_H
