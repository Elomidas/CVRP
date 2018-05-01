//
// Created by bastien on 01/05/18.
//

#ifndef CVRP_ELEMENTARYTRANSFORMATION_H
#define CVRP_ELEMENTARYTRANSFORMATION_H


#include <vector>

class ElementaryTransformation {

private:
    unsigned int m_type; // 0 --> init, 1 --> invert, 2 --> moove
    unsigned int  m_firstNode;
    unsigned int m_secondNode;
    unsigned int m_Truck;
    unsigned int m_Index;

public:
    ElementaryTransformation();
    ~ElementaryTransformation();

    const unsigned int getType() const { return m_type; };
    void setType(unsigned int type) { m_type = type; };
    const unsigned int getFirstNode() const {return m_firstNode; };
    void setFirstNode(unsigned int node) { m_firstNode = node; };
    const unsigned int getSecNode() const { return  m_secondNode; };
    void setSecNode(unsigned int secNode) {m_secondNode = secNode; };
    const unsigned int getOldTruck() const { return m_Truck; };
    void SetOldTruck(unsigned int old_truck) { m_Truck = old_truck; };
    const unsigned int getOldIndex() const { return m_Index; };
    void setOldIndex(unsigned int oldIndex) { m_Index = oldIndex; };
    void setTransfo(unsigned int type, unsigned int firstNode, unsigned int secondNode);
    void setTransfo(unsigned int type, unsigned int firstNode, unsigned int truck, unsigned int index);
};


#endif //CVRP_ELEMENTARYTRANSFORMATION_H
