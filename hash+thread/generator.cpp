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
#include "lib/hash.hpp"

const int NUM_THREADS = 4;

using ed = std :: pair<int, int>;

FILE *out;
int n, m, a, matriz_pos[MAX_V][MAX_V], sigma[4], dT[4][MAX_V];
ed edges[MAX_E];
Hash h;

pthread_t thread_id[NUM_THREADS];
pthread_mutex_t mutex;

struct Info {
	char matriz[MAX_E];
	int diam;
	int dT;
	int sigma;
};

int next_prufer_code(int P[], int m, int carry) {
	for(int i = m - 1; i >= 0 && carry; --i) {
		P[i] += carry;
		carry = P[i] / n;
		P[i] %= n;
	}
	return carry;
}

void backtrack(Info& info, ed matriz[], int m, std :: bitset<MAXN>& adj, Graph& G, int e) {
	if(m < 0) {
		if(e == n - 1) return;
		pthread_mutex_lock(&mutex);
		if(h.insert(adj)) {
			info.diam = OpBasic :: diameter(G);
			info.dT = OpBasic :: min_diameter_tree_value(G);
			info.sigma = 2;
			++dT[2][info.dT];
			fwrite(&info, sizeof(Info), 1, out);
			++sigma[2];
		}
		pthread_mutex_unlock(&mutex);
	} else {
		auto [u, v] = matriz[m];
		int pos = matriz_pos[u][v];

		backtrack(info, matriz, m - 1, adj, G, e);
		
		adj[pos] = 1;
		info.matriz[pos] = 1;
		G.add_edge(u, v);
		backtrack(info, matriz, m - 1, adj, G, e + 1);
		G.rollback();
		adj[pos] = 0;
		info.matriz[pos] = 0;
	}
}

void backtrack(Info& info, ed matriz[], int m, std :: bitset<MAXN>& adj, Graph& G, int max_degree, int e) {
	if(max_degree == n - 1) return;
	else if(m < 0) {
		if(e == n - 1) return;
		pthread_mutex_lock(&mutex);
		if(h.insert(adj)) {
			info.diam = OpBasic :: diameter(G);
			info.dT = OpBasic :: min_diameter_tree_value(G);
			info.sigma = 3;
			++dT[3][info.dT];
			fwrite(&info, sizeof(Info), 1, out);
			++sigma[3];
		}
		pthread_mutex_unlock(&mutex);
	} else {
		auto [u, v] = matriz[m];
		int pos = matriz_pos[u][v];

		backtrack(info, matriz, m - 1, adj, G, max_degree, e);	

		adj[pos] = 1;
		info.matriz[pos] = 1;
		G.add_edge(u, v);
		backtrack(info, matriz, m - 1, adj, G, std :: max(max_degree, std :: max(G.degree(u), G.degree(v))), e + 1);	
		G.rollback();
		adj[pos] = 0;
		info.matriz[pos] = 0;
	}
}

void* search2Sigma(void *params) {
	int id = *(int*)params, P[MAX_V], dist[MAX_E];
	ed matriz[MAX_E];
	std :: bitset<MAXN> adj;
	Info info;

	memset(&info, 0, sizeof(Info));
	memset(P, 0, sizeof(int) * n);

	if(next_prufer_code(P, m, id)) return nullptr;

	do
	{
		Tree t(n, P);
		Graph G(n);
		int i = 0;
		t.all_shortest_paths(dist);
		adj.reset();
		for(int u = 0; u < n; ++u) {
			for(int v = u + 1; v < n; ++v) {
				int d = dist[u * n + v];
				if(d == 1) {
					adj[matriz_pos[u][v]] = 1;
					G.add_edge(u, v);
				} else if(d == 2) matriz[i++] = {u, v};
			}
		}
		backtrack(info, matriz, i - 1, adj, G, n - 1);
	} while(!next_prufer_code(P, m, NUM_THREADS));

	return nullptr;
}

void* search3Sigma(void *params) {
	int id = *(int*)params, P[MAX_V], dist[MAX_E];
	ed matriz[MAX_E];
	std :: bitset<MAXN> adj;
	Info info;

	memset(&info, 0, sizeof(Info));
	memset(P, 0, n * sizeof(int));

	if(next_prufer_code(P, m, id)) return nullptr;

	do
	{
		Tree t(n, P);
		if(t.diameter() >= 3) {
			Graph G(n);
			int i = 0;
			t.all_shortest_paths(dist);
			adj.reset();
			for(int u = 0; u < n; ++u) {
				for(int v = u + 1; v < n; ++v) {
					int d = dist[u * n + v];
					if(d == 1) {
						adj[matriz_pos[u][v]] = 1;
						G.add_edge(u, v);
					} else if(d <= 3) matriz[i++] = {u, v};
				}
			}
			backtrack(info, matriz, i - 1, adj, G, 0, n - 1);
		}
	} while(!next_prufer_code(P, m, NUM_THREADS));

	return nullptr;
}

int main(int argc, char* argv[]) {
	
	int args[NUM_THREADS];

	if(argc < 3) {
		puts("use: ./generator <vertices> <arquivo>");
		return 0;
	}

	
	out = fopen(argv[2], "wb");

	if(!out) {
		printf("o arquivo %s não foi aberto: %s\n", argv[2], strerror(errno));
		return 0;
	}

	n = atoi(argv[1]);
	m = n - 2;

	h.load("hash.dat", "head.dat");

	for(int u = 0; u < n; ++u) {
		for(int v = u + 1; v < n; ++v) {
			matriz_pos[u][v] = a;
			edges[a++] = {u, v};
		}
	}

	pthread_mutex_init(&mutex, nullptr);

	for(int i = 0; i < NUM_THREADS; ++i) {
		args[i] = i;
		pthread_create(&thread_id[i], nullptr, search2Sigma, &args[i]); 
	}

	for(int i = 0; i < NUM_THREADS; ++i) 
		pthread_join(thread_id[i], nullptr);

	for(int i = 0; i < NUM_THREADS; ++i)
		pthread_create(&thread_id[i], nullptr, search3Sigma, &args[i]); 

	for(int i = 0; i < NUM_THREADS; ++i) 
		pthread_join(thread_id[i], nullptr);

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
