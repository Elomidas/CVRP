#include <iostream>
#include <cassert>
#include "../include/DistancesMatrix.h"
#include "../include/GraphFactory.h"
#include "../include/TabouAlgorithm.h"
#include "../include/GeneticAlgorithm.h"

unsigned long computeDistance(unsigned int i, unsigned int j);
void testProject();

int main() {
    std::cout << "Main CVRP" << std::endl;
    std::srand(static_cast<unsigned int>(time(nullptr)));
    testProject();
    return 0;
}

std::string vectToStr(const std::vector<unsigned int> &vector) {
    std::string res(std::to_string(vector[0]));
    for (unsigned int i : vector) {
        res += "-" + std::to_string(i);
    }
    return res;
}

bool testGraph() {
    GraphFactory::test("../data/data01.txt");
    return true;
}

bool testDistancesMatrix() {
    return graph::DistancesMatrix::test(&computeDistance, 70);
}

bool testRandomSolution() {
    std::vector<graph::Node> vector = GraphFactory::readFile("../data/data02.txt");
    Graph graph(vector);
    graph.buildRandomSolution();
    Solution solution = graph.getSolution();
    std::clog << "Solution :" << std::endl << solution.toString() << std::endl;
    Graph second(vector);
    second.loadSolution(solution);
    std::clog << "Solution 2 :" << std::endl << second.getSolution().toString() << std::endl;
    second.buildRandomSolution();
    std::clog << "Solution 3 :" << std::endl << second.getSolution().toString() << std::endl;
    std::vector<unsigned int> genetic(graph.getGenetic());
    std::clog << "Gen1 : " << vectToStr(genetic) << std::endl;
    second.loadGenetic(genetic);
    std::clog << "Gen2 : " << vectToStr(second.getGenetic()) << std::endl;
    std::clog << "Solution 3 :" << std::endl << second.getSolution().toString() << std::endl;
    return true;
}

bool testAlgoTabou(){
    TabouAlgorithm tabou = TabouAlgorithm();
    tabou.lancerAlgo();
    return true;
}

unsigned long computeDistance(unsigned int i, unsigned int j) {
    return i + j;
}

void testGeneticLoad() {
    Graph graph(GraphFactory::readFile("../data/data02.txt"));
    double total(0);
    double iterations(1000);

    for(unsigned int i(0); i < iterations; i++) {
        graph.buildRandomSolution();
        std::vector<unsigned int> genetic(graph.getGenetic());
        double res(graph.getCost());
        graph.loadGenetic(genetic);
        res -= graph.getCost();
        total += res;
    }
    total /= iterations;
    std::clog << "Margin : " << total;
}

void testGenetic() {
    GeneticAlgorithm gen(50, "../data/data01.txt", 10000);
    gen.getStatus();
    gen.launch();
}

void testProject() {
    //assert(testDistancesMatrix());
    //assert(testGraph());
    //assert(testAlgoTabou());
    //assert(testRandomSolution());
    //testGeneticLoad();
    testGenetic();
}
