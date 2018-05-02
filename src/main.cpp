#include <iostream>
#include <cassert>
#include "../include/DistancesMatrix.h"
#include "../include/GraphFactory.h"
#include "../include/TabouAlgorithm.h"
#include "../include/GeneticAlgorithm.h"
#include "../include/Graphviz.h"

/**
 * function used
 * @param i
 * @param j
 * @return
 */
unsigned long computeDistance(unsigned int i, unsigned int j);
void testProject();

/**
 * main
 * @return
 */
int main() {
    std::cout << "Main CVRP" << std::endl;
    std::srand(static_cast<unsigned int>(time(nullptr)));
    testProject();
    return 0;
}

/**
 *
 * @param vector
 * @return string which represents the vector
 */
std::string vectToStr(const std::vector<unsigned int> &vector) {
    std::string res(std::to_string(vector[0]));
    for (unsigned int i : vector) {
        res += "-" + std::to_string(i);
    }
    return res;
}

/**
 * test the graph
 * @return
 */
bool testGraph() {
    GraphFactory::test("../data/data01.txt");
    return true;
}

/**
 * test distance matrix
 * @return
 */
bool testDistancesMatrix() {
    return graph::DistancesMatrix::test(&computeDistance, 70);
}

/**
 * test generation of random solution
 * @return
 */
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

/**
 * test tabou algorithm
 * @return
 */
bool testAlgoTabou() {
    std::string jeu("05");
    TabouAlgorithm tabou(10, "../data/data"+jeu+".txt", 100, 20);
    tabou.launchAlgo();
    tabou.display("data"+jeu+"-tabou");
    return true;
}

/**
 * test neighbour generation
 * @return
 */
bool testVoisinage(){
    std::vector<graph::Node> vector = GraphFactory::readFile("../data/data01.txt");
    Graph graph(vector);
    graph.buildRandomSolution();

    std::cout << std::endl << std::endl;
    Solution res = graph.getSolution();
    std::cout << res.toString() << std::endl << std::endl;

    unsigned int id(0);
    std::cin >> id;

    std::vector<ElementaryTransformation> transfo;
    ElementaryTransformation tabou1, tabou2;
    tabou1.setTransfo(2, id, 0, 0);
    tabou2.setTransfo(2, id, 0, 1);
    std::list<ElementaryTransformation> tabouList;
    tabouList.push_back(tabou1);
    tabouList.push_back(tabou2);

    std::vector<Graph> voisinage = graph.getVoisinage(tabouList, transfo);


    Solution base = graph.getSolution();
    for(Graph &voisin : voisinage) {
        Solution sol = voisin.getSolution();
        std::cout << base.toString() << std::endl << std::endl
                  << sol.toString() << std::endl << std::endl;
    }

    //std::pair<unsigned int , unsigned int> diff = graph.getDifference(voisinage.at(0));
    std::cout << transfo[0].getType() << std::endl << transfo[0].getFirstNode() << std::endl << transfo[0].getSecNode() << std::endl << transfo[0].getOldTruck() << std::endl << transfo[0].getOldIndex() <<std::endl << std::endl;

    //diff = graph.getDifference(voisinage.at(1));
    std::cout << transfo[1].getType() << std::endl << transfo[1].getFirstNode() << std::endl << transfo[1].getSecNode() << std::endl << transfo[1].getOldTruck() << std::endl << transfo[1].getOldIndex() <<std::endl << std::endl;
}

/**
 * test elementary operations
 * @return
 */
bool testOperationsEl(){
    std::vector<graph::Node> vector = GraphFactory::readFile("../data/data01.txt");
    Graph graph(vector);

    graph.testElementaryOp();

    std::clog << "End of test" <<std::endl;
    return true;
}

/**
 *
 * @param i
 * @param j
 * @return distance computed
 */
unsigned long computeDistance(unsigned int i, unsigned int j) {
    return i + j;
}

/**
 * test generic algorithm load
 */
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

/**
 * test genetic algorithm
 */
void testGenetic() {
    std::string jeu("01");
    GeneticAlgorithm gen(100, "../data/data"+jeu+".txt", 1000, 100);
    gen.getStatus();
    gen.launchAlgo();
    gen.display("data"+jeu+"_gen");
}

bool testGraphviz() {
    Graph graph(GraphFactory::readFile("../data/data01.txt"));
    graph.buildRandomSolution();
    //std::clog << Graphviz::fromGraph(graph.getSolution()) << std::endl;
    Graphviz::getImg(graph, "test");
    return true;
}

/**
 * Main function of project
 */
void testProject() {
    //assert(testDistancesMatrix());
    //assert(testGraph());
    assert(testAlgoTabou());
    //assert(testRandomSolution());
    //testGeneticLoad();
    //testGenetic();
    //assert(testOperationsEl());
    //assert(testVoisinage());
    //assert(testGraphviz());
}
