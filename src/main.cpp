#include <iostream>
#include <cassert>
#include "../include/DistancesMatrix.h"
#include "../include/GraphFactory.h"
#include "../include/TabouAlgorithm.h"

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

bool testAlgoTabou(){
    TabouAlgorithm tabou = TabouAlgorithm();
    tabou.lancerAlgo();
    return true;
}

unsigned long computeDistance(unsigned int i, unsigned int j) {
    return i + j;
}

void testProject() {
    //assert(testDistancesMatrix());
    //assert(testGraph());
    assert(testAlgoTabou());
}
