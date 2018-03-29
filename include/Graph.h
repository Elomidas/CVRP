//
// Created by bastien on 14/03/2018.
//

#ifndef CVRP_GRAPH_H
#define CVRP_GRAPH_H

#include <vector>

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

    public:
        Graph(int nodeNb);
        Graph(int nodeNb, Node nodes[], int** distances);
        Graph(int nodeNb, Node nodes[], int** distances, std::vector<Truck> trucks);
        ~Graph();

        int getNodeNb();
        Node* getNodes();
        DistancesMatrix& getDistances();
        unsigned long getDistance(Node start, Node end);
        std::vector<Truck> getTrucks();
        void setNodeNb(int nodeNb);
        void setNodes(Node nodes[]);
        void setDistances(int** distances);
        void setDistances(Node start, Node end, int value);
        void setTrucks(std::vector<Truck> trucks);

};


#endif //CVRP_GRAPH_H
