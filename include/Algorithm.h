//
// Created by bastien on 14/03/2018.
//

#ifndef CVRP_ALGORITHM_H
#define CVRP_ALGORITHM_H

#include <string>

#include "Graph.h"
#include "Node.h"

using namespace graph;

class Algorithm {

protected:
    graph::Graph m_graph;

    virtual void getMini();

public:
    explicit Algorithm(const std::string &);
    virtual ~Algorithm();

    virtual void launchAlgo();
    virtual void display();
    virtual void display(const std::string &);
};


#endif //CVRP_ALGORITHM_H
