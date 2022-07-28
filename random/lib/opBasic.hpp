#ifndef OP_BASIC_HPP_
#define OP_BASIC_HPP_

#include "graph.hpp"
#include "tree.hpp"

#include <bitset>
#include <utility>
#include <vector>
#include <tuple>
#include <ogdf/basic/Graph_d.h>

class OpBasic
{
	static const int N = 32;
	int tempo, low[N], in[N], ind[N], visV[N], vID, eID, visE[N][N], deg[N], spdeg[N];
	bool spann[N][N];
	std :: bitset<N> cut[N];
	std :: vector<std :: pair<int, int>> edBlock[N];
	std :: vector<int> stV;
	ogdf :: node nodes[N];
	std :: vector<std :: vector<std :: pair<int, int>>> triE;
	std :: vector<std :: vector<int>> triV;
	Tree tree;

	bool dfs(Graph&, int, int);
	std :: vector<std :: tuple<int, int, int>> getPath(Graph&, int);

	public:

	Tree shortest_path_tree(Graph& g, int v);
	int min_diameter_tree_value(Graph& g);
    int distance(Graph& g, int v, int u);
    int diameter(Graph& g);
	std :: vector<int> shortest_path_dist(Graph&, int);
	bool is_2_admissible(Graph&);
};

#endif
