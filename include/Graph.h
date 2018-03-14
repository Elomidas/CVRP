//
// Created by bastien on 14/03/2018.
//

#ifndef CVRP_GRAPH_H
#define CVRP_GRAPH_H

using namespace std;

#include "Node.h";
#include "Truck.h";

#include "Vector";

class Truck;

class Graph {
    private:
        int m_nodeNb;
        Node* m_nodes;
        int** m_distances;
        vector<Truck> m_trucks;

    public:
        Graph(int nodeNb);
        Graph(int nodeNb, Node nodes[], int** distances);
        Graph(int nodeNb, Node nodes[], int** distances, vector<Truck> trucks);
        ~Graph();

        int getNodeNb();
        Node* getNodes();
        int** getDistances();
        int getDistance(Node start, Node end);
        vector<Truck> getTrucks();
        void setNodeNb(int nodeNb);
        void setNodes(Node nodes[]);
        void setDistances(int** distances);
        void setDistances(Node start, Node end, int value);
        void setTrucks(vector<Truck> trucks);

};


#endif //CVRP_GRAPH_H
