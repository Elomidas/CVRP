//
// Created by elomidas on 28/03/18.
//

#ifndef CVRP_TRUCK_H
#define CVRP_TRUCK_H

#include <vector>
#include "TruckStep.h"

#define _CAPACITY   100

class Truck {
public:
    Truck(const Truck &);
    explicit Truck(const Truck &, std::vector<graph::Node> &);
    explicit Truck(graph::Node &, unsigned int);
    ~Truck();

    double getDistance(const graph::DistancesMatrix &) const;
    unsigned int getIndex() const {return m_index;};
    unsigned int getTruckLoad() const;
    unsigned int getComputedLoad();
    void computeLoad();
    unsigned int getAvailableCapacity() const;
    void addState(graph::Node &);
    void addStateByIndex(unsigned int, graph::Node &);
    void removeStateById(unsigned int);
    void removeStateByIndex(unsigned int);
    void replaceStateById(unsigned int, graph::Node &);
    void replaceStateByIndex(unsigned int, graph::Node &);
    int hasNode(unsigned int) const;
    int hasNode(const graph::Node &) const;
    static unsigned int getCapacity();
    bool isValid() const;
    unsigned int getSize() const;
    std::vector<unsigned int> toVector() const;

private:
    const static unsigned int m_capacity = _CAPACITY;
    TruckStep *m_origin;
    unsigned int m_currentLoad;
    unsigned int m_size;
    unsigned int m_index;
};


#endif //CVRP_TRUCK_H
