//
// Created by elomidas on 24/04/18.
//
// Documents :
// - https://www.sciencedirect.com/science/article/pii/S0307904X11005105
// - https://en.wikipedia.org/wiki/Edge_recombination_operator
// - http://www.rubicite.com/Tutorials/GeneticAlgorithms/CrossoverOperators/PMXCrossoverOperator.aspx/
//

#ifndef CVRP_GENETICALGORITHM_H
#define CVRP_GENETICALGORITHM_H


#include "Graph.h"
#include "Algorithm.h"

class GeneticAlgorithm : public Algorithm {
public:
    explicit GeneticAlgorithm(unsigned int, const std::string &, const double &,
                              const double &, const double &probaEdgeReco = double(0.4), const double &probaPMX = double(0.4));
    ~GeneticAlgorithm();

    void getStatus() const;
    void launchAlgo();

private:
    unsigned int m_populationSize;
    std::vector< std::vector<unsigned int> > m_population;
    std::vector< std::vector<unsigned int> > m_parents;
    std::vector<double> m_costs;
    double m_min, m_max, m_bestCost, m_step, m_iterations, m_display;
    std::vector<unsigned int> m_best;
    Solution m_bestSolution;
    double m_probaEdgeReco, m_probaPMX;

    void generateFirstPopulation();
    void nextStep();
    void checkFitness();
    void addMember(const std::vector<unsigned int> &);
    bool isValid(const std::vector<unsigned int> &) const;
    void getMini() override;

    //Helpers
    unsigned int getIndexPMX(unsigned int, const std::vector<unsigned int> &) const;
    static bool contains(const std::vector<unsigned int> &, unsigned int);

    //Legacy
    void selectParents();
    void reproduction();

    //Mutations
    void edgeRecombination();
    void swapNodes(std::vector<unsigned int>);
    void partiallyMappedCrossover();
    std::vector<std::vector<unsigned int>> getAdjacencyMatrix(const std::vector<unsigned int> &) const;
    std::vector<std::vector<unsigned int>> getAdjacencyMatrix() const;
    static void removeNodeFromAdjacencyMatrix(std::vector<std::vector<unsigned int>> &, unsigned int);
    static void removeNodeFromVector(std::vector<unsigned int> &, unsigned int);

};


#endif //CVRP_GENETICALGORITHM_H
