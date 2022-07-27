#include "tree.hpp"
#include <queue>
#include <algorithm>

Tree :: Tree() {
	n_v = n_e = 0;
}

Tree :: Tree(int n) {
	n_v = n;
	n_e = 0;
	g.resize(n);
}

Tree :: Tree(std :: vector<std :: vector<int>>& adj) : g {adj} {
	n_v = adj.size();
	n_e = 0;
	for(auto& A : adj) n_e += size(A);
	n_e /= 2;
}

Tree :: Tree(int n, std :: vector<int>& prufer) {
	g.resize(n);
	
	std :: vector<int> deg(n, 0);
	int pq = 0;

	for(int v : prufer) ++deg[v];
	for(int v = 0; v < n; ++v) if(!deg[v]) pq |= 1 << v;
	
	for(int v : prufer) {
		int u = __builtin_ctz(pq);
		pq ^= pq & -pq;
		g[u].push_back(v);
		g[v].push_back(u);
		if(--deg[v] == 0) pq |= 1 << v;
	}

	int u = __builtin_ctz(pq);
	int v = __builtin_ctz(pq ^ (pq & -pq));

	g[u].push_back(v);
	g[v].push_back(u);
}

std :: vector<int> Tree :: all_shortest_paths() {
	int n = g.size();
	std :: vector<int> d(n * n, -1);
	for(int u = 0; u < n; ++u) {
		std :: queue<int> q;
		d[u * n + u] = 0;
		q.push(u);
		while(!q.empty()) {
			int v = q.front();
			q.pop();
			for(int w : g[v]) {
				if(d[u * n + w] != -1) continue;
				d[u * n + w] = 1 + d[u * n + v];
				q.push(w);
			}
		}
	}
	return d;
}

std :: bitset<MAX_E> Tree :: adjacent_matrix() {
	std :: bitset<MAX_E> mat;
	int n = g.size();
	for(int u = 0; u < n; ++u)
	for(int v : g[u])
		mat[u * n + v] = 1;
	return mat;
}

int Tree :: diameter() {
	int n = g.size(), dim = -1, cnt = 0;
	std :: queue<int> q;
	std :: vector<int> deg(n), t(n, -1);
	for(int u = 0; u < n; ++u) {
		deg[u] = g[u].size();
		if(deg[u] <= 1) {
			t[u] = 0;
			q.push(u);
		}
	}
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		if(t[u] > dim) cnt = 1, dim = t[u];
		else if(dim == t[u]) ++cnt;
		for(int v : g[u]) {
			if(--deg[v] != 1) continue;
			t[v] = 1 + t[u];
			q.push(v);
		}
	}
	return 2 * dim + cnt - 1;
}

void Tree :: add_edge(int u, int v) {
	++n_e;
	g[u].push_back(v);
	g[v].push_back(u);
}

std :: vector<int> Tree :: center() {
	int n = g.size(), last = -1;
	std :: queue<int> q;
	std :: vector<int> deg(n), t(n, -1), c;
	for(int u = 0; u < n; ++u) {
		deg[u] = g[u].size();
		if(deg[u] <= 1) {
			t[u] = 0;
			q.push(u);
		}
	}
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		if(last < t[u]) last = t[u];
		for(int v : g[u]) {
			if(--deg[v] != 1) continue;
			t[v] = 1 + t[u];
			q.push(v);
		}
	}
	for(int u = 0; u < n; ++u) if(t[u] == last) c.push_back(u);
	return c;
}

int Tree :: get_hash(int u, int p, std :: map<std :: vector<int>, int>& hash, bool& newlist) {
	std :: vector<int> L;
	for(int v : g[u]) {
		if(v == p) continue;
		L.push_back(get_hash(v, u, hash, newlist));
	}
	std :: sort(L.begin(), L.end());
	newlist = false;
	if(!hash.count(L)) {
		newlist = true;
		hash[L] = hash.size();
	}
	return hash[L];
}

int Tree :: getQtdVertices() const {
	return n_v;
}

int Tree :: getQtdArestas() const {
	return n_e;
}

bool Tree :: is_tree() const {
	std :: queue<int> q;
	std :: vector<bool> vis(n_v, false);
	int cntVis = 0;
	q.push(0);
	vis[0] = true;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		++cntVis;
		for(int v : g[u]) {
			if(vis[v]) continue;
			vis[v] = true;
			q.push(v);
		}
	}
	return cntVis == n_v && n_v - 1 == n_e;
}

int Tree :: degree(int v) const {
	return g[v].size();
}

std :: vector<int>& Tree :: adjList(int u) {
	return g[u];
}
