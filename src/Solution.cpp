//
// Created by elomidas on 28/04/18.
//

#include <cstdlib>
#include <cfloat>
#include <cassert>

#include "../include/Solution.h"

/**
 * Create an empty solution with the highest cost possible
 */
Solution::Solution() : m_paths(), m_cost(DBL_MAX) {
    //Nothing
}

/**
 * Destructor
 */
Solution::~Solution() {
    if(!m_paths.empty()) {
        for (auto &m_path : m_paths) {
            if(!m_path.empty()) {
                m_path.clear();
            }
        }
        m_paths.clear();
    }
}

/**
 * Get Solution's cost
 * @return Cost of this Solution
 */
const double& Solution::getCost() const {
    return m_cost;
}

/**
 * Add a path to this Solution
 * @param path Path to add
 */
void Solution::addPath(const std::vector<unsigned int> &path) {
    m_paths.push_back(path);
}

/**
 * Set Solution's cost
 * @param cost Solution's cost
 */
void Solution::setCost(const double &cost) {
    m_cost = cost;
}

/**
 * Get a string representation of the Solution
 * @return String representing the Solution
 */
const std::string Solution::toString() const {
    std::string result;
    for(unsigned long i(0); i < m_paths.size(); i++) {
        result += "Truck " + std::to_string(i+1) + " : \n";
        for(unsigned long j(0); j < m_paths[i].size(); j++) {
            if(j != 0) {
                result += " -> ";
            }
            result += std::to_string(m_paths[i][j]);
        }
        result += "\n";
    }
    result += "Solution's cost : " + std::to_string(m_cost);
    return result;
}

/**
 *
 * @param index
 * @return path of truck in parameter
 */
const std::vector<unsigned int>& Solution::getPath(const unsigned int index) const {
    assert(index < m_paths.size());
    return m_paths[index];
}
