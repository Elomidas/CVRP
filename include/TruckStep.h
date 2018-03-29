//
// Created by elomidas on 28/03/18.
//

#ifndef CVRP_TRUCKSTEP_H
#define CVRP_TRUCKSTEP_H


#include "Node.h"
#include "DistancesMatrix.h"

class TruckStep {
public:
    explicit TruckStep(Node &);
    ~TruckStep();
    bool hasNext() const;
    TruckStep* getNext() const;
    Node& getNode();
    void setNext(TruckStep *);
    unsigned int getId() const;
    int hasNode(unsigned int) const;
    unsigned int getLoad() const;
    unsigned long getDistance(const Node &, const DistancesMatrix &) const;
    void add(Node &);
    void addByIndex(unsigned int, Node &);
    unsigned int delById(unsigned int);
    unsigned int delIndex(unsigned int);
    unsigned int replaceById(unsigned int, Node &);
    unsigned int replaceByIndex(unsigned int, Node &);

private:
    unsigned int replaceNext(Node &);
    unsigned int delNext();
    Node &m_node;
    TruckStep *m_next;

};


#endif //CVRP_TRUCKSTEP_H
