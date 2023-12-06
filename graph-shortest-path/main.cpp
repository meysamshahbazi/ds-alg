#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <bits/stdc++.h> 
#include <unordered_map>
#include <unordered_set>

using namespace std;

const int OO = (int) 10e6;

template<class T>
void print(vector<T> &v)
{
    for (int i = 0; i < (int) v.size(); ++i) {
		cout << v[i] << " ";
	}
    cout<<endl;
}

template<class T>
void print(vector<vector<T>> &vec){
	for(auto &v : vec)
		print(v);
}

vector<vector<int>> createAdjMat(string path) {
	freopen(path.c_str(), "rt", stdin);
	int n, m;	// nodes and edges;
	cin >> n >> m;

	// Initialize all to OO
	vector<vector<int>> adjMatrix = vector<vector<int>>(n, vector<int>(n, OO));

	for (int i = 0; i < n; ++i)
		adjMatrix[i][i] = 0;	// set self loop = 0

	for (int i = 0; i < m; ++i) {
		int from, to, weight;
		cin >> from >> to >> weight;	// 0-based
		if (from == to)
			continue;	// let's ignore even if -ve
		adjMatrix[from][to] = min(adjMatrix[from][to], weight);
	}

	return adjMatrix;
}

vector<vector<int>> createPathMat(string path) {
	freopen(path.c_str(), "rt", stdin);
	int n, m;	// nodes and edges;
	cin >> n >> m;

	// Initialize all to 0
	vector<vector<int>> pathMat = vector<vector<int>>(n, vector<int>(n, 0));

	for (int i = 0; i < m; ++i) {
		int from, to;
		cin >> from >> to;	// 0-based
		pathMat[from][to] += 1;	// add one more path
	}

	return pathMat;
}

void printAdj(const vector<vector<int>> &adjMatrix) {
	int n = adjMatrix.size();

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (adjMatrix[i][j] >= OO)
				cout << "OO" << "\t";
			else
				cout << adjMatrix[i][j] << "\t";
		}
		cout << "\n";
	}
	cout << "**************************\n";
}

void floyd(vector<vector<int>> &adjMatrix) {
	int n = adjMatrix.size();

	// printAdj(adjMatrix);

	for (int k = 0; k < n; k++) {
		for (int from = 0; from < n; from++) {
			for (int to = 0; to < n; to++) {
				int relax = adjMatrix[from][k] + adjMatrix[k][to];
				adjMatrix[from][to] = min(adjMatrix[from][to], relax);
			}
		}
		// cout << "After relaxing with " << k << "\n";
		// printAdj(adjMatrix);
	}
}

// https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        
    }
};

void print_path(vector<vector<int>> &adjMatrix) {
	int n = adjMatrix.size();

	// printAdj(adjMatrix);

	vector<vector<vector<int>>> shortest_paths(n, vector<vector<int>>(n));

	for (int from = 0; from < n; from++) {
		for (int to = 0; to < n; to++) {
			if (adjMatrix[from][to] < OO) 
				shortest_paths[from][to].push_back(to);
		}
	}

	for (int k = 0; k < n; k++) {
		for (int from = 0; from < n; from++) {
			for (int to = 0; to < n; to++) {
				int relax = adjMatrix[from][k] + adjMatrix[k][to];
				if (relax < adjMatrix[from][to]) {
					shortest_paths[from][to] = shortest_paths[from][k];
					shortest_paths[from][to].insert(shortest_paths[from][to].end() , shortest_paths[k][to].begin(), shortest_paths[k][to].end());
					adjMatrix[from][to] = relax;
				}
			}
		}
	}

	for (int from = 0; from < n; from++) {
		for (int to = 0; to < n; to++) {
			cout << "Path from: "<< from<<" to: "<<to <<": ";
			print(shortest_paths[from][to]);
		}
	}

	// cout << "After relaxing\n";
	printAdj(adjMatrix);
}

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=475
void compute_min_max(vector<vector<int>> &graph) {
	int n = graph.size();

	for (int k = 0; k < n; k++) {
		for (int from = 0; from < n; from++) {
			for (int to = 0; to < n; to++) {
				int relax = max(graph[from][k], graph[k][to]);
				graph[from][to] = min(graph[from][to], relax);
			}
		}
		// cout << "After relaxing with " << k << "\n";
	}
	printAdj(graph);
}

// https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=61
void count_paths(vector<vector<int>> &graph)
{
	int n = graph.size();

	for (int k = 0; k < n; k++) {
		for (int from = 0; from < n; from++) {
			for (int to = 0; to < n; to++) {
				graph[from][to] += graph[from][k] * graph[k][to];
			}
		}
	}

	for (int k = 0; k < n; k++)
		if (graph[k][k])	// cycle
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					// if i-j path with k, then infinite paths
					if (graph[i][k] && graph[k][j])
						graph[i][j] = -1;


	printAdj(graph);
}

struct edge {
	int from, w;

	edge(int from, int w) :
			from(from), w(w) {
	}
};

vector<int> BellmanFord(vector<vector<edge>> &fromGraph, int n, int src) {
	vector<vector<int>> dist(n, vector<int>(n, OO)); // used_edge * dsts

	for (int used_edges = 0; used_edges < n; ++used_edges)
		dist[used_edges][src] = 0;

	for (int used_edges = 1; used_edges < n; used_edges++) {
		for (int to = 0; to < n; to++) {
			int ans = dist[used_edges - 1][to];
			for (auto &edge : fromGraph[to]) {
				if (ans > dist[used_edges - 1][edge.from] + edge.w)
					ans = dist[used_edges - 1][edge.from] + edge.w;
			}
			dist[used_edges][to] = ans;
		}
	}

	vector<int> ret(n);
	for (int node = 0; node < n; ++node)
		ret[node] = dist[n - 1][node];

	return ret;
}

// https://leetcode.com/problems/network-delay-time/ : bellman ford
class Solution743 {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        
    }
};

int main() 
{
	auto adjMatrix = createAdjMat("../data.txt");
	floyd(adjMatrix);	
	printAdj(adjMatrix);
	// hw1 p1 
	auto hw1p1 = createAdjMat("../hw1p1.txt");
	print_path(hw1p1);
	// hw1 p2
	auto hw1p2 = createAdjMat("../hw1p2.txt");
	compute_min_max(hw1p2);

	auto hw1p3 = createPathMat("../hw1p3.txt");
	count_paths(hw1p3);

	
	int n = 6;

	vector<vector<edge>> fromGraph(n);
	fromGraph[1] = { { 0, 1 } };
	fromGraph[2] = { { 1, 99 }, { 4, 3 } };
	fromGraph[3] = { { 2, 5 }, { 5, 7 } };
	fromGraph[4] = { { 1, 1 } };
	fromGraph[5] = { { 4, 6 } };

	vector<int> sp = BellmanFord(fromGraph, n, 0);

	for (int i = 0; i < (int) sp.size(); ++i)
		cout << i << " " << sp[i] << "\n";

	return 0;
}

