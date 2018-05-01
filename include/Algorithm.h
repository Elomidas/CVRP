//
// Created by bastien on 14/03/2018.
//

#ifndef CVRP_ALGORITHM_H
#define CVRP_ALGORITHM_H

#include <string>

#include "Graph.h"
#include "AlgorithmSettings.h"
#include "Node.h"

using namespace graph;

class Algorithm {

protected:
    graph::Graph m_graph;
    AlgorithmSettings m_settings;

public:
    Algorithm();
    explicit Algorithm(const std::string &);
    ~Algorithm();

    void setInputFile(const std::string&);
    void setConfigurationFile(const std::string&);
    virtual void lancerAlgo();
};


#endif //CVRP_ALGORITHM_H
