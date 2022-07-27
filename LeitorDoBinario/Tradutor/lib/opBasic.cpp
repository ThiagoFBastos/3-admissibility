#include "opBasic.hpp"
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>
#include <utility>

#define DEBUG

std :: vector<int> OpBasic :: shortest_path_dist(Graph& g, int v) {
	std :: vector<int> dist(g.getQtdVertices(), -1);	
	std :: queue<int> q;
	q.push(v);
	dist[v] = 0;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : g.adjList(u)) {
			if(dist[v] != -1) continue;
			dist[v] = 1 + dist[u];
			q.push(v);
		}
	}
	return dist;
}

int OpBasic :: diameter(Graph& g) {
    int maior = 0, n = g.getQtdVertices();
    for(int v = 0; v < n; ++v) {
		auto dist = shortest_path_dist(g, v);
		for(int u = 0; u < n; ++u) {
			if(maior < dist[u])
				maior = dist[u];
		}
    }
    return maior;
}

Tree OpBasic :: shortest_path_tree(Graph& g, int v) {
	int n = g.getQtdVertices();

	Tree t(n);
	std :: vector<int> parent(n, -1);
	std :: queue<int> q;

	parent[v] = v;
	q.push(v);

	while(!q.empty()) {
		int v = q.front();
		q.pop();
		for(int u : g.adjList(v)) {
			if(parent[u] != -1) continue;
			t.add_edge(u, v);
			parent[u] = v;
			q.push(u);
		}
	}

	return t;
}

std :: vector<std :: tuple<int, int, int>> OpBasic :: getPath(Graph& g, int v) {
	int n = g.getQtdVertices(), cur = 0;
	std :: queue<int> q;
	std :: vector<int> dist(n, -1);
	std :: vector<std :: tuple<int, int, int>> path(n);
	dist[v] = 0;
	path[cur++] = std :: make_tuple(v, 0, -1);
	q.push(v);
	while(!q.empty()) {
		int v = q.front();
		q.pop();
		for(int u : g.adjList(v)) {
			if(dist[u] != -1) continue;
			dist[u] = 1 + dist[v];
			path[cur++] = std :: make_tuple(u, dist[u], v);
			q.push(u);
		}
	}
	return path;
}

int OpBasic :: min_diameter_tree_value(Graph& g) {
	int min_diameter = INF_VALUE, n = g.getQtdVertices(), ex = INF_VALUE;
	std :: vector<bool> vis(n);
	std :: vector<std :: vector<std :: tuple<int, int, int>>> path(n);	
	std :: vector<int> id(n);
	std :: queue<int> q;

	for(int v = 0; v < n; ++v) {
		path[v] = getPath(g, v);
		ex = std :: min(ex, std :: get<1>(path[v].back()));
	}

	for(int v = 0; v < n; ++v) {
		if(std :: get<1>(path[v].back()) != ex) continue;

		Tree t(n);

		for(auto [v, d, p] : path[v]) {
			if(p < 0) continue;
			t.add_edge(v, p);
		}

		min_diameter = std :: min(min_diameter, t.diameter());

		for(int u : g.adjList(v)) {
			if(u < v || std :: get<1>(path[u].back()) != ex) continue;

			Tree t(n - 1);

			for(int x = 0; x < n; ++x) {
				vis[x] = false;
				if(x > u) id[x] = x - 1;
				else if(x == u) id[x] = v;
				else id[x] = x;
			}

			vis[u] = vis[v] = true;

			for(int i = 0, j = 0, X = u, Y = v; i < n; ) {
				auto [xu, du, pu] = path[X][i];
				auto [xv, dv, pv] = path[Y][j];
				if(du > dv) {
					std :: swap(X, Y);
					std :: swap(i, j);
					std :: swap(xu, xv);
					std :: swap(pu, pv);
				}
				if(!vis[xu]) {
					vis[xu] = true;
					t.add_edge(id[xu], id[pu]);
				}
				++i;
			}

			min_diameter = std :: min(min_diameter, 1 + t.diameter());
		}
	}

	return min_diameter;
}
