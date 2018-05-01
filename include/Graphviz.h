//
// Created by elomidas on 01/05/18.
//

#ifndef CVRP_GRAPHVIZ_H
#define CVRP_GRAPHVIZ_H

#include "Solution.h"
#include "Graph.h"

#define _GRAPH_DIR "../graphviz"

class Graphviz {
public:
    Graphviz();
    int test();
    static std::string fromGraph(const graph::Graph &);
    static void getImg(const graph::Graph &);

private:
    static unsigned int _count;

};


#endif //CVRP_GRAPHVIZ_H
