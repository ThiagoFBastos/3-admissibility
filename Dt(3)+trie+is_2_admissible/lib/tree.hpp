#ifndef TREE_HPP
#define TREE_HPP

#include <vector>
#include <bitset>
#include <map>
#include "constants.hpp"

class Tree {
	std :: vector<std :: vector<int>> g;
	int n_v, n_e;

	public:

	Tree();

	Tree(int);

	Tree(std :: vector<std :: vector<int>>&);

	Tree(int, std :: vector<int>&);

	std :: bitset<MAX_E> adjacent_matrix();	

	std :: vector<int> all_shortest_paths();	

	int diameter();

	void add_edge(int, int);

	std :: vector<int> center();

	int get_hash(int, int, std :: map<std :: vector<int>, int>&, bool&);	

	int getQtdVertices() const;

	int getQtdArestas() const;

	bool is_tree() const;

	int degree(int) const;

	std :: vector<int>& adjList(int);
};

#endif
