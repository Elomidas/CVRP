//
// Created by elomidas on 28/03/18.
//

#ifndef CVRP_TRUCKSTEP_H
#define CVRP_TRUCKSTEP_H


#include <vector>
#include "Node.h"
#include "DistancesMatrix.h"

class TruckStep {

public:
    TruckStep(const TruckStep &);
    explicit TruckStep(graph::Node &, unsigned int);
    explicit TruckStep(const TruckStep &, std::vector<graph::Node> &, unsigned int);
    ~TruckStep();

    bool hasNext() const;
    TruckStep* getNext() const;
    graph::Node& getNode();
    void setNext(TruckStep*);
    unsigned int getId() const;
    int hasNode(unsigned int) const;
    unsigned int getLoad() const;
    double getDistance(const graph::Node&, const graph::DistancesMatrix&) const;
    unsigned int getSize() const;
    void add(graph::Node&);
    void addByIndex(unsigned int, graph::Node&);
    unsigned int delById(unsigned int);
    unsigned int delIndex(unsigned int);
    unsigned int replaceById(unsigned int, graph::Node&);
    unsigned int replaceByIndex(unsigned int, graph::Node&);
    std::vector<unsigned int> toVector(std::vector<unsigned int> &) const;

private:
    unsigned int replaceNext(graph::Node&);
    unsigned int delNext();
    graph::Node &m_node;
    TruckStep *m_next;
    unsigned int m_truckId;

};


#endif //CVRP_TRUCKSTEP_H
