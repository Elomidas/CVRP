//
// Created by elomidas on 28/04/18.
//

#ifndef CVRP_SOLUTION_H
#define CVRP_SOLUTION_H


#include <vector>
#include <string>

class Solution {
private:
    double m_cost;
    std::vector< std::vector< unsigned int > > m_paths;

public:
    Solution();
    ~Solution();
    std::vector< std::vector< unsigned int > > getPaths() const { return m_paths; };
    void addPath(const std::vector<unsigned int>&);
    void setCost(const double &);
    const double & getCost() const;
    const std::string toString() const;
    unsigned long getPathNumber() const {return m_paths.size();};
    const std::vector<unsigned int>& getPath(unsigned int) const;
};


#endif //CVRP_SOLUTION_H
