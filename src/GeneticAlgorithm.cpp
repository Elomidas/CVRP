//
// Created by elomidas on 24/04/18.
//

#include <cfloat>
#include <iostream>
#include <cmath>
#include <cassert>

#include "../include/GeneticAlgorithm.h"
#include "../include/GraphFactory.h"

GeneticAlgorithm::GeneticAlgorithm(const unsigned int populationSize, const std::string &path) :
        Algorithm(path), m_populationSize(populationSize),
        m_bestCost(DBL_MAX), m_step(0) {
    generateFirstPopulation();
}

GeneticAlgorithm::~GeneticAlgorithm() {
    if(!m_population.empty()) {
        m_population.clear();
    }
}

void GeneticAlgorithm::generateFirstPopulation() {
    if(!m_population.empty()) {
        m_population.clear();
    }
    m_min = DBL_MAX;
    m_max = 0;
    for(unsigned int i(0); i < m_populationSize; i++) {
        m_graph.buildRandomSolution();
        std::vector<unsigned int> gen(m_graph.getGenetic());
        m_graph.loadGenetic(gen);
        double cost(m_graph.getCost());
        if(m_min > cost) {
            m_min = cost;
            m_bestCost = cost;
            m_best = gen;
        }
        if(m_max < cost) {
            m_max = cost;
        }
        m_population.emplace_back(gen);
        m_costs.emplace_back(cost);
    }
}

void GeneticAlgorithm::nextStep() {
    //Step 1 : select parents
    selectParents();
    unsigned int nbParents(static_cast<unsigned int>(m_population.size()));
    std::clog << nbParents << " parents selected." << std::endl;
    //Step 2 :
    //TODO
    //End
    m_step++;
}

std::string displayVector(const std::vector<unsigned int> &vector) {
    std::string res(std::to_string(vector[0]));
    for (unsigned int i : vector) {
        res += "-" + std::to_string(i);
    }
    return res;
}

void GeneticAlgorithm::getStatus() const {
    std::clog << "Step : " << m_step << std::endl
              << "Current min : " << m_min << std::endl
              << "Current max : " << m_max << std::endl
              << "Global min : " << m_bestCost << std::endl << " > " << displayVector(m_best) << std::endl;
}

void GeneticAlgorithm::selectParents() {
    std::vector<std::vector<unsigned int>> parents;
    double gap(m_max - m_min);
    /* We want to be sure to have at least 6 parents available
     */
    do {
        if(!parents.empty()) {
            parents.clear();
        }
        for (unsigned int i(0); i < m_population.size(); i++) {
            /* Solution with the best score is taken at 75%
             * Solution with the worst score is taken at 25%
             * We use a linear repartition
             */
            double proba(0.25 + ((m_costs[i] - m_min) / gap) * 0.5);
            double rand(std::rand() / (double)RAND_MAX);
            if (rand < proba) {
                parents.emplace_back(m_population[i]);
            }
        }
    } while(parents.size() < 6);
    m_population = parents;
}

void GeneticAlgorithm::edgeRecombination() {
    assert(m_population.size() < m_populationSize);
    //Family
    std::vector<unsigned int> child;
    unsigned int id1(static_cast<unsigned int>(rand() % m_population.size())), id2(0);
    do {
        id2 = static_cast<unsigned int>(rand() % m_population.size());
    }while(id2 == id1);
    std::vector<unsigned int> parent1 = m_population[id1];
    std::vector<unsigned int> parent2 = m_population[id2];

    //Neighbor lists
    std::vector<std::vector<unsigned int>> neighbors(getAdjacencyMatrix(id1, id2));
    std::vector<unsigned int> available(parent1);

    //Algorithm
    std::vector<unsigned int> &parent = ((rand() / (double)RAND_MAX) > 0.5) ? parent1 : parent2;
    unsigned int node = parent[0];
    while(child.size() < parent.size()) {
        child.emplace_back(node);
        removeNodeFromAdjacencyMatrix(neighbors, node);
        removeNodeFromVector(available, node);
        if(!neighbors[node].empty()) {
            auto tmp = static_cast<unsigned int>(rand() % neighbors[node].size());
            node = neighbors[node][tmp];
        } else {
            auto tmp = static_cast<unsigned int>(rand() % available.size());
            node = available[tmp];
        }
    }
    m_population.emplace_back(child);
}

std::vector<std::vector<unsigned int>> GeneticAlgorithm::getAdjacencyMatrix(const unsigned int memberIndex) const {
    std::vector<unsigned int> &member = m_population[memberIndex];
    std::vector<std::vector<unsigned int>> matrix(member.size(), std::vector<unsigned int>());
    for(unsigned int i(0); i < member.size(); i++) {
        unsigned int index = member[i];
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
}

bool contains(const std::vector<unsigned int> &vector, const unsigned int value) {
    for(unsigned int i : vector) {
        if(i == value) {
            return true;
        }
    }
    return false;
}

std::vector<std::vector<unsigned int>> GeneticAlgorithm::getAdjacencyMatrix(const unsigned int member1,
                                                                            const unsigned int member2) const {
    std::vector<std::vector<unsigned int>>
            matrix1(getAdjacencyMatrix(member1)),
            matrix2(getAdjacencyMatrix(member2)),
            matrix(matrix1.size(), std::vector<unsigned int>());
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

void GeneticAlgorithm::removeNodeFromAdjacencyMatrix(std::vector<std::vector<unsigned int>> &matrix, const unsigned int node) {
    for (auto &m : matrix) {
        removeNodeFromVector(m, node);
    }
}

void GeneticAlgorithm::removeNodeFromVector(std::vector<unsigned int> &vector, const unsigned int node) {
    for(unsigned int i(0); i < vector.size(); i++) {
        if(vector[i] == node) {
            vector.erase(vector.begin() + i);
        }
    }
}

void GeneticAlgorithm::swaphNodes(const std::vector<unsigned int> member) {
    std::vector<unsigned int> child(member);
    double proba(1 / (double)member.size());
    for(unsigned int i(0); i < member.size(); i++) {
        if(proba > (rand() / (double)RAND_MAX)) {
            unsigned int target;
            do {
                target = static_cast<unsigned int>(rand() % member.size());
            } while(target == i);
            child[i] = member[target];
            child[target] = member[i];
        }
    }
    m_population.emplace_back(child);
}
