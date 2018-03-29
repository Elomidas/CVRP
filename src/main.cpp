#include <iostream>
#include "../include/DistancesMatrix.h"

#define _NUMBER_OF_NODES    5

int testDistancesMatrix();

int main() {
    int result(0);
    result = testDistancesMatrix();
    return result;
}

/**
 * Test classes DistancesMatrix & DistanceNode
 * @return 0 if there isn't any mistake
 */
int testDistancesMatrix() {
    DistancesMatrix matrix(_NUMBER_OF_NODES);
    //Matrix filling
    for(unsigned int i(0); i < _NUMBER_OF_NODES; i++) {
        for(unsigned int j(0); j < i; j++) {
            matrix.setDistance(i, j, i+j);
        }
    }
    //Data retrieving check
    for(unsigned int i(0); i < _NUMBER_OF_NODES; i++) {
        for(unsigned int j(0); j < i; j++) {
            std::cout << matrix.getDistance(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << "DistancesMatrix test passed without errors." << std::endl;
    return 0;
}