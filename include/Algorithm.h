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
    std::string m_inputFile;
    AlgorithmSettings m_settings;

    const unsigned int getGraphSize();

public:
    Algorithm();

    //Algorithm(const std::string&, const std::string&);

    virtual ~Algorithm();

    void setInputFile(const std::string&);

    void setConfigurationFile(const std::string&);

    void reverse(Node n1, Node n2);

    virtual void lancerAlgo();

};


#endif //CVRP_ALGORITHM_H
