#ifndef OP_BASIC_HPP_
#define OP_BASIC_HPP_

#include "graph.hpp"
#include "tree.hpp"

#include <vector>
#include <limits>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
#include <tuple>

#define INF_VALUE std::numeric_limits<int>::max()
#define INF "inf"

class OpBasic
{
	static std :: vector<std :: tuple<int, int, int>> getPath(Graph&, int);

	public:

	static Tree shortest_path_tree(Graph& g, int v);
	static int min_diameter_tree_value(Graph& g);
    static int distance(Graph& g, int v, int u);
    static int diameter(Graph& g);
	static std :: vector<int> shortest_path_dist(Graph&, int);
};

#endif
