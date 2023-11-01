#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>

using namespace std;

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

typedef vector<vector<int>> GRAPH;
const int OO = 10000000;	// A big value expressing infinity

void add_undirected_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
	graph[to].push_back(from);
}

void add_undirected_edge(GRAPH &graph, vector<vector<int>> &nodes_edge) {
	for(auto &item:nodes_edge) {
		int from = item[0];
		int to = item[1];
		add_undirected_edge(graph, from, to);
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

vector<int> BFS_v1(GRAPH &adjlist, int start)
{
	vector<int> len(adjlist.size(), OO);
	queue<pair<int,int> > q;
	q.push({start, 0});
	len[start] = 0;

	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();

		int cur = p.first, level = p.second;

		for (int neighbour : adjlist[cur]) 
			if (len[neighbour] == OO) { // havnt visited
				q.push( {neighbour, level + 1});
				len[neighbour] = level + 1;
			}
	}
	return len;
}

vector<int> BFS_v2(GRAPH &adjlist, int start)
{
	vector<int> len(adjlist.size(), OO);
	queue<int> q;
	q.push(start);
	len[start] = 0;

	for (int level = 0, sz = 1; !q.empty(); ++level, sz = q.size() ) {
		while (sz--){
			int cur = q.front();
			q.pop();
			for (int neighbour : adjlist[cur]) 
				if (len[neighbour] == OO) { // havnt visited
					q.push(neighbour);
					len[neighbour] = level + 1;
				}
		}
	}

	return len;
}

int main()
{
	vector<vector<int>> nodes_edge = { {2, 0}, {0 ,1}, {1 ,4}, {4 ,3}, {3 ,1}, {1 ,0}, {0 ,3}, {5 ,6}, {6 ,6} };
	GRAPH test_graph(7);
	add_undirected_edge(test_graph, nodes_edge);
	print_adjaceny_matrix(test_graph);
	vector<int> bfs1 = BFS_v1(test_graph, 0);
	print(bfs1);

	vector<int> bfs2 = BFS_v2(test_graph, 0);
	print(bfs2);
    return 0;
}
