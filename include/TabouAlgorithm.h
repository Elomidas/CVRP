//
// Created by bastien on 26/04/18.
//

#ifndef CVRP_TABOUALGORITHM_H
#define CVRP_TABOUALGORITHM_H


#include "Algorithm.h"

using namespace std;


class TabouAlgorithm : Algorithm{
private:
    Node m_xmin;
    vector<int> m_T;
    double m_fmin;
    const int m_nmax;

public:
    TabouAlgorithm();

    ~TabouAlgorithm() override;

    void lancerAlgo() override;

    vector<Node> getVoisinage(Node act);
};


#endif //CVRP_TABOUALGORITHM_H
