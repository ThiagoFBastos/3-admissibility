#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <pthread.h>

#include "lib/tree.hpp"
#include "lib/graph.hpp"
#include "lib/opBasic.hpp"

const int NUM_THREADS = 16;

struct trie_node {
	int next[2];
	trie_node() {
		next[0] = next[1] = -1;
	}
};

using Trie = std :: vector<trie_node>;

int n, m, a, matriz_pos[MAX_V][MAX_V];

pthread_t thread_id[NUM_THREADS];

Trie adm2[NUM_THREADS], adm3[NUM_THREADS];

int args[NUM_THREADS], matriz[NUM_THREADS][MAX_E], deg[NUM_THREADS][MAX_V], P[NUM_THREADS][MAX_V], dist[NUM_THREADS][MAX_E];

std :: pair<int, int> edges[MAX_E];

bool backtrack(int thread_id, Trie& tree, int no, int pos, int e = 0) {
	if(a == pos) return e != n - 1;
	else if(matriz[thread_id][pos] == 0) {
		if(tree[no].next[0] == -1) {
			tree[no].next[0] = tree.size();
			tree.emplace_back();
		}
		if(!backtrack(thread_id, tree, tree[no].next[0], pos + 1, e)) {
			tree[no].next[0] = -1;
			tree.pop_back();
		}
 	} else if(matriz[thread_id][pos] == 1) {	
		if(tree[no].next[1] == -1) {
			tree[no].next[1] = tree.size();
			tree.emplace_back();
		}
		if(!backtrack(thread_id, tree, tree[no].next[1], pos + 1, e + 1)) {
			tree[no].next[1] = -1;
			tree.pop_back();
		}
	} else {
		for(int k = 0; k < 2; ++k) {
			if(tree[no].next[k] == -1) {
				tree[no].next[k] = tree.size();
				tree.emplace_back();
			}
			if(!backtrack(thread_id, tree, tree[no].next[k], pos + 1, e + k)) {
				tree[no].next[k] = -1;
				tree.pop_back();
			}
		}
	}
	return tree[no].next[0] != -1 || tree[no].next[1] != -1;
}

bool backtrack3Sigma(int thread_id, Trie& adm2, int _2, Trie& adm3, int _3, int pos, int max_degree, int e = 0) {
	if(max_degree == n - 1) return false;
	else if(_2 < 0) return backtrack(thread_id, adm3, _3, pos, e);
	else if(a == pos) return false;
	else if(matriz[thread_id][pos] == 0) {
		if(adm3[_3].next[0] == -1) {
			adm3[_3].next[0] = adm3.size();
			adm3.emplace_back();
		}
		bool ans = backtrack3Sigma(thread_id, adm2, adm2[_2].next[0], adm3, adm3[_3].next[0], pos + 1, max_degree, e);
		if(!ans) {
			adm3[_3].next[0] = -1;
			adm3.pop_back();
		}
	} else if(matriz[thread_id][pos] == 1) {
		auto [u, v] = edges[pos];
		++deg[thread_id][u], ++deg[thread_id][v];
		if(adm3[_3].next[1] == -1) {
			adm3[_3].next[1] = adm3.size();
			adm3.emplace_back();
		}
		bool ans = backtrack3Sigma(thread_id, adm2, adm2[_2].next[1], adm3, adm3[_3].next[1], pos + 1, std :: max(max_degree, std :: max(deg[thread_id][u], deg[thread_id][v])), e + 1);
		--deg[thread_id][u], --deg[thread_id][v];
		if(!ans) {
			adm3[_3].next[1] = -1;
			adm3.pop_back();
		}
	} else {
		auto [u, v] = edges[pos];
		for(int k = 0; k < 2; ++k) {
			deg[thread_id][u] += k, deg[thread_id][v] += k;
			if(adm3[_3].next[k] == -1) {
				adm3[_3].next[k] = adm3.size();
				adm3.emplace_back();
			}
			bool ans = backtrack3Sigma(thread_id, adm2, adm2[_2].next[k], adm3, adm3[_3].next[k], pos + 1, std :: max(max_degree, std :: max(deg[thread_id][u], deg[thread_id][v])), e + k);	
			if(!ans) {
				adm3[_3].next[k] = -1;
				adm3.pop_back();
			}
			deg[thread_id][u] -= k, deg[thread_id][v] -= k;
		}
	}
	return adm3[_3].next[0] != -1 || adm3[_3].next[1] != -1;
}

int next_prufer_code(int P[], int m, int carry) {
	for(int i = m - 1; i >= 0 && carry; --i) {
		P[i] += carry;
		carry = P[i] / n;
		P[i] %= n;
	}
	return carry;
}

void* search2Sigma(void *params) {
	int id = *(int*)params;

	if(next_prufer_code(P[id], m, id)) return nullptr;

	adm2[id].emplace_back();

	do
	{
		Tree t(n, P[id]);
		t.all_shortest_paths(dist[id]);
		for(int u = 0, i = 0; u < n; ++u) {
			for(int v = u + 1; v < n; ++v) {
				int d = dist[id][u * n + v];
				matriz[id][i++] = d <= 2 ? d : 0;
			}
		}
		(void)backtrack(id, adm2[id], 0, 0);
	} while(!next_prufer_code(P[id], m, NUM_THREADS));

	return nullptr;
}

void* search3Sigma(void *params) {
	int id = *(int*)params;

	memset(P[id], 0, n * sizeof(int));

	if(next_prufer_code(P[id], m, id)) return nullptr;

	adm3[id].emplace_back();

	do
	{
		Tree t(n, P[id]);
		if(t.diameter() >= 3) {
			int max_degree = 0;
			t.all_shortest_paths(dist[id]);
			for(int u = 0, i = 0; u < n; ++u) {
				for(int v = u + 1; v < n; ++v) {
					int d = dist[id][u * n + v];
					matriz[id][i++] = d <= 3 ? std :: min(d, 2) : 0;
				}
			}
			(void)backtrack3Sigma(id, adm2[0], 0, adm3[id], 0, 0, 0);
		}
	} while(!next_prufer_code(P[id], m, NUM_THREADS));

	return nullptr;
}

void join_trie(Trie& dest, int destno, Trie& src, int srcno) {
	for(int k = 0; k < 2; ++k) {
		if(src[srcno].next[k] != -1) {
			if(dest[destno].next[k] == -1) {
				dest[destno].next[k] = size(dest);
				dest.emplace_back();
			}
			join_trie(dest, dest[destno].next[k], src, src[srcno].next[k]);
		}
	}
}

struct Info {
	char matriz[MAX_E];
	int diam;
	int dT;
	int sigma;
} info;

Graph graph;
int sigma[4], dT[4][MAX_V];
FILE *out;

void dfs(Trie& tree, int no, int pos, int type) {
	if(pos == a) {
		info.sigma = type;
		info.dT = OpBasic :: min_diameter_tree_value(graph);
		info.diam = OpBasic :: diameter(graph);
		fwrite(&info, sizeof(Info), 1, out);
		++sigma[type];
		++dT[type][info.dT];
		return;
	}
	
	if(tree[no].next[1] != -1) {
		auto [u, v] = edges[pos];
		info.matriz[matriz_pos[u][v]] = 1;
		graph.add_aresta(u, v);
		dfs(tree, tree[no].next[1], pos + 1, type);
		graph.remove_ultima_aresta(u);
		graph.remove_ultima_aresta(v);
		info.matriz[matriz_pos[u][v]] = 0;
	}

	if(tree[no].next[0] != -1) dfs(tree, tree[no].next[0], pos + 1, type);
}

int main(int argc, char* argv[]) {

	if(argc < 3) {
		puts("use: ./generator <vertices> <arquivo>");
		return 0;
	}

	out = fopen(argv[2], "wb");

	if(!out) {
		printf("o arquivo %s não foi aberto: %s\n", argv[2], strerror(errno));
		return 0;
	}

	memset(&info, 0, sizeof(Info));

	n = atoi(argv[1]);
	m = n - 2;

	fwrite(&n, sizeof(int), 1, out);

	graph = Graph(n);

	for(int u = 0; u < n; ++u) {
		for(int v = u + 1; v < n; ++v) {
			matriz_pos[u][v] = a;
			edges[a++] = {u, v};
		}
	}

	for(int i = 0; i < NUM_THREADS; ++i) {
		args[i] = i;
		pthread_create(&thread_id[i], nullptr, search2Sigma, &args[i]); 
	}	

	for(int i = 0; i < NUM_THREADS; ++i)
		pthread_join(thread_id[i], nullptr);

	for(int i = 1; i < NUM_THREADS; ++i) {
		if(std :: size(adm2[0]) < std :: size(adm2[i]))
			std :: swap(adm2[0], adm2[i]);
	}

	for(int i = 1; i < NUM_THREADS; ++i)
		join_trie(adm2[0], 0, adm2[i], 0);

	for(int i = 0; i < NUM_THREADS; ++i)
		pthread_create(&thread_id[i], nullptr, search3Sigma, &args[i]);

	for(int i = 0; i < NUM_THREADS; ++i)
		pthread_join(thread_id[i], nullptr);

	for(int i = 1; i < NUM_THREADS; ++i) {
		if(size(adm3[0]) < size(adm3[i]))
			std :: swap(adm3[0], adm3[i]);
	}

	for(int i = 1; i < NUM_THREADS; ++i)
		join_trie(adm3[0], 0, adm3[i], 0);

	dfs(adm2[0], 0, 0, 2);
	dfs(adm3[0], 0, 0, 3);

	for(int k = 2; k <= 3; ++k) {	
		printf("Grafos \\sigma(G) = %d e suas quantidades por atributos\n", k); 
		printf("\\sigma(G)=%d: %d\n", k, sigma[k]);
		for(int i = 1; i <= n; ++i)
			printf("\\sigma(G)=%d e dT(G) = %d: %d (%.3lf%%)\n", k, i, dT[k][i], 100.0 * dT[k][i] / sigma[k]);
		puts("\n");
	}

	fclose(out);

	return 0;
}
