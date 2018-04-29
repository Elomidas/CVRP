//
// Created by bastien on 26/04/18.
//

#ifndef CVRP_TABOUALGORITHM_H
#define CVRP_TABOUALGORITHM_H


#include "Algorithm.h"


class TabouAlgorithm : Algorithm{
private:
    Solution m_xmin;
    /**
     * les deux noeuds utilisés pour la transformation élémentaire
     */
    std::vector< std::pair<Node,Node> > m_T;
    double m_fmin;
    const int m_nmax;

public:
    TabouAlgorithm();

    ~TabouAlgorithm() override;

    void lancerAlgo() override;

};


#endif //CVRP_TABOUALGORITHM_H
