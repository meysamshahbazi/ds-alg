#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <stack>

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

void add_directed_edge(GRAPH &graph, int from, int to) {
	graph[from].push_back(to);
}

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

void print_path(GRAPH &graph)
{
	vector<int> len(graph.size(), OO);
	vector<int> parents(graph.size(), OO);
	queue<int> q;
	q.push(0);
	len[0] = 0;
	for (int level = 0, sz = 1; !q.empty(); ++level, sz = q.size() ) {
		while(sz--) {
			int cur = q.front();
			q.pop();
			for (int neighbour: graph[cur])
				if (len[neighbour] == OO){
					q.push(neighbour);
					len[neighbour] = level + 1;
					parents[neighbour] = cur;
				}
		}
	}

	for (int i = 1; i < graph.size(); i++) {
		cout << " Path from 0 to "<<i<<": ";
		if(parents[i] == OO) 
			cout<< "Not exist";
		else {
			stack<int> stk;
			stk.push(i);
			int parent = parents[i];

			while (parent != 0) {
				stk.push(parent);
				parent = parents[parent];
			} 

			stk.push(0);

			while (!stk.empty()) {
				cout<< stk.top()<<" ";
				stk.pop();
			}
		}
		cout<<"\n";
	}

}

// https://leetcode.com/problems/graph-valid-tree/   premium
bool validTree(int nodes, vector<vector<int>> &edges)
{
	GRAPH graph(nodes);
	add_directed_edge(graph, edges);
	vector<int> len(graph.size(), OO);
	queue<int> q;
	q.push(0);
	// len[0] = 0;
	for (int level = 0, sz = 1; !q.empty(); ++level, sz = q.size() ) {
		while(sz--) {
			int cur = q.front();
			q.pop();
			for (int neighbour: graph[cur]){
				if (len[neighbour] == OO){
					q.push(neighbour);
					len[neighbour] = level + 1;
				}
				else 
					return false;
			}
		}
	}
	return true;
}

bool isValid(int r, int c, int R, int C){
	if (r < 0 || c < 0 || r >= R || c >= C)
		return false;

	return true;
}

bool isValid(pair<int,int> &loc, int R, int C){
	int r = loc.first;
	int c = loc.second;
	return isValid(r, c, R, C);
}

// https://leetcode.com/problems/shortest-path-to-get-food/
int getFood(vector<vector<char>> &matrix)
{
	int m = matrix.size();
	int n = matrix[0].size();
	pair<int,int> loc;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (matrix[i][j] == '*') {
				loc = make_pair(i,j);
				break;;
			}
	

	int dr[4] {0, -1, +1, 0};
	int dc[4] {-1, 0, 0, +1};

	vector<vector<int>> len(m, vector<int>(n, OO));
	queue<pair<int,int>> q;
	q.push(loc);
	len[loc.first][loc.second] = 0;

	for (int level = 0, sz = 1; !q.empty(); ++level, sz = q.size() ) {
		while (sz--){
			auto cur = q.front();
			q.pop();

			for (int i = 0; i < 4; i++) {
				pair<int,int> neighbour = make_pair(cur.first + dr[i], cur.second + dc[i]);
				if (!isValid(neighbour, m, n) || matrix[neighbour.first][neighbour.second] == 'X')
					continue;
				if (len[neighbour.first][neighbour.second] == OO) { // havnt visited
					q.push(neighbour);
					len[neighbour.first][neighbour.second] = level + 1;
					if (matrix[neighbour.first][neighbour.second] == '#')
						return level + 1;
				}

			}
		}
	}

	return -1;

}

// https://leetcode.com/problems/jump-game-iii/
bool canReach(vector<int>& arr, int start) 
{
	int n = (int) arr.size();
	vector<int> len(n, INT32_MAX);

	queue<int> q;
	q.push(start);
	len[start] = 0;

	for (int level = 0, sz = 1; !q.empty(); ++level, sz = q.size() ) {
		while (sz--){
			int cur = q.front();
			q.pop();
			vector<int> adjlist;
			if (cur + arr[cur] < n)
				adjlist.push_back(cur + arr[cur]);
			if (cur - arr[cur] >= 0)
				adjlist.push_back(cur - arr[cur]);
			for (int neighbour : adjlist) 
				if (len[neighbour] == INT32_MAX) { 
					q.push(neighbour);
					len[neighbour] = level + 1;
					if (arr[neighbour] == 0)
						return true;
				}
		}
	}
	return false;
}

// https://leetcode.com/problems/minimum-operations-to-convert-number/
int minimumOperations(vector<int>& nums, int start, int goal)
{
	
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
	// hw1 p1
	GRAPH hw1p1(5);
	add_directed_edge(hw1p1, 0, 1);
	add_directed_edge(hw1p1, 1, 2);
	add_directed_edge(hw1p1, 2, 3);
	add_directed_edge(hw1p1, 4, 3);
	print_path(hw1p1);
	hw1p1 = GRAPH(9);
	add_directed_edge(hw1p1, 1, 3);
	add_directed_edge(hw1p1, 1, 5);
	add_directed_edge(hw1p1, 1, 6);
	add_directed_edge(hw1p1, 3, 5);
	add_directed_edge(hw1p1, 4, 3);
	add_directed_edge(hw1p1, 3, 7);
	add_directed_edge(hw1p1, 5, 4);
	add_directed_edge(hw1p1, 6, 0);
	add_directed_edge(hw1p1, 2, 4);
	add_directed_edge(hw1p1, 2, 8);
	add_directed_edge(hw1p1, 0, 2);
	add_directed_edge(hw1p1, 2, 8);
	add_directed_edge(hw1p1, 2, 2);
	print_path(hw1p1);
	// hw1 p2
	vector<vector<int>> hw1p2 = {{0,1},{0,2},{0,3},{1,4}};
	cout<<validTree(5, hw1p2)<<endl;
	hw1p2 = {{0,1},{1,2},{2,3},{1,3},{1,4}};
	cout<<validTree(5, hw1p2)<<endl;
	// hw1 p3
	vector<vector<char>> hw1p3 = { 	{'X','X','X','X','X','X'},
									{'X','*','0','0','0','X'},
									{'X','0','0','#','0','X'},
									{'X','X','X','X','X','X'}};
	cout<<getFood(hw1p3)<<endl;

	hw1p3 = { 	{'X','X','X','X','X','X'},
				{'X','*','0','X','0','X'},
				{'X','0','0','X','#','X'},
				{'X','X','X','X','X','X'}};
	cout<<getFood(hw1p3)<<endl;
	// hw2 p1
	vector<int> hw2p1 = {4,2,3,0,3,1,2};
	cout<<canReach(hw2p1, 5)<<endl;

    return 0;
}
