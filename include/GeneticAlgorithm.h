//
// Created by elomidas on 24/04/18.
//
// Documents :
// - https://www.sciencedirect.com/science/article/pii/S0307904X11005105
// - https://en.wikipedia.org/wiki/Edge_recombination_operator
//

#ifndef CVRP_GENETICALGORITHM_H
#define CVRP_GENETICALGORITHM_H


#include "Graph.h"
#include "Algorithm.h"

class GeneticAlgorithm : public Algorithm {
public:
    explicit GeneticAlgorithm(unsigned int, const std::string &);
    ~GeneticAlgorithm();

    void getStatus() const;
    void nextStep();

private:
    unsigned int m_populationSize, m_step;
    std::vector< std::vector<unsigned int> > m_population;
    std::vector<double> m_costs;
    double m_min, m_max, m_bestCost;
    std::vector<unsigned int> m_best;

    void generateFirstPopulation();

    //Legacy
    void selectParents();

    //Mutations
    void edgeRecombination();
    void swaphNodes(const std::vector<unsigned int>);
    std::vector<std::vector<unsigned int>> getAdjacencyMatrix(unsigned int) const;
    std::vector<std::vector<unsigned int>> getAdjacencyMatrix(unsigned int, unsigned int) const;
    static void removeNodeFromAdjacencyMatrix(std::vector<std::vector<unsigned int>> &, unsigned int);
    static void removeNodeFromVector(std::vector<unsigned int> &, unsigned int);

    //Crossover

};


#endif //CVRP_GENETICALGORITHM_H
