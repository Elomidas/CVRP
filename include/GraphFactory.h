//
// Created by elomidas on 24/04/18.
//

#ifndef CVRP_GRAPHFACTORY_H
#define CVRP_GRAPHFACTORY_H

#include <string>

#include "Graph.h"

class GraphFactory {
public:
    static std::vector<graph::Node> readFile(const std::string&);
    static void test(const std::string&);
};


#endif //CVRP_GRAPHFACTORY_H
