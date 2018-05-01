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
    static std::string fromGraph(const graph::Graph &, const std::string &);
    static void getImg(const graph::Graph &, const std::string &);

private:
    static unsigned int _count;

};


#endif //CVRP_GRAPHVIZ_H
