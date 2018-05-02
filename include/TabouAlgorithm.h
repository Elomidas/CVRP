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
#define M_NB_DISPLAY 20

class TabouAlgorithm : public Algorithm {
private:
    Solution m_xmin;
    const unsigned int M_TAILLE = M_TAILLE_LISTE_TABOU;
    const int M_NMAX = M_NBITERATIONMAX;
    const int M_DISPLAY = M_NB_DISPLAY;
    std::list< ElementaryTransformation > m_T;
    double m_fmin;
    void addList(ElementaryTransformation);
    void getMini() override;

public:
    TabouAlgorithm();
    explicit TabouAlgorithm(const std::string &);
    explicit TabouAlgorithm(const unsigned int, const std::string&, const unsigned int, const unsigned int);
    ~TabouAlgorithm();

    void launchAlgo() override;
};


#endif //CVRP_TABOUALGORITHM_H
