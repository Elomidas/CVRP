//
// Created by elomidas on 28/04/18.
//

#ifndef CVRP_SOLUTION_H
#define CVRP_SOLUTION_H


#include <vector>
#include <string>

class Solution {
private:
    unsigned long m_cost;
    std::vector< std::vector< unsigned int > > m_paths;

public:
    Solution();
    ~Solution();
    void addPath(const std::vector<unsigned int>&);
    void setCost(const unsigned long &);
    const unsigned long & getCost() const;
    std::string toString() const;

};


#endif //CVRP_SOLUTION_H
