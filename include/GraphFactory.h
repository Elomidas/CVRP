//
// Created by elomidas on 24/04/18.
//

#ifndef CVRP_GRAPHFACTORY_H
#define CVRP_GRAPHFACTORY_H

#include <string>

#include "Graph.h"

class GraphFactory {
public:
    static Graph createGraph(const std::string&);

private:
    struct Data {

    };
};


#endif //CVRP_GRAPHFACTORY_H
