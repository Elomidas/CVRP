#include <iostream>
#include "../include/DistancesMatrix.h"

unsigned long computeDistance(unsigned int i, unsigned int j) {
    return i + j;
}

int main() {
    return DistancesMatrix::test(&computeDistance, 70);
}
