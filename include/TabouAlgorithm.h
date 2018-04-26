//
// Created by bastien on 26/04/18.
//

#ifndef CVRP_TABOUALGORITHM_H
#define CVRP_TABOUALGORITHM_H


#include "Algorithm.h"

using namespace std;

class TabouAlgorithm : Algorithm{
private:
    vector<Node> m_x;
    Node m_xmin;
    std::vector<int> m_T;
    double m_fmin;
    const int m_nmax;

public:
    TabouAlgorithm();
    ~TabouAlgorithm();
    virtual void lancerAlgo();
};


#endif //CVRP_TABOUALGORITHM_H
