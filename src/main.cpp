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
void launchProject();

/**
 * main
 * @return
 */
int main() {
    std::cout << "Main CVRP" << std::endl;
    std::srand(static_cast<unsigned int>(time(nullptr)));
    launchProject();
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
bool testAlgoTabou(unsigned int taille, std::string data, unsigned int ite, unsigned int aff) {
    std::string jeu(data);
    TabouAlgorithm tabou(taille, "../data/data"+jeu+".txt", ite, aff);
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
void testGenetic(unsigned int pop, std::string data, unsigned int ite, unsigned int aff) {
    std::string jeu(data);
    GeneticAlgorithm gen(pop, "../data/data"+jeu+".txt", ite, aff);
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
    //assert(testAlgoTabou());
    //assert(testRandomSolution());
    //testGeneticLoad();
    //testGenetic();
    //assert(testOperationsEl());
    //assert(testVoisinage());
    //assert(testGraphviz());
}

/**
 * Main function
 */
void launchProject(){
    unsigned int choice = 0;
    std:: string data;
    unsigned int ite = 0, aff= 0;
    std::cout << "Choisissez l'algorithme à utiliser, 1 pour tabou, 2 pour génétique." << std::endl;
    std:: cin >> choice;
    std:: cout << "Choisissez le jeu de données (01, 02, ..., 05)." << std::endl;
    std:: cin >> data;
    std::cout << "Choisissez le nombre d'itérations total." << std::endl;
    std::cin >> ite;
    std::cout << "Choisissez le nombre d'itérations entre deux affichages." << std::endl;
    std::cin >> aff;
    if(choice == 1){
        unsigned int taille = 0;
        std::cout << "Choisissez la taille de la liste tabou." << std::endl;
        std::cin >> taille;
        testAlgoTabou(taille, data, ite, aff);
    }
    else if (choice == 2){
        unsigned int pop = 0;
        std::cout << "Choisissez la taille de la population." << std::endl;
        std::cin >> pop;
        testGenetic(pop, data, ite, aff);
    }
    std::cout << "Fin du programme";
}