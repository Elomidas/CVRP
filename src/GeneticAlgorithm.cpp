//
// Created by elomidas on 24/04/18.
//

#include <cfloat>
#include <iostream>
#include <cmath>
#include <cassert>

#include "../include/GeneticAlgorithm.h"
#include "../include/Graphviz.h"

/**
 * @brief GeneticAlgorithm::GeneticAlgorithm Constructor
 * @param populationSize    Size of population for each iteration
 * @param path              Path to source file
 * @param ite               Number of iteration (<0 for infinite run)
 * @param display           Nuber of iteration between to status' display
 * @param probaEdgeReco     Probability of an Edge Recombination for reproduction (optionnal, default = 0.4)
 * @param probaPMX          Probability of a Partial Mapped Crossover for reproduction (optionnal, default = 0.4)
 */
GeneticAlgorithm::GeneticAlgorithm(const unsigned int populationSize, const std::string &path, const double &ite,
                                   const double &display, const double &probaEdgeReco, const double &probaPMX) : Algorithm(path) {
    m_probaEdgeReco = probaEdgeReco;
    m_probaPMX = probaPMX;
    m_populationSize = populationSize;
    m_iterations = ite;
    m_display = display;
    m_bestCost = DBL_MAX;
    if((m_probaEdgeReco + m_probaPMX) > 1) {
        m_probaEdgeReco = m_probaPMX = 0.4;
    }
    generateFirstPopulation();
}

/**
 * Destructor
 */
GeneticAlgorithm::~GeneticAlgorithm() {
    if(!m_population.empty()) {
        m_population.clear();
    }
}

/**
 * Generate the population before launching algorithm
 */
void GeneticAlgorithm::generateFirstPopulation() {
    if(!m_population.empty()) {
        m_population.clear();
    }
    m_min = DBL_MAX;
    m_max = 0;
    for(unsigned int i(0); i < m_populationSize; i++) {
        m_graph.buildRandomSolution();
        std::vector<unsigned int> gen(m_graph.getGenetic());
        addMember(gen);
    }
    checkFitness();
}

/**
 * Add a member to population
 * @param member Member to add
 */
void GeneticAlgorithm::addMember(const std::vector<unsigned int> &member) {
    assert(isValid(member));
    assert(m_population.size() < m_populationSize);
    m_population.emplace_back(member);
}

/**
 * Iterate one time
 */
void GeneticAlgorithm::nextStep() {
    //Step 1 : select parents and reproduce
    selectParents();
    //Step 2 : Reproduction
    reproduction();
    //Step 3 : Apllying fitness
    checkFitness();
    //End
    m_step++;
}

/**
 * Attribute a score to each population member
 */
void GeneticAlgorithm::checkFitness() {
    if(!m_costs.empty()) {
        m_costs.clear();
    }
    m_min = DBL_MAX;
    m_max = 0;
    for(std::vector<unsigned int> &vector : m_population) {
        m_graph.loadGenetic(vector);
        double cost(m_graph.getCost());
        if(m_min > cost) {
            m_min = cost;
            if(m_min < m_bestCost) {
                m_bestCost = cost;
                m_best = vector;
                m_bestSolution = m_graph.getSolution();
            }
        }
        if(m_max < cost) {
            m_max = cost;
        }
        m_costs.emplace_back(cost);
    }
}

/**
 * Display a vector
 * @param vector Vector to display
 * @return String representing the vector
 */
std::string displayVector(const std::vector<unsigned int> &vector) {
    std::string res;
    for (unsigned int i : vector) {
        res += "-" + std::to_string(i);
    }
    return res.substr(1);
}

/**
 * Describe current algorithm status
 */
void GeneticAlgorithm::getStatus() const {
    std::clog << std::endl
              << "Step : " << m_step << std::endl
              << "Current min : " << m_min << std::endl
              << "Current max : " << m_max << std::endl
              << "Global min : " << m_bestCost << std::endl << " > " << displayVector(m_best) << std::endl;
}

/**
 * Select parents for reproduce population
 */
void GeneticAlgorithm::selectParents() {
    /*  Keep about 3/5 of the population
     */
    unsigned int quota(4 * m_population.size() / 5);
    std::vector<std::vector<unsigned int>> parents(m_population);
    std::vector<double> newCosts;
    m_population.clear();
    double cumul(0);
    std::vector<double> probas;
    for(unsigned int i(0); i < parents.size(); i++) {
        double prob(m_max - m_costs[i]);
        cumul += prob;
        probas.emplace_back(prob);
    }
    do {
        unsigned int i(0);
        double random(cumul * (rand() / (double)RAND_MAX));
        for(; (random >= probas[i]) && (i < parents.size() - 1); i++) {
            random -= probas[i];
        }
        m_population.emplace_back(parents[i]);
        newCosts.emplace_back(m_costs[i]);
        m_costs[i] = m_max;
    } while(m_population.size() < quota);
    m_costs = newCosts;
}

/**
 * Create new population with selected parents
 */
void GeneticAlgorithm::reproduction() {
    std::vector<std::vector<unsigned int>> parents(m_population);
    double cumul(0);
    std::vector<double> probas;
    for(unsigned int i(0); i < parents.size(); i++) {
        double prob(m_max - m_costs[i]);
        cumul += prob;
        probas.emplace_back(prob);
    }
    while(m_population.size() < m_populationSize) {
        if(!m_parents.empty()) {
            m_parents.clear();
        }
        unsigned int index1(parents.size()), index2(parents.size());
        do {
            double random = cumul * (rand() / (double)RAND_MAX);
            unsigned int i(0);for(; (random >= probas[i]) && (i < parents.size() - 1); i++) {
                random -= probas[i];
            }
            if(index1 >= parents.size()) {
                index1 = i;
            } else {
                index2 = i;
            }
        } while(!((index1 != index2) && (index1 < parents.size()) && (index2 < parents.size())));
        for(const unsigned int &i : {index1, index2}) {
            m_parents.emplace_back(parents[i]);
        }
        //Reproduction part
        double rand(std::rand() / (double)RAND_MAX);
        if((rand -= m_probaEdgeReco) <= 0) {
            //Crossover
            edgeRecombination();
        } else if((rand -= m_probaPMX) <= 0) {
            //Partially Mapped Crossover
            partiallyMappedCrossover();
        } else {
            //Swap Node
            for(const int id : {0, 1}) {
                if(m_population.size() < m_populationSize) {
                    swapNodes(m_parents[id]);
                }
            }
        }
    }
}

/**
 * Recombination of edges (type of reproduction)
 */
void GeneticAlgorithm::edgeRecombination() {
    assert(m_population.size() < m_populationSize);

    //Neighbor lists
    std::vector<std::vector<unsigned int>> neighborsList(getAdjacencyMatrix());

    //Algorithm
    for(std::vector<unsigned int> parent : {m_parents[0], m_parents[1]}) {
        assert(isValid(parent));
        if(m_population.size() < m_populationSize) {
            std::vector<unsigned int> available(parent);
            std::vector<std::vector<unsigned int>> neighbors(neighborsList);
            std::vector<unsigned int> child;
            unsigned int node = parent[0];
            while (child.size() < parent.size()) {
                child.emplace_back(node);
                removeNodeFromAdjacencyMatrix(neighbors, node);
                removeNodeFromVector(available, node);
                if(child.size() < parent.size()) {
                    if (!neighbors[node - 1].empty()) {
                        auto tmp = static_cast<unsigned int>(std::rand() % neighbors[node - 1].size());
                        node = neighbors[node - 1][tmp];
                    } else {
                        auto tmp = static_cast<unsigned int>(std::rand() % available.size());
                        node = available[tmp];
                    }
                }
            }
            addMember(child);
        }
    }
}

void GeneticAlgorithm::partiallyMappedCrossover() {
    assert(m_parents.size() == 2);
    //Step 1 : Select a swth of parent 1 and copy it to child
    unsigned int size = m_parents[0].size();
    std::vector<unsigned int> child(size, 0);
    int i1, i2, diff;
    do {
        i1 = rand() % size;
        i2 = rand() % size;
        diff = abs(i1 - i2);
    } while((diff > (size / 2)) || (diff < 4));
    unsigned int i, j;
    if(i1 < i2) {
        i = i1;
        j = i2;
    } else {
        i = i2;
        j = i1;
    }

    unsigned int k(0);
    for(k = i; k < j; k++) {
        child[k] = m_parents[0][k];
    }

    //Algo
    unsigned int nbSearch(m_parents[1][i]);
    do {
        for(k = 0; k < size; k++) {
            if((child[k] != 0) && !contains(child, m_parents[1][k])) {
                nbSearch = m_parents[1][k];
                k = size+1;
            }
        }
        if(k != size) {
            child[getIndexPMX(nbSearch, child)] = nbSearch;
        }
    } while(k != size);

    //Copy rest of parent 2 in child
    for(k = 0; k < size; k++) {
        if(child[k] == 0) {
            child[k] = m_parents[1][k];
        }
    }
    addMember(child);
}

unsigned int GeneticAlgorithm::getIndexPMX(unsigned int nbSearch, const std::vector<unsigned int> &child) const {
    unsigned int index;
    bool ok(false);
    do {
        for(index = 0; m_parents[0][index] != nbSearch; index++);
        if(child[index] != 0) {
            nbSearch = m_parents[1][index];
        } else {
            ok = true;
        }
    } while(!ok);
    return index;
}

/**
 * Get Node's neighbors list for each Node
 * @param member Member of the population to analyze
 * @return Adjacency matrix of this member
 */
std::vector<std::vector<unsigned int>> GeneticAlgorithm::getAdjacencyMatrix(const std::vector<unsigned int> &member) const {
    std::vector<std::vector<unsigned int>> matrix(member.size());
    for(unsigned int i(0); i < member.size(); i++) {
        unsigned int index = member[i]-1;
        unsigned int prev, next;
        if(i == 0) {
            prev = member[member.size() - 1];
        } else {
            prev = member[i-1];
        }
        if(i == (member.size() - 1)) {
            next = member[0];
        } else {
            next = member[i+1];
        }
        matrix[index].emplace_back(prev);
        matrix[index].emplace_back(next);
    }
    return matrix;
}

/**
 * Check if a vector contains a value
 * @param vector Vector to check
 * @param value  Value tu search
 * @return true if vector contains value, false else
 */
bool GeneticAlgorithm::contains(const std::vector<unsigned int> &vector, const unsigned int value) {
    for(unsigned int i : vector) {
        if(i == value) {
            return true;
        }
    }
    return false;
}

/**
 * Get adjacency matrix for the selected parents
 * @return Adjacency Matrix
 */
std::vector<std::vector<unsigned int>> GeneticAlgorithm::getAdjacencyMatrix() const {
    std::vector<std::vector<unsigned int>>
            matrix1(getAdjacencyMatrix(m_parents[0])),
            matrix2(getAdjacencyMatrix(m_parents[1]));
    std::vector<std::vector<unsigned int>>
            matrix(matrix1.size());
    for(unsigned int i(0); i < matrix.size(); i++) {
        for(unsigned int j(0); j < fmax(matrix1[i].size(), matrix2[i].size()); j++) {
            if((j < matrix1[i].size()) && (!contains(matrix[i], matrix1[i][j]))) {
                matrix[i].emplace_back(matrix1[i][j]);
            }
            if((j < matrix2[i].size()) && (!contains(matrix[i], matrix2[i][j]))) {
                matrix[i].emplace_back(matrix2[i][j]);
            }
        }
    }
    return matrix;
}

/**
 * Remove a Node from an adjacency matrix
 * @param matrix Adjacency matrix
 * @param node   Node to delete
 */
void GeneticAlgorithm::removeNodeFromAdjacencyMatrix(std::vector<std::vector<unsigned int>> &matrix, const unsigned int node) {
    for (auto &m : matrix) {
        removeNodeFromVector(m, node);
    }
}

/**
 * Remove a Node from a vector
 * @param vector Vector
 * @param node   Node to delete
 */
void GeneticAlgorithm::removeNodeFromVector(std::vector<unsigned int> &vector, const unsigned int node) {
    for(unsigned int i(0); i < vector.size(); i++) {
        if(vector[i] == node) {
            vector.erase(vector.begin() + i);
            i--;
        }
    }
}

/**
 * Swap two Nodes (reproduction method)
 * @param member Parent to alterate
 */
void GeneticAlgorithm::swapNodes(const std::vector<unsigned int> member) {
    std::vector<unsigned int> child(member);
    double proba(1 / (2.0 * member.size()));
    for(unsigned int i(0); i < member.size(); i++) {
        if(proba > (rand() / (double)RAND_MAX)) {
            unsigned int target;
            do {
                target = static_cast<unsigned int>(std::rand() % member.size());
            } while(target == i);
            unsigned int tmp(child[i]);
            child[i] = child[target];
            child[target] = tmp;
        }
    }
    addMember(child);
}

/**
 * Launch algorithm
 */
void GeneticAlgorithm::launchAlgo() {
    m_step = 0;
    double display(m_display);
    while((m_iterations < 0) || (m_step < m_iterations)) {
        nextStep();
        if((display <= 0) || (m_step == m_iterations)) {
            getStatus();
            display = m_display;
        }
        display--;
    }
    getMini();
}

/**
 * Check if a member is valid
 * @param vector member to check
 * @return true if member is valid, false else
 */
bool GeneticAlgorithm::isValid(const std::vector<unsigned int> &vector) const {
    std::vector<bool> check(vector.size(), true);
    for(const unsigned int &i : vector) {
        if(!check[i-1]) {
            std::cerr << "Duplicate entry " << i << std::endl;
            return false;
        }
        check[i-1] = false;
    }
    return true;
}

/**
 * Load best solution in the graph
 */
void GeneticAlgorithm::getMini() {
    m_graph.loadGenetic(m_best);
}
