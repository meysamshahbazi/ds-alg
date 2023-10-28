#include<iostream>
#include<vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>

using namespace std;

typedef vector<vector<int>> GRAPH;

void add_directed_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
}

void add_directed_edge(GRAPH &graph, vector<vector<int>> &nodes_edge) {
	for(auto &item:nodes_edge) {
		int from = item[0];
		int to = item[1];
		add_directed_edge(graph, from, to);
	}
}


void print_adjaceny_matrix(GRAPH &graph) {
	int nodes = graph.size();
	for (int from = 0; from < nodes; ++from) {
		cout << "Node " << from << " has neighbors: ";
		for (int to = 0; to < (int) graph[from].size(); ++to)
			cout << graph[from][to] << " ";
		cout << "\n";
	}
}

void dfs(GRAPH &graph, int node, vector<bool> &visited) {
	visited[node] = true;
	for(int neighbour : graph[node]) {
		if (!visited[neighbour]) {
			cout<<"\tWe can reach " << neighbour <<"\n";
			dfs(graph, neighbour, visited);
		}
	}
}

void reachability(GRAPH &graph) {
	int nodes = graph.size();
	for (int i = 0; i < nodes; ++i) {
		vector<bool> visited(nodes);	// RESET
		cout << "Reachable set of node " << i << "\n";
		dfs(graph, i, visited);
	}
}

int main()
{
	vector<vector<int>> nodes_edge = { {2, 0}, {0 ,1}, {1 ,4}, {4 ,3}, {3 ,1}, {1 ,0}, {0 ,3}, {5 ,6}, {6 ,6} };
	GRAPH test_graph(7);
	add_directed_edge(test_graph, nodes_edge);
	print_adjaceny_matrix(test_graph);
	reachability(test_graph);
    return 0;
}


