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

    void reverse(Solution solution, unsigned int n1, unsigned int n2);

    Solution getRandomSolution();

    const std::vector<Solution> getVoisinage(const Solution, const std::vector< std::pair<unsigned int, unsigned int> >);

    const std::pair<unsigned int, unsigned int> getDifference(const Solution, const Solution);

    virtual void lancerAlgo();

};


#endif //CVRP_ALGORITHM_H
