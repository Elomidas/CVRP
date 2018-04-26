#include <iostream>
#include <cassert>
#include "../include/DistancesMatrix.h"
#include "../include/GraphFactory.h"

unsigned long computeDistance(unsigned int i, unsigned int j);
bool testDistancesMatrix();
void testProject();

int main() {
    std::cout << "Main CVRP" << std::endl;
    testProject();
    return 0;
}

bool testGraph() {
    GraphFactory::test("../data/data01.txt");
    return true;
}

bool testDistancesMatrix() {
    return graph::DistancesMatrix::test(&computeDistance, 70);
}

unsigned long computeDistance(unsigned int i, unsigned int j) {
    return i + j;
}

void testProject() {
    //assert(testDistancesMatrix());
    assert(testGraph());
}
