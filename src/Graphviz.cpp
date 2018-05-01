//
// Created by elomidas on 01/05/18.
//

#include <boost/graph/graphviz.hpp>
#include <graphviz/gvc.h>

#include "../include/Graphviz.h"
#include "../include/Graph.h"

struct vertex_info {
    int color;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, vertex_info> MyGraph;
typedef std::pair<int, int> Edge;

Graphviz::Graphviz() = default;

int Graphviz::test() {
    MyGraph g;
    add_edge(0, 1, g);
    add_edge(1, 2, g);

    g[0].color = 1;

    boost::dynamic_properties dp;
    dp.property("color", get(&vertex_info::color, g));
    dp.property("node_id", get(boost::vertex_index, g));
    write_graphviz_dp(std::cout, g, dp);

    return 0;
}

std::string Graphviz::fromGraph(const graph::Graph &graph) {
    std::string fname("../graphviz/tmp.dot");
    std::ofstream data(fname);
    unsigned int counter(0);
    data << "digraph g {" << std::endl
         << "ratio=\"compress\"" << std::endl
         << "node [fontsize = 100];" <<std::endl;
    for(unsigned int i(0); i < graph.getNodeNb(); i++) {
        const graph::Node &n = graph.getNode(i);
        data << n.getId() << " [pos = \"" << n.getX() << "," << n.getY() << "!\", penwidth=15];" << std::endl;
    }
    Solution s = graph.getSolution();
    std::vector<std::string> colors = {"blue", "red", "black", "green", "orange"};
    for(unsigned int i(0); i < s.getPathNumber(); i++) {
        std::vector<unsigned int> vector(s.getPath(i));
        unsigned int last(0);
        for(const unsigned int &j : vector) {
            if(last != j) {
                data << last << "->" << j << " [color=" << colors[i % colors.size()] << ", penwidth=15];" << std::endl;
                last = j;
            }
        }
    }
    data << "}";

    return fname;
}

void Graphviz::getImg(const graph::Graph &myGraph) {
    std::string fname(fromGraph(myGraph));
    std::string o_arg = std::string("-o") + "../graphviz/image_file.svg";
    char* args[] = {const_cast<char*>("dot"),
                    const_cast<char*>("-Kfdp"),
                    const_cast<char*>("-Tsvg"),
                    const_cast<char*>(fname.c_str()),
                    const_cast<char*>(o_arg.c_str()) };

    const int argc = sizeof(args)/sizeof(args[0]);
    Agraph_t *g, *prev = nullptr;
    GVC_t *gvc;

    gvc = gvContext();
    gvParseArgs(gvc, argc, args);

    while ((g = gvNextInputGraph(gvc)))
    {
        if (prev)
        {
            gvFreeLayout(gvc, prev);
            agclose(prev);
        }
        gvLayoutJobs(gvc, g);
        gvRenderJobs(gvc, g);
        prev = g;
    }

    gvFreeContext(gvc);
}
