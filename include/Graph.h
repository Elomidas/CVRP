//
// Created by bastien on 14/03/2018.
//

#ifndef CVRP_GRAPH_H
#define CVRP_GRAPH_H

using namespace std;

#include "Node.h";
#include "Truck.h";

#include "Vector";

class Graph {
    private:
        Node* m_nodes;
        int** m_distances;
        vector<Truck> m_trucks;

    public:
        Graph(int nodesNb);
        Graph(Node nodes[], int** distances);
        Graph(Node nodes[], int** distances, vector<Truck> trucks);

        Node* getNodes();
        int** getDistances();
        vector<Truck> getTrucks();
        void setNodes(Node nodes[]);
        void setDistances(int** distances);
        void setTrucks(vector<Truck> trucks);

};


#endif //CVRP_GRAPH_H
