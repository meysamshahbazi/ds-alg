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

vector<vector<int>> read_graph(string path) {
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

	printAdj(adjMatrix);

	for (int k = 0; k < n; k++) {
		for (int from = 0; from < n; from++) {
			for (int to = 0; to < n; to++) {
				int relax = adjMatrix[from][k] + adjMatrix[k][to];
				adjMatrix[from][to] = min (adjMatrix[from][to], relax);
			}
		}
		cout<<"After relaxing with "<<k<<"\n";
		printAdj(adjMatrix);
	}

}

// https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        
    }
};

int main() 
{
	auto adjMatrix = read_graph("../data.txt");
	floyd(adjMatrix);

    return 0;
}

