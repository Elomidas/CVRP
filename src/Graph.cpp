//
// Created by bastien on 14/03/2018.
//

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "../include/Graph.h"

Graph::Graph(const unsigned int nodeNb) : m_trucks(), m_nodeNb(nodeNb), m_distances(nodeNb) {
    m_nodes = new Node[nodeNb];
}
/*
Graph::Graph(int nodeNb, Node *nodes, int **distances) : m_trucks(), m_distances(distances), m_nodes(nodes), m_nodeNb(nodeNb) {
    //Nothing
}

Graph::Graph(int nodeNb, Node *nodes, int **distances, std::vector<Truck> trucks) : m_trucks(trucks), m_distances(distances), m_nodes(nodes), m_nodeNb(nodeNb) {
    //Nothing
}
*/

Graph Graph::getGraph(const std::string &path) {
    std::ifstream fichier(path);

    if(fichier) {
        std::string line;
        getline(fichier, line);
        std::cout << "File head : " << line << std::endl;
        unsigned int fileSize;
        std::vector<Node> nodes;
        while(getline(fichier, line)) {
            unsigned int parts[] = {0,0,0,0};
            std::cout << line << std::endl;
            splitLine(line, parts);
            Node n(parts[0], parts[2], parts[3], parts[1]);
            nodes.push_back(n);
        }
        fichier.close();
        std::cout << "File size : " << fileSize << std::endl;
        Graph graph(nodes.size());
    }
    else {
        std::cerr << "Unable to open file " << path << " !" << std::endl;
    }
}

Graph::~Graph() {
    delete(m_nodes);
    m_trucks.clear();
    m_nodeNb = 0;
}

DistancesMatrix& Graph::getDistances() {return m_distances;}

unsigned long Graph::getDistance(Node start, Node end) {
    return m_distances.getDistance(start.getId(), end.getId());
}

Node* Graph::getNodes() {return m_nodes;}

std::vector<Truck> Graph::getTrucks() {return m_trucks;}
/*
void Graph::setDistances(int **distances) {m_distances = distances;}
*/
void Graph::setDistances(const Node& start, const Node& end, const unsigned long &value) {
    m_distances.setDistance(start.getId(), end.getId(), value);
}

void Graph::setNodes(Node *nodes) {m_nodes = nodes;}

void Graph::setTrucks(std::vector <Truck> trucks) {m_trucks = trucks;}

void Graph::splitLine(std::string &line, unsigned int *res) const {
    std::string delimiter = ";";
    unsigned int i;
    size_t pos = 0;
    for(i = 0; ((pos = line.find(delimiter)) != std::string::npos); i++) {
        res[i] = (unsigned int)atoi(line.substr(0, pos).c_str());
        line.erase(0, pos + delimiter.length());
    }
    res[i] = (unsigned int)atoi(line.c_str());
}
