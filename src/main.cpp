#include <iostream>
#include <cassert>
#include <unistd.h>
#include "../include/DistancesMatrix.h"
#include "../include/GraphFactory.h"
#include "../include/TabouAlgorithm.h"
#include "../include/GeneticAlgorithm.h"
#include "../include/Graphviz.h"

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
    //Algorithm algo;
    //TabouAlgorithm tabou = TabouAlgorithm();
    //tabou.lancerAlgo();
    //tabou.lancerAlgo();
    return true;
}

bool testVoisinage(){
    std::vector<graph::Node> vector = GraphFactory::readFile("../data/data01.txt");
    Graph graph(vector);
    graph.buildRandomSolution();

    std::cout << std::endl << std::endl;
    Solution res = graph.getSolution();
    std::cout << res.toString() << std::endl << std::endl;

    std::vector<Graph> voisinage = graph.getVoisinage(std::vector<std::pair<unsigned int, unsigned int>>());

    /*
    Solution base = graph.getSolution();
    for(Graph voisin : voisinage){
        Solution sol = voisin.getSolution();
        std::cout << base.toString() << std::endl << std::endl;
        std::cout << sol.toString() << std::endl << std::endl;
    }
    */
    std::pair<unsigned int , unsigned int> diff = graph.getDifference(voisinage.at(0));
    std::cout << diff.first << std::endl << diff.second <<std::endl << std::endl;

    diff = graph.getDifference(voisinage.at(1));
    std::cout << diff.first << std::endl << diff.second <<std::endl << std::endl;
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

    int num1(15), num2(13);
    std::cin >> num1 >> num2;
    graph.invertNodes(num1, num2);
    res = graph.getSolution();
    std::cout << res.toString() << std::endl << std::endl;


    std::clog << "End of test" <<std::endl;
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
    GeneticAlgorithm gen(50, "../data/data01.txt", 10000, 1000);
    gen.getStatus();
    gen.launch();
}

bool testGraphviz() {
    Graph graph(GraphFactory::readFile("../data/data01.txt"));
    graph.buildRandomSolution();
    //std::clog << Graphviz::fromGraph(graph.getSolution()) << std::endl;
    Graphviz::getImg(graph);
    return true;
}

void testProject() {
    //assert(testDistancesMatrix());
    //assert(testGraph());
    //assert(testAlgoTabou());
    //assert(testRandomSolution());
    //testGeneticLoad();
    //testGenetic();
    //assert(testOperationsEl());
    //assert(testVoisinage());
    //assert(testGraphviz());
}
