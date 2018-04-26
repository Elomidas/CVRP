//
// Created by elomidas on 24/04/18.
//

#ifndef CVRP_GRAPHFACTORY_H
#define CVRP_GRAPHFACTORY_H

#include <string>
#include <queue>

#include "Graph.h"

class GraphFactory {
public:
    static std::queue<graph::Node> readFile(const std::string&);
    static void test(const std::string&);

private:
    static void splitLine(std::string &, unsigned int*);
    static unsigned int atoi(const std::string &);
};


#endif //CVRP_GRAPHFACTORY_H
