#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <vector>
#include <bitset>
#include "constants.hpp"

class Graph
{
    std::vector<std::vector<int>> graph;
    int qtdVertices;
    int qtdArestas;

public:

    Graph(int);

	Graph(int, const std :: bitset<MAX_E>&);

    Graph();

	void remove_ultima_aresta(int);

    void add_aresta(int, int);

    int grau(int);

    std::vector<int>& adjList(int);

    int getQtdVertices();

    int getQtdArestas();
};


#endif
