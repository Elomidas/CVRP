//
// Created by elomidas on 01/05/18.
//

#include <fstream>

#include "../include/Graphviz.h"

/**
 * Create data/tmp.dot, a file containing all info to build graph
 * @param   graph Graph to build
 * @param   title Title of the graph
 * @return  path to created .dot file
 */
std::string Graphviz::fromGraph(const graph::Graph &graph, const std::string &title) {
    std::string fname("../graphviz/tmp.dot");
    auto cost(static_cast<unsigned long>(graph.getCost()));
    std::ofstream data(fname);
    data << "digraph g {" << std::endl
         << "labelloc=\"t\";" << std::endl
         << "label=\"" << title << " (cost = " << cost << ")\";" << std::endl
         << "margin=\"3,3!\";" << std::endl
         << "outputorder=\"edgesfirst\";" << std::endl
         << "node [fontsize = 100, shape=circle, fillcolor=white, style=filled];" <<std::endl;
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

/**
 * Create the .svg graph
 * @param myGraph Graph to build
 * @param out     Image name (without the .svg)
 */
void Graphviz::getImg(const graph::Graph &myGraph, const std::string &out) {
    std::string fname(fromGraph(myGraph, out));
    std::string cmd("dot -Kneato -Tsvg " + fname + " -o ../graphviz/" + out + ".svg");
    system(cmd.c_str());
}
