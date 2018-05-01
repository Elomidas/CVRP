//
// Created by elomidas on 24/04/18.
//

#include <cfloat>
#include <iostream>
#include <cmath>
#include <cassert>

#include "../include/GeneticAlgorithm.h"

/**
 * Constructor
 * @param populationSize    Size of population for each iteration
 * @param path              Path to source file
 * @param ite               Number of iteration (<0 for infinite run)
 * @param display           Nuber of iteration between to status' display
 */
GeneticAlgorithm::GeneticAlgorithm(const unsigned int populationSize, const std::string &path, const double &ite,
                                   const double &display) :
        Algorithm(path), m_populationSize(populationSize), m_iterations(ite), m_display(display), m_bestCost(DBL_MAX),
        m_step(0) {
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
    //Step 2 :
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
    for(std::vector<unsigned int> &vector : m_population) {
        m_graph.loadGenetic(vector);
        double cost(m_graph.getCost());
        if(m_min > cost) {
            m_min = cost;
            if(m_min < m_bestCost) {
                m_bestCost = cost;
                m_best = vector;
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
    std::clog << "Step : " << m_step << std::endl
              << "Current min : " << m_min << std::endl
              << "Current max : " << m_max << std::endl
              << "Global min : " << m_bestCost << std::endl << " > " << displayVector(m_best) << std::endl;
}

/**
 * Select parents for reproduce population
 */
void GeneticAlgorithm::selectParents() {
    std::vector<std::vector<unsigned int>> parents(m_population);
    m_population.clear();
    double gap(m_max - m_min);
    do {
        for (unsigned int i(0); (i < parents.size()) && (m_population.size() < m_populationSize); i++) {
            /* Solution with the best score is taken at 75%
             * Solution with the worst score is taken at 25%
             */
            double proba(0.25 + ((m_costs[i] - m_min) / gap) * 0.5);
            double rand(std::rand() / (double)RAND_MAX);
            if (rand < proba) {
                m_parents.emplace_back(parents[i]);
                if(m_parents.size() == 2) {
                    reproduction();
                    m_parents.clear();
                }
            }
        }
    } while(m_population.size() < m_populationSize);
}

/**
 * Create new population with selected parents
 */
void GeneticAlgorithm::reproduction() {
    assert(m_parents.size() == 2);
    double rand(std::rand() / (double)RAND_MAX);
    if(rand < 0.75) {
        //Crossover
        edgeRecombination();
    } else {
        //Swap Node
        for(const int id : {0, 1}) {
            if(m_population.size() < m_populationSize) {
                swapNodes(m_parents[id]);
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
bool contains(const std::vector<unsigned int> &vector, const unsigned int value) {
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
