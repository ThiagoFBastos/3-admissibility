#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <vector>
#include <utility>
#include "constants.hpp"

class Graph
{
    std :: vector<std::vector<int>> graph;
	std :: vector<std :: pair<int, int>> edges;
    int qtdVertices;
    int qtdArestas;

public:

    Graph(int);

    Graph();

	void rollback();

    void add_edge(int, int);

    int degree(int) const;

    std::vector<int>& adjList(int);

    int getQtdVertices();

    int getQtdArestas();
};


#endif
