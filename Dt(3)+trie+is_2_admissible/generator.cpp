#include <iostream>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <cerrno>

//#define DEBUG

#include "lib/tree.hpp"
#include "lib/graph.hpp"
#include "lib/opBasic.hpp"

struct Trie {
	int next[2];
	Trie() {
		next[0] = next[1] = -1;
	}
};

std :: vector<Trie> node(1);
char matriz[MAX_E];
int matriz_pos[MAX_E], n, m, a, deg[MAX_V];
std :: pair<int, int> edges[MAX_E];

bool backtrack(int no, int pos, int max_degree, int e) {
	if(max_degree == n - 1) return false;
	else if(pos == a) return e != n - 1;
	else if(matriz[pos] == 0) {
		if(node[no].next[0] == -1) {
			node[no].next[0] = node.size();
			node.emplace_back();
		}
		if(!backtrack(node[no].next[0], pos + 1, max_degree, e)) {
			node[no].next[0] = -1;
			node.pop_back();
		}
 	} else if(matriz[pos] == 1) {	
		auto [u, v] = edges[pos];
		++deg[u], ++deg[v];
		if(node[no].next[1] == -1) {
			node[no].next[1] = node.size();
			node.emplace_back();
		}
		if(!backtrack(node[no].next[1], pos + 1, std :: max(max_degree, std :: max(deg[u], deg[v])), e + 1)) {
			node[no].next[1] = -1;
			node.pop_back();
		}
		--deg[u], --deg[v];
	} else {
		auto [u, v] = edges[pos];
		for(int k = 0; k < 2; ++k) {
			deg[u] += k, deg[v] += k;
			if(node[no].next[k] == -1) {
				node[no].next[k] = node.size();
				node.emplace_back();
			}
			if(!backtrack(node[no].next[k], pos + 1, std :: max(max_degree, std :: max(deg[u], deg[v])), e + k)) {
				node[no].next[k] = -1;
				node.pop_back();
			}
			deg[u] -= k, deg[v] -= k;
		}
	}
	return node[no].next[0] != -1 || node[no].next[1] != -1;
}

struct Info {
	char matriz[MAX_E];
	int diam;
	int dT;
	int sigma;
} info;

FILE *out;
Graph graph;
int sigma[4];

void build(int no, int pos) {
	if(pos == a) {
		info.sigma = OpBasic :: is_2_admissible(graph) ? 2 : 3;
		info.diam = OpBasic :: diameter(graph);
		info.dT = 3;
		fwrite(&info, sizeof(Info), 1, out);
		++sigma[info.sigma];
	} else {
		if(node[no].next[1] != -1) {
			auto [u, v] = edges[pos];
			info.matriz[matriz_pos[u * n + v]] = 1;
			graph.add_aresta(u, v);
			build(node[no].next[1], pos + 1);
			graph.remove_ultima_aresta(u);
			graph.remove_ultima_aresta(v);
			info.matriz[matriz_pos[u * n + v]] = 0;
		}
		if(node[no].next[0] != -1) build(node[no].next[0], pos + 1);
	}
}

int main(int argc, char* argv[]) {

	if(argc < 3) {
		puts("use: ./generator <vertices> <arquivo>");
		return 0;
	}

	memset(&info, 0, sizeof(Info));

	out = fopen(argv[2], "wb");

	if(!out) {
		printf("o arquivo %s não foi aberto: %s\n", argv[2], strerror(errno));
		return 0;
	}

	n = atoi(argv[1]);
	m = n - 2;

	fwrite(&n, sizeof(int), 1, out);

	for(int u = 0; u < n; ++u) {
		for(int v = u + 1; v < n; ++v) {
			matriz_pos[u * n + v] = a;
			edges[a++] = {u, v};
		}
	}

	graph = Graph(n);

	for(int i = 0; i < a; ++i) {	
		auto [u, v] = edges[i];
		int S = ((1 << n) - 1) ^ (1 << u) ^ (1 << v);
		for(int P = S & (S - 1); P; P = (P - 1) & S) {
			memset(matriz, 2, sizeof(char) * a);
			for(int k = 0; k < n; ++k) {
				if(v == k) continue;
				else if(P & (1 << k))
					matriz[matriz_pos[std :: min(u, k) * n + std :: max(u, k)]] = 1;
				else 
					matriz[matriz_pos[std :: min(v, k) * n + std :: max(v, k)]] = 1;
			}
			(void)backtrack(0, 0, 0, 0);
		}
	}

	build(0, 0);

	for(int k = 2; k <= 3; ++k) {	
		printf("Grafos \\sigma(G) = %d e suas quantidades por atributos\n", k); 
		printf("\\sigma(G)=%d: %d\n\n", k, sigma[k]);
	}

	fclose(out);

	return 0;
}
