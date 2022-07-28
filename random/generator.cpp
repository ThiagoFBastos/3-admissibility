#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <random>
#include <chrono>
#include <cerrno>

//#define DEBUG

#include "lib/tree.hpp"
#include "lib/graph.hpp"
#include "lib/opBasic.hpp"

const int NUM_THREADS = 16;

struct Info {
	char matriz[MAX_E];
	int diam;
	int dT;
	int sigma;
} info;

FILE *out;

int n, m, arestas, instancias, matriz_pos[MAX_E];

pthread_t thread_id[NUM_THREADS];

pthread_mutex_t mutex;

std :: pair<int, int> edges[MAX_E], args[NUM_THREADS];

void* search(void *params) {
	auto [id, instancias] = *(std :: pair<int, int>*)params;
	std :: mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
	Info info;
	OpBasic op;
	int P[MAX_V], dist[MAX_E];

	for(int i = 0; i < instancias; ++i) {

		for(int j = 0; j < m; ++j) 
			P[j] = rng() % n;

		Tree t(n, P);
		Graph g(n);
		std :: vector<std :: pair<int, int>> ed;

		t.all_shortest_paths(dist);
		
		memset(info.matriz, 0, sizeof(char) * arestas);

		for(int u = 0, k = 0; u < n; ++u) {
			for(int v = u + 1; v < n; ++v, ++k) {
				int d = dist[u * n + v];
				if(d == 1) {
					info.matriz[k] = 1;
					g.add_aresta(u, v);
				} else if(d <= 3) ed.emplace_back(u, v);
			}
		}

		std :: shuffle(ed.begin(), ed.end(), rng);

		int n_a = rng() % ed.size() + 1;

		for(int i = 0; i < n_a; ++i) {
			auto [u, v] = ed[i];
			info.matriz[matriz_pos[u * n + v]] = 1;
			g.add_aresta(u, v);
		}

		info.sigma = op.is_2_admissible(g) ? 2 : 3;
		info.diam = op.diameter(g);
		info.dT = op.min_diameter_tree_value(g);

		pthread_mutex_lock(&mutex);
		fwrite(&info, sizeof(Info), 1, out);
		pthread_mutex_unlock(&mutex);
	}

	return nullptr;
}

int main(int argc, char* argv[]) {

	if(argc < 4) {
		puts("use: ./generator <vertices> <instâncias> <arquivo>");
		return 0;
	}

	n = atoi(argv[1]);
	m = n - 2;
	instancias = atoi(argv[2]);

	for(int u = 0; u < n; ++u) {
		for(int v = u + 1; v < n; ++v) {
			matriz_pos[u * n + v] = arestas;
			edges[arestas++] = {u, v};
		}
	}

	if(!(out = fopen(argv[3], "wb"))) {
		printf("erro ao abrir %s: %s\n", argv[3], strerror(errno));
		return 0;	
	}

	pthread_mutex_init(&mutex, nullptr);

	for(int i = 0; i < NUM_THREADS; ++i) {
		args[i] = {i, instancias / NUM_THREADS + (instancias % NUM_THREADS > 0)};	
		pthread_create(&thread_id[i], nullptr, search, &args[i]); 
	}

	for(int i = 0; i < NUM_THREADS; ++i)
		pthread_join(thread_id[i], nullptr);
	
	fclose(out);

	return 0;
}
