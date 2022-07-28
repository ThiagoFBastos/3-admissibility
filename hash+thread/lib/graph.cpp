#include "graph.hpp"

Graph :: Graph(int n) : qtdVertices {n}, qtdArestas {} {
    graph.resize(n);
}

Graph :: Graph() {
    qtdVertices = 0;
    qtdArestas = 0;
}

int Graph :: getQtdVertices() {
	return qtdVertices;
}

int Graph :: getQtdArestas() {
	return qtdArestas;
}

std::vector<int>& Graph :: adjList(int v) {
    return graph[v];
}

int Graph :: degree(int v) const {
    return graph[v].size();
}

void Graph :: rollback() {
	auto [u, v] = edges.back();
	edges.pop_back();
	graph[u].pop_back();
	graph[v].pop_back();
}

void Graph :: add_edge(int u, int v) {
	graph[u].push_back(v);
	graph[v].push_back(u);
	edges.emplace_back(u, v);
}
