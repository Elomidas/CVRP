//
// Created by elomidas on 28/04/18.
//

#ifndef CVRP_SOLUTION_H
#define CVRP_SOLUTION_H


#include <vector>
#include <string>

class Solution {
private:
    unsigned double m_cost;
    std::vector< std::vector< unsigned int > > m_paths;

public:
    Solution();
    ~Solution();
    void addPath(const std::vector<unsigned int>&);
    void setCost(const unsigned double &);
    const unsigned double & getCost() const;
    std::string toString() const;

};


#endif //CVRP_SOLUTION_H
