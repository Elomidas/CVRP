//
// Created by elomidas on 28/03/18.
//

#ifndef CVRP_TRUCK_H
#define CVRP_TRUCK_H

#include "TruckStep.h"

#define _CAPACITY   100

class Truck {
public:
    explicit Truck(Node &);
    ~Truck();
    unsigned long getDistance(const DistancesMatrix &) const;
    unsigned int getTruckLoad() const;
    unsigned int getComputedLoad();
    void addState(Node &);
    void addStateByIndex(unsigned int, Node &);
    void removeStateById(unsigned int);
    void removeStateByIndex(unsigned int);
    void replaceStateById(unsigned int, Node &);
    void replaceStateByIndex(unsigned int, Node &);
    int hasNode(unsigned int) const;
    int hasNode(const Node &) const;
    static unsigned int getCapacity();

private:
    const static unsigned int m_capacity = _CAPACITY;
    TruckStep *m_origin;
    unsigned int m_currentLoad;
    unsigned int m_size;
};


#endif //CVRP_TRUCK_H
