#include <iostream>
#include <cassert>
#include "../include/DistancesMatrix.h"

unsigned long computeDistance(unsigned int i, unsigned int j);
bool testDistancesMatrix();
void testProject();

int main() {
    std::cout << "Main CVRP" << std::endl;
    testProject();
    return 0;
}

bool testDistancesMatrix() {
    return DistancesMatrix::test(&computeDistance, 70);
}

unsigned long computeDistance(unsigned int i, unsigned int j) {
    return i + j;
}

void testProject() {
    assert(testDistancesMatrix());
}
