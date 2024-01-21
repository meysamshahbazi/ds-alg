#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <stack>

#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <bits/stdc++.h> 
#include <unordered_map>

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
		while (sz--) {
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
// hw1 p1
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
// hw1 p2
// https://leetcode.com/problems/graph-valid-tree/   [premium]
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
// hw1 p3
// https://leetcode.com/problems/shortest-path-to-get-food/ [premium]
int getFood(vector<vector<char>> &matrix)
{
	int m = matrix.size();
	int n = matrix[0].size();
	pair<int,int> loc;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (matrix[i][j] == '*') {
				loc = make_pair(i,j);
				break;
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
// hw2 p1
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

bool isInRange(int num)
{
	return num <= 1000 && num >= 0;
}

// hw2 p2
// https://leetcode.com/problems/minimum-operations-to-convert-number/
int minimumOperations(vector<int>& nums, int start, int goal)
{
	queue<int> q;
	
	q.push(start);
	vector<int> len(1001, INT32_MAX);
	int res;
	for (int level = 0, sz = 1; !q.empty(); ++level, sz = q.size() ) {
		while (sz--){
			int start_ = q.front();
			q.pop();
			for (int num : nums) {
				res = start_ + num;
				if (res == goal)
					return level + 1;
				if (isInRange(res) && len[res] == INT32_MAX) {
					len[res] = level + 1;
					q.push(res);
				}

				res = start_ - num;
				if (res == goal)
					return level + 1;
				if (isInRange(res) && len[res] == INT32_MAX) {
					len[res] = level + 1;
					q.push(res);
				}
				

				res = start_ ^ num;
				if (res == goal)
					return level + 1;
				if (isInRange(res) && len[res] == INT32_MAX) {
					len[res] = level + 1;
					q.push(res);
				}
			}
		}		
	}
	return -1;
}

char getNextDigit(char c)
{
	if (c == '9')
		return '0';

	return c + 1;	
}

char getPervDigit(char c)
{
	if (c == '0')
		return '9';

	return c - 1;	
}


vector<string> lockAdj(string str)
{
	vector<string> res;
	for(int i = 0; i < 4; i++) {
		string adj = str;
		adj[i] = getNextDigit(str[i]);
		res.push_back(adj);
		adj[i] = getPervDigit(str[i]);
		res.push_back(adj);
	}
	return res;
}

// hw2 p3
// https://leetcode.com/problems/open-the-lock/
int openLock(vector<string>& deadends, string target)
{
	queue<string> q;
	q.push("0000");
	vector<bool> visited(10000); // convert deadends to visited!

	for (string &str : deadends) {
		visited[stoi(str)] = true;
		if (str == "0000")
			return -1;
	}
	if ( target == "0000")
		return 0;

	for (int level = 0, sz = 1; !q.empty(); ++level, sz = q.size()){
		while (sz--){
			string cur = q.front();
			q.pop();
			vector<string> adjList = lockAdj(cur);
			for (string &str : adjList) {
				if (!visited[stoi(str)]) {
					q.push(str);
					visited[stoi(str)] = true;
				}
				if (str == target)
					return level + 1;
			}
		}
	}

	return -1;
}

// hw3 p1
#define INF INT32_MAX
// https://leetcode.com/problems/walls-and-gates/ premium
void wallsAndGates(vector<vector<int>>& rooms)
{
	int m = rooms.size();
	if (m == 0)
		return;
	int n = rooms[0].size();

	int dr[4] {0, -1, +1, 0};
	int dc[4] {-1, 0, 0, +1};

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (rooms[i][j] == 0) {
				queue<pair<int,int>> q;
				q.push({i, j});
				for (int level = 0, sz = 1; !q.empty(); level++, sz = q.size()){
					while (sz--) {
						auto cur = q.front();
						q.pop();
						for (int d = 0; d < 4; d++) {
							int nr = dr[d] + cur.first;
							int nc = dc[d] + cur.second; 
							if (isValid(nr, nc, m, n) && rooms[nr][nc] != -1  && rooms[nr][nc] > (level + 1)) {
								rooms[nr][nc] = level + 1;
								q.push({nr,nc});
							} 
						}
					}
				}
			}
		}
	}
}

void bfs(vector<vector<int>>& heights, vector<vector<bool>> &visited, int r, int c, int R, int C)
{
	queue<pair<int, int>> q;
	q.push({r, c});
	visited[r][c] = true;
	int dr[4] {0, -1, +1, 0};
	int dc[4] {-1, 0, 0, +1};

	for (int level = 0, sz = 1; !q.empty(); level++, sz = q.size()) {
		while (sz--){
			int cur_r = q.front().first;
			int cur_c = q.front().second;
			q.pop();
			
			for (int d = 0; d < 4; d++) {
				int nr = cur_r + dr[d];
				int nc = cur_c + dc[d];
				if (isValid(nr, nc, R, C) && !visited[nr][nc] && heights[nr][nc] >= heights[cur_r][cur_c]) {
					visited[nr][nc] = true;
					q.push({nr,nc});
				}
			}
		}
		
	}
	
}
// hw3 p2
// https://leetcode.com/problems/pacific-atlantic-water-flow/
vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) 
{
	vector<vector<int>> result;
	int R = heights.size();
	if (R == 0)
		return result;
	int C = heights[0].size();

	vector<vector<bool>> tl(R, vector<bool>(C));
	vector<vector<bool>> br(R, vector<bool>(C));
	
	int r,c;
	r = 0;
	for (c = 0; c < C; c++) {
		bfs(heights, tl, r, c, R, C);
	}
	c = 0;
	for (r = 0; r < R; r++) {
		bfs(heights, tl, r, c, R, C);
	}

	r = R - 1;
	for (c = 0; c < C; c++) {
		bfs(heights, br, r, c, R, C);
	}

	c = C - 1;
	for (r = 0; r < R; r++)
		bfs(heights, br, r, c, R, C);

	for (int r = 0; r < R; r++)
		for (int c = 0; c < C; c++)
			if (tl[r][c] && br[r][c])
				result.push_back({r,c});

	return result;

}

int nextDigit(int d)
{
	if (d == 9)
		return 0;
	return d + 1;
}

int prevDigit(int d)
{
	if (d == 0)
		return 9;
	return d - 1;
}

// hw3 p3
// https://leetcode.com/problems/stepping-numbers/ premium
vector<int> countSteppingNumbers(long long low, long long high)
{
	vector<int> result;

	queue<int> q;
	for (int i = 0; i < 10; i++){
		q.push(i);
		if (i >= low && i <= high)
			result.push_back(i);
	}

	for (int level = 0, sz = 10; !q.empty(); level++, sz = q.size()) {
		while (sz--) {
			int cur = q.front();
			q.pop();

			if (cur == 0)
				continue;

			int prev = cur * 10 + prevDigit(cur % 10);
			q.push(prev);
			if (prev > high)
				return result;

			result.push_back(prev);

			int next = cur * 10 + nextDigit(cur % 10);
			q.push(next);

			if (next > high)
				return result;

			result.push_back(next);
		}
	}

	return result;
}

// hw 4 p1
// https://leetcode.com/problems/shortest-path-with-alternating-colors/
class Solution1129 {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
		vector<pair<vector<int>,vector<int>>> graph(n); // first for red, second for blue

		for (auto &item : redEdges ) {
			int from = item[0];
			int to = item[1];
			graph[from].first.push_back(to);
		}
		
		for (auto &item : blueEdges ) {
			int from = item[0];
			int to = item[1];
			graph[from].second.push_back(to);
		}

		queue<pair<int, int> > qred; // last edge is red!
		queue<pair<int, int> > qblue; // last edge is blue!

		vector<int> len_red(n, INT32_MAX);
		vector<int> len_blue(n, INT32_MAX);

		qred.push({0, 0});
		qblue.push({0, 0});

		len_red[0] = 0;
		len_blue[0] = 0;

		while (!qred.empty() || !qblue.empty() ) {
			if (!qred.empty()) {
				auto p = qred.front();
				qred.pop();
				int cur = p.first, level = p.second;

				for (int neighbour : graph[cur].second) { // we need blue edge!
					if (len_blue[neighbour] == INT32_MAX) {
						qblue.push({neighbour, level + 1});
						len_blue[neighbour] = level + 1;
					}
				}
			}

			if (!qblue.empty()) {
				auto p = qblue.front();
				qblue.pop();
				int cur = p.first, level = p.second;

				for (int neighbour : graph[cur].first) { // we need red edge!
					if (len_red[neighbour] == INT32_MAX) {
						qred.push({neighbour, level + 1});
						len_red[neighbour] = level + 1;
					}
				}
			}
		}

		vector<int> ans(n);

		for (int i = 0; i < n; i++) {
			ans[i] = min(len_blue[i], len_red[i]);
			if (ans[i] == INT32_MAX)
				ans[i] = -1;
		}

		return ans;
    }
};

// hw4 p2
// https://leetcode.com/problems/water-and-jug-problem/ TLE
class Solution365 {
	// Hash function 
	struct hashFunction { 
  		size_t operator()(const vector<int>  &myVector) const { 
			std::hash<int> hasher; 
			size_t answer = 0; 
		
			for (int i : myVector) { 
				answer ^= hasher(i) + 0x9e3779b9 +  
					(answer << 6) + (answer >> 2); 
			} 
			return answer; 
  		} 
	}; 
public:
    bool canMeasureWater(int jug1Capacity, int jug2Capacity, int targetCapacity) {
		unordered_set< vector<int>, hashFunction> visited;
        queue<pair<int, int> > q; // water contained in {jug 1, jug 2}
		q.push({0, 0});
		visited.insert({0, 0});
		int tc = targetCapacity;
		while (!q.empty()){
			pair<int, int> p = q.front();
			int volume1 = p.first, volume2 = p.second;
			q.pop();

			if (volume1 == tc || volume2 == tc || volume1 + volume2 == tc)
				return true;
			
			int remainCap1 = jug1Capacity - volume1;
			int remainCap2 = jug2Capacity - volume2;
			// jug 1 to jug 2
			if (remainCap2 >= volume1 && !visited.count({0, volume1 + volume2})) {
				q.push({0, volume1 + volume2});
				visited.insert({0, volume1 + volume2});
			}
			// jug 2 to jug 1
			if (remainCap1 >= volume2 && !visited.count({volume1 + volume2, 0}) ) {
				q.push({volume1 + volume2, 0});
				visited.insert({volume1 + volume2, 0});
			}
			if (remainCap2 < volume1 && !visited.count({volume1 - remainCap2, jug2Capacity}) ) {
				q.push({volume1 - remainCap2, jug2Capacity});
				visited.insert({volume1 - remainCap2, jug2Capacity});
			}
			if (remainCap1 < volume2 && !visited.count({jug1Capacity,  volume2 - remainCap1}) ) {
				q.push({jug1Capacity,  volume2 - remainCap1});
				visited.insert({jug1Capacity,  volume2 - remainCap1});
			}
			// make jug 1 empty 
			if (!visited.count({0,  volume2}) ) {
				q.push({jug1Capacity,  volume2});
				visited.insert({jug1Capacity,  volume2});
			}
			// make jug 2 empty
			if (!visited.count({volume1,  0}) ) {
				q.push({volume1,  0});
				visited.insert({volume1,  0});
			}
			// make jug 1 full
			if (!visited.count({volume1, jug2Capacity})) {
				q.push({volume1, jug2Capacity});
				visited.insert({volume1, jug2Capacity});
			}
			// make jug 2 full
			if (!visited.count({jug1Capacity, volume2})) {
				q.push({jug1Capacity, volume2});
				visited.insert({jug1Capacity, volume2});
			}
		}
		return false;
    }
};

// hw4 p3
// https://leetcode.com/problems/sliding-puzzle/
class Solution773 {
	typedef vector<vector<int>> Board;
	const Board correct {{1,2,3},{4,5,0}};
	bool isSolved(vector<vector<int>>& board) {
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 3; j++)
				if (board[i][j] != correct[i][j])
					return false;
		
		return true;
	}
	struct hashFunction { 
  		size_t operator()(const Board  &board) const { 
			std::hash<int> hasher; 
			size_t answer = 0; 
		
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 3; j++) { // try simpler one! 
				answer ^= hasher(board[i][j]) + 0x9e3779b9 +  
					(answer << 6) + (answer >> 2); 
			} 
			return answer; 
  		} 
	}; 
	vector<pair<int,int>> getNeighbIdx(pair<int,int> cur) {
		if (cur == make_pair(0,0))
			return {{0,1}, {1,0}};
		
		if (cur == make_pair(0,1))
			return {{0,0}, {1,1}, {0,2}};

		if (cur == make_pair(0,2))
			return {{0,1}, {1,2}};


		if (cur == make_pair(1,0))
			return {{0,0}, {1,1}};
		
		if (cur == make_pair(1,1))
			return {{1,0}, {0,1}, {1,2}};

		if (cur == make_pair(1,2))
			return {{1,1}, {0,2}};

		return {};
	}

	pair<int, int> getZeroIdx(Board &board) {
		if (0 ==  board[0][0])
			return {0,0};
		
		if (0 ==  board[0][1])
			return {0,1};

		if (0 ==  board[0][2])
			return {0,2};


		if (0 ==  board[1][0])
			return {1,0};
		
		if (0 ==  board[1][1])
			return {1,1};

		if (0 ==  board[1][2])
			return {1,2};

		return {-1,-1};
	}

public:

    int slidingPuzzle(vector<vector<int>>& board) {
		if (isSolved(board))
			return 0;

		unordered_map<Board, int, hashFunction> visited;

		queue<Board> q;
		q.push(board);
		visited[board] = 0;

		for (int level = 0, sz = 1; !q.empty(); ++level, sz = q.size()) {
			while (sz--) {
				Board cur = q.front();
				q.pop();

				auto zero_pos = getZeroIdx(cur);

				auto adjlist = getNeighbIdx(zero_pos);
				for (auto adj : adjlist) {
					Board neigh(cur);
					swap(neigh[zero_pos.first][zero_pos.second],neigh[adj.first][adj.second]);
					if (!visited.count(neigh)) {
						q.push(neigh);
						visited[neigh] = level + 1;

						if (isSolved(neigh))
							return level + 1;
					}
				}
			}
		}

		return -1;
    }
};

// hw4 p4
// https://leetcode.com/problems/maximum-candies-you-can-get-from-boxes/
class Solution1298 {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        
    }
};

// hw5 p1
// https://leetcode.com/problems/shortest-bridge/
class Solution934 {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        
    }
};

// hw5 p2
// https://www.spoj.com/problems/PT07Z/




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
	cout << "hw1 p2 \n";
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
	// hw2 p2
	cout<<"-------------------------"<<endl;
	vector<int> hw2p2 = {2,4,12};
	cout<<minimumOperations(hw2p2, 2, 12)<< endl;
	hw2p2 = {3,5,7};
	cout<<minimumOperations(hw2p2, 0, -4)<< endl;
	hw2p2 = {2,8,16};
	cout<<minimumOperations(hw2p2, 0, 1)<< endl;
	// hw2 p 3
	vector<string> hw2p3 = {"0201","0101","0102","1212","2002"};
	cout<<openLock(hw2p3, "0202")<<endl;
	// hw3 p1
	vector<vector<int>> hw3p1 = {{INF, -1,0, INF}, 
								{INF, INF, INF, -1},
								{INF,-1, INF,-1},
								{0, -1, INF, INF}};
	wallsAndGates(hw3p1);
	print(hw3p1);
	cout<< endl;
	// hw3 p2: 
	vector<vector<int>> hw3p2 = {{1,2,2,3,5},{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5},{5,1,1,2,4}};
	print(hw3p2);
	cout<< endl;
	auto hw3p22 = pacificAtlantic(hw3p2);
	print(hw3p22);
	// hw3 p3 
	auto hw3p3 = countSteppingNumbers(0, 21);
	print(hw3p3);

	// hw 4 p1 is submited!
	// hw4 p2

	Solution365 s365;
	freopen("02_LeetCode_365_Jug-input.txt", "rt", stdin);
	int cases;
	cin >> cases;
	cases = 100;
	vector<int> res365;
	while (cases--) {
		int j1, j2, tc;
		cin >> j1 >> j2 >> tc; 
		res365.push_back(s365.canMeasureWater(j1, j2, tc));
		// cout << s365.canMeasureWater(3,5,4) << endl;
		// cout << s365.canMeasureWater(2,6,5) << endl;

	}
	freopen("02_LeetCode_365_Jug-output.txt", "rt", stdin);
	cout << res365.size() << endl;
	for (auto  r : res365) {
		int a;
		cin >> a;
		cout << a << ", " << r << endl;
		if (a != r)
			cout << "test failed \n";
	}


    return 0;
}


