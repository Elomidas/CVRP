//
// Created by bastien on 26/04/18.
//

#ifndef CVRP_TABOUALGORITHM_H
#define CVRP_TABOUALGORITHM_H


#include "Algorithm.h"
#include "ElementaryTransformation.h"
#include <list>

#define M_TAILLE_LISTE_TABOU 20
#define M_NBITERATIONMAX 100

class TabouAlgorithm : Algorithm{
private:
    Solution m_xmin;
    const static unsigned int M_TAILLE = M_TAILLE_LISTE_TABOU;
    std::list< ElementaryTransformation > m_T;
    double m_fmin;
    const int m_nmax = M_NBITERATIONMAX;
    void addList(ElementaryTransformation);

public:
    TabouAlgorithm();
    ~TabouAlgorithm();

    void lancerAlgo() override;
};


#endif //CVRP_TABOUALGORITHM_H
