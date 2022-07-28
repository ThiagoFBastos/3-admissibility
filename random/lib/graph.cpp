#include "graph.hpp"

Graph :: Graph(int n) : qtdVertices {n}, qtdArestas {}
{
    graph.resize(n);
}

Graph :: Graph(int n, const std :: bitset<MAX_E>& adj) :  qtdVertices{n}, qtdArestas{}
{
    graph.resize(n);
	for(int u = 0; u < n; ++u) {
		for(int v = 0; v < n; ++v) {
			if(adj[u * n + v]) {
				++qtdArestas;
				graph[u].push_back(v);	
			}
		}
	}
}

Graph :: Graph()
{
    qtdVertices = 0;
    qtdArestas = 0;
}

int Graph :: getQtdVertices() {
	return qtdVertices;
}

int Graph :: getQtdArestas() {
	return qtdArestas;
}

std::vector<int>& Graph :: adjList(int v)
{
    return graph[v];
}

int Graph :: grau(int v)
{
    return graph[v].size();
}

void Graph :: remove_ultima_aresta(int v) {
	graph[v].pop_back();
}

void Graph :: add_aresta(int u, int v) {
	graph[u].push_back(v);
	graph[v].push_back(u);
}
