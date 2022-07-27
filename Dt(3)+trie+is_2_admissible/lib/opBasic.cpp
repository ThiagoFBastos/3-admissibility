#include "opBasic.hpp"
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>
#include <utility>
#include <bitset>
#include <ogdf/graphalg/Triconnectivity.h>
#include <ogdf/basic/Graph_d.h>
#include <ogdf/basic/List.h>
#include <ogdf/basic/simple_graph_alg.h>

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

using ii = std :: pair<int, int>;
using vii = std :: vector<ii>;

static const int N = 64;
static int tempo, low[N], in[N], ind[N], visV[N], visVTime, visE[N][N], visETime, deg[N], spdeg[N];
static bool spann[N][N];
static std :: bitset<N> cut[N];
static vii ed[N], E;
static std :: vector<int> st, V;
static ogdf :: node nodes[N];
static std :: vector<vii> triE;
static std :: vector<std :: vector<int>> triV;
static Tree tree;

bool OpBasic :: dfs(Graph& g, int u, int p) {
	low[u] = in[u] = tempo++;

	for(int v : g.adjList(u)) {
		if(v == p) continue;

		else if(in[v] == -1) {

			if(!dfs(g, v, u)) return false;

			if(low[v] < low[u]) low[u] = low[v];

			if(low[v] >= in[u]) {

				// achando um bloco

				E.clear();
				V.clear();
	
				while(!st.empty() && low[st.back()] >= in[u]) {
					int w = st.back();
					for(auto [x, y] : ed[w]) {
						if(visV[x] != visVTime) {
							visV[x] = visVTime;
							V.push_back(x);
						}
						if(visV[y] != visVTime) {
							visV[y] = visVTime;
							V.push_back(y);	
						}
						E.emplace_back(x, y);
					}
					st.pop_back();
				}

				++visVTime;

				// achando componentes triconexos do bloco

				// Triconnectivity não funciona com menos de 3 vértices
				if((int)V.size() < 3) {
					triE.emplace_back(E);
					triV.emplace_back(V);
				} else {
					ogdf :: Graph G;
					int curIndex = 0;

					for(int v : V) {
						ind[v] = curIndex++;
						cut[v].reset();
						nodes[v] = G.newNode(curIndex - 1);
					}

					for(auto [x, y] : E) {
						auto e = G.newEdge(nodes[x], nodes[y]);
						cut[x][y] = 1;
						cut[y][x] = 1;
					}

					ogdf :: Triconnectivity T(G);
					auto GC = T.m_pGC;

					for(auto e : GC->edges) {
				
						if(!GC->isDummy(e)) continue;

						auto nos = e->nodes();
						int x = V[nos[0]->index()], y = V[nos[1]->index()];

						if(!cut[x][y]) return false;
						else if(spann[x][y]) continue;

						tree.add_edge(x, y);
						spann[x][y] = true;
						spann[y][x] = true;
					}

					for(auto& component : T.m_component) {
						auto& edges = component.m_edges;

						if(edges.size() == 0) continue;

						triE.emplace_back(vii());
						triV.emplace_back(std :: vector<int>());

						auto& edgeList = triE.back();
						auto& vertexList = triV.back();

						for(auto e : edges) {
							auto nos = e->nodes();
							int x = V[nos[0]->index()], y = V[nos[1]->index()];

							if(visE[x][y] == visETime) continue;

							if(visV[x] != visVTime) {
								visV[x] = visVTime;
								vertexList.push_back(x);
							}

							if(visV[y] != visVTime) {
								visV[y] = visVTime;
								vertexList.push_back(y);
							}

							edgeList.emplace_back(x, y);
							visE[x][y] = visETime;
							visE[y][x] = visETime;
						}

						++visVTime;
						++visETime;
					}	
				}
			}
		} else if(in[v] < in[u]){
			if(in[v] < low[u]) low[u] = in[v];
			ed[u].emplace_back(u, v);
		}
	}

	st.emplace_back(u);

	if(p != -1) ed[u].emplace_back(p, u);

	return true;
}

bool OpBasic :: is_2_admissible(Graph& g) {

	int n = g.getQtdVertices();

	for(int u = 0; u < n; ++u) {
		ed[u].clear();
		deg[u] = 0;
		spdeg[u] = 0;
		in[u] = -1;
		visV[u] = -1;
		for(int v : g.adjList(u)) {
			visE[u][v] = -1;
			spann[u][v] = false;
		}
	}

	visVTime = 0;
	visETime = 0;
	tempo = 0;	
	st.clear();	
	triE.clear();
	triV.clear();
	tree = Tree(n);

	if(!dfs(g, 0, -1)) return false;

	for(int i = 0; i < (int)triE.size(); ++i) {
		int cntEdges = 0;
		bool flag = false;

		int n = triV[i].size();

		for(auto [x, y] : triE[i]) {
			++deg[x], ++deg[y];
			if(spann[x][y]) {
				++spdeg[x];
				++spdeg[y];
				++cntEdges;
			}
		}

		// procurando estrela geradora
		for(int x : triV[i]) {
			if(spdeg[x] == cntEdges && deg[x] == n - 1) {
				flag = true;
				for(auto [u, v] : triE[i]) {
					if(!spann[u][v] && (u == x || v == x)) {
						spann[u][v] = true;
						tree.add_edge(u, v);
					}
				}
				break;
			}
		}

		if(!flag) return false;

		for(int x : triV[i]) {
			deg[x] = 0;
			spdeg[x] = 0;
		}
	}

	return tree.is_tree();
}
