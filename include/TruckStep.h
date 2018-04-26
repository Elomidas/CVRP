//
// Created by elomidas on 28/03/18.
//

#ifndef CVRP_TRUCKSTEP_H
#define CVRP_TRUCKSTEP_H


#include "Node.h"
#include "DistancesMatrix.h"

class TruckStep {

public:
    TruckStep(graph::Node &);
    ~TruckStep();
    bool hasNext() const;
    TruckStep* getNext() const;
    graph::Node& getNode();
    void setNext(TruckStep*);
    unsigned int getId() const;
    int hasNode(unsigned int) const;
    unsigned int getLoad() const;
    unsigned long getDistance(const graph::Node&, const graph::DistancesMatrix&) const;
    void add(graph::Node&);
    void addByIndex(unsigned int, graph::Node&);
    unsigned int delById(unsigned int);
    unsigned int delIndex(unsigned int);
    unsigned int replaceById(unsigned int, graph::Node&);
    unsigned int replaceByIndex(unsigned int, graph::Node&);

private:
    unsigned int replaceNext(graph::Node&);
    unsigned int delNext();
    graph::Node &m_node;
    TruckStep *m_next;

};


#endif //CVRP_TRUCKSTEP_H
