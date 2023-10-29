#include<iostream>
#include<vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>

using namespace std;

template<class T>
void print(vector<T> &v)
{
    for (int i = 0; i < (int) v.size(); ++i) {
		cout << v[i] << " ";
	}
    cout<<endl;
}


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

typedef unordered_map<int, vector<int>> GRAPHMP;

void dfs(GRAPHMP &graph, int node, unordered_set<int> &visited, vector<int> &childs) {
	visited.insert(node);
	childs.push_back(node);
	for (auto neighbour : graph[node]) {
		if (visited.count(neighbour) == 0) {
			dfs(graph, neighbour, visited, childs);
		}
	}
}

// https://leetcode.com/problems/kill-process/
vector<int> killProcess(vector<int> &pid, vector<int> &ppid, int kill) {
	int nodes = (int) pid.size();
	GRAPHMP graph;

	for (int i = 0; i < nodes; i++)
		graph[ppid[i]].push_back(pid[i]);
	
	vector<int> childs;
	unordered_set<int> visited;
	dfs(graph, kill, visited, childs);
	
	return childs;
}

// https://leetcode.com/problems/employee-importance/
class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};

typedef unordered_map<int, pair<int, vector<int>> > GRAPHEM;

int dfs(GRAPHEM &graph, int node)
{
	int res = graph[node].first;
	for (auto neighbour: graph[node].second) {
			res += dfs(graph, neighbour);
	}
	return res;
}

int getImportance(vector<Employee*> employees, int id) {
	GRAPHEM graph;

	for (auto &e: employees)
		graph[e->id] = make_pair(e->importance, e->subordinates);
	// No need for visited array in DAG, as no cycles :)
	unordered_set<int> visited;
	return dfs(graph, id);
}


void dfs2(GRAPH &graph, int node, vector<bool> &visited) {
	visited[node] = true;
	for(int neighbour : graph[node]) {
		if (!visited[neighbour]) {
			dfs2(graph, neighbour, visited);
		}
	}
}

// https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/
int countComponents(int n, vector<vector<int>>& edges) {
	GRAPH graph(n);
	add_directed_edge(graph, edges);
	vector<bool> visited(n);
	int cc = 0;
	for (int i = 0; i < n; ++i) {
		if (!visited[i]) {
			dfs2(graph, i, visited);
			cc++;
		}
	}
	return cc;
}

int main()
{
	vector<vector<int>> nodes_edge = { {2, 0}, {0 ,1}, {1 ,4}, {4 ,3}, {3 ,1}, {1 ,0}, {0 ,3}, {5 ,6}, {6 ,6} };
	GRAPH test_graph(7);
	add_directed_edge(test_graph, nodes_edge);
	print_adjaceny_matrix(test_graph);
	reachability(test_graph);
	// hw1 p1
	vector<int> pid = {5, 2, 0, 1, 6, 3, 4};
	vector<int> ppid = {-1, 5, 5, 5, 2, 2, 1};
	vector<int> hw1p1 = killProcess(pid, ppid, 5);
	print(hw1p1);
	// hw1 p2 submited on leetcode!
	// hw1 p3
	vector<vector<int>> hw1p3 = {{0,1},{1,2},{3,4}};
	cout<<countComponents(5,hw1p3)<<endl;
	hw1p3 = {{0,1},{1,2},{3,4},{2,3}};
	cout<<countComponents(5,hw1p3)<<endl;
    return 0;
}


