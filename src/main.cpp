#include <iostream>
#include <cassert>
#include "../include/DistancesMatrix.h"
#include "../include/GraphFactory.h"
#include "../include/TabouAlgorithm.h"

unsigned long computeDistance(unsigned int i, unsigned int j);
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

bool testRandomSolution() {
    std::vector<graph::Node> vector = GraphFactory::readFile("../data/data01.txt");
    Graph graph(vector);
    graph.buildRandomSolution();
    assert(graph.isSolution());
    std::clog << "Solution :" << std::endl << graph.getSolution().toString() << std::endl;
    return true;
}

bool testAlgoTabou(){
    TabouAlgorithm tabou = TabouAlgorithm();
    tabou.lancerAlgo();
    return true;
}

bool testOperationsEl(){
    std::vector<graph::Node> vector = GraphFactory::readFile("../data/data01.txt");
    Graph graph(vector);
    graph.buildRandomSolution();
    std::cout << std::endl << std::endl;
    Solution res = graph.getSolution();
    std::cout << res.toString() << std::endl << std::endl;

    int num, cam, index;
    std::cin >> num >> cam;

    graph.deleteNodeToTruck(num, cam);
    res = graph.getSolution();
    std::cout << res.toString() << std::endl << std::endl;

    graph.addNodeToTruck(num, cam);
    res = graph.getSolution();
    std::cout << res.toString() << std::endl << std::endl;


    std::clog << "End of test" <<std::endl;
    return true;
}

unsigned long computeDistance(unsigned int i, unsigned int j) {
    return i + j;
}

void testProject() {
    //assert(testDistancesMatrix());
    //assert(testGraph());
    //assert(testAlgoTabou());
    //assert(testRandomSolution());
    assert(testOperationsEl());
}
