#include <iostream>
#include <vector>
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

template<class T>
void print(vector<vector<T>> &vec){
	for(auto &v : vec)
		print(v);
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
// hw1 p1
// https://leetcode.com/problems/kill-process/ [premium]
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

// hw1 p2
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

// hw1 p3
// https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/ [premium]
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

bool isValidPixel(int r, int c, int R, int C){
	if (r < 0 || c < 0 || r >= R || c >= C)
		return false;

	return true;
}

vector<vector<int>> get_neighbour(int r, int c, int R, int C) {
	vector<vector<int>> neighbour;

	if (isValidPixel(r - 1, c , R, C))
		neighbour.push_back({r - 1, c});
	
	if (isValidPixel(r + 1, c, R, C))
		neighbour.push_back({r + 1, c});

	if (isValidPixel(r, c - 1, R, C))
		neighbour.push_back({r, c - 1});

	if (isValidPixel(r, c + 1, R, C))
		neighbour.push_back({r, c + 1});

	return neighbour;
}

void dfs(vector<vector<int>>& image, int sr, int sc, int R, int C, int prev_color, int color)
{
	image[sr][sc] = color;
	
	vector<vector<int>> neighbours = get_neighbour(sr, sc, R, C);

	for (auto &neighbour : neighbours) {
		int r = neighbour[0];
		int c = neighbour[1];
		if (image[r][c] != prev_color) {
			dfs(image, r, c, R, C, prev_color, color);
		}
	}
}

// https://leetcode.com/problems/flood-fill/
vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
	int prev_color = image[sr][sc];
	
	int R = image.size();
	if (R == 0) return image;
	int C = image[0].size();
	if (prev_color == color)
		return image;
	dfs(image, sr, sc, R, C, prev_color, color);
	return image;
}

void dfs(vector<vector<int>> &grid1, vector<vector<int>> &grid2, int r, int c, int R, int C, vector<vector<bool>> &visited, vector<int> &grid1_eq)
{
	int dr[] = {0, -1, +1 , 0};
	int dc[] = {-1, 0, 0 , +1};
	visited[r][c] = true;
	grid1_eq.push_back(grid1[r][c]);
	bool res = true;
	
	for (int i = 0; i < 4; i++) {
		if (isValidPixel(r + dr[i], c + dc[i], R, C)) {	
			if (!visited[r + dr[i]][c + dc[i]] && grid2[r + dr[i]][c + dc[i]] == 1  /* && grid1[r + dr[i]][c + dc[i]] == 1 */ )
				dfs(grid1, grid2, r + dr[i], c + dc[i], R, C, visited, grid1_eq);
		}
	}
}
// hw2 p1
// https://leetcode.com/problems/count-sub-islands/
int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
	int R = (int) grid1.size();

	if (R == 0)
		return 0;

	int C = grid1[0].size();

	int sub_islands = 0;
	vector<vector<bool>> visited(R, vector<bool>(C));

	for (int r = 0; r < R; r++)
		for (int c = 0; c < C; c++) {
			if (!visited[r][c] && grid2[r][c] == 1) {
				vector<int> grid1_eq;
				dfs(grid1, grid2, r, c, R, C, visited, grid1_eq);
				bool grid1_have_zero = false;
				for(auto g:grid1_eq)
					if(g == 0) {
						grid1_have_zero = true;
						break;
					}
					if(!grid1_have_zero)
						sub_islands++;
			}
		}

	return sub_islands;
}

void dfs1(vector<vector<int>> &grid, int r, int c, int R, int C, int old_color, int color, vector<vector<bool>> &visited) 
{	
	int dr[] = {0, -1, +1 , 0};
	int dc[] = {-1, 0, 0 , +1};

	if (!isValidPixel(r, c, R, C))
		return;
	
	if (visited[r][c])
		return;

	if (grid[r][c] != old_color && grid[r][c] != color)
		return;

	bool isBorder = false;
	
	for (int i = 0; i < 4; i++) {
		if (isValidPixel(r + dr[i], c + dc[i], R, C) ) {
			if (r == 0 || c == 0 || r == R - 1 || c == C - 1) {
				isBorder = true;
				break;
			}

			if (visited[r + dr[i]][c + dc[i]]) {
				if (grid[r + dr[i]][c + dc[i]] != color) {
					isBorder = true;
					break;
				}
			}
			else { // Not visited!
				if (grid[r + dr[i]][c + dc[i]] != old_color) {
					isBorder = true;
					break;
				}
			} 
		}
	}
	
	if (isBorder) {
		grid[r][c] = color;
	}

	visited[r][c] = true;

	for (int i = 0; i < 4; i++) {
		dfs1(grid, r + dr[i], c + dc[i], R, C, old_color, color, visited);
	}
}
// hw2 p2
// https://leetcode.com/problems/coloring-a-border/
vector<vector<int>> colorBorder1(vector<vector<int>>& grid, int row, int col, int color) {
	// TODO solve it correctly!
	int R = (int) grid.size();

	if (R == 0)
		return grid;

	int C = grid[0].size();
	vector<vector<bool>> visited(R, vector<bool>(C));
	
	dfs1(grid, row, col, R, C, grid[row][col], color, visited);
	return grid;
}

void dfs(const vector<vector<int>> &grid, int old_color, int r, int c, int R, int C, vector<vector<bool>> &visited)
{
	if (!isValidPixel(r, c, R, C))
		return;

	if (visited[r][c])
		return;

	if (grid[r][c] != old_color)
		return;

	int dr[4] {0, -1, +1, 0};
	int dc[4] {-1, 0, 0, +1};
	
	visited[r][c] = true;

	for (int i = 0; i < 4; i++)
		dfs(grid, old_color, r + dr[i], c + dc[i], R, C, visited);
}

bool isBorder(const vector<vector<int>>& grid, int r, int c, int R, int C, const vector<vector<bool>> &visited)
{
	int dr[4] {0, -1, +1, 0};
	int dc[4] {-1, 0, 0, +1};

	if (r == 0 || c == 0 || r == R - 1 || c == C - 1) 
		return true;
	
	for (int i = 0; i < 4; i++) {
		if (!visited[r + dr[i]][c + dc[i]])
			return true;
	}

	return false;
}

// https://leetcode.com/problems/coloring-a-border/
vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color)
{
	int R = (int) grid.size();
	if (R == 0)
		return grid;
	int C = grid[0].size();

	vector<vector<bool>> visited(R, vector<bool>(C));

	// first update the visited matrix!
	dfs(grid, grid[row][col], row, col, R, C, visited);

	for (int r  = 0; r < R; r++) {
		for (int c  = 0; c < C; c++) {
			if (visited[r][c] && isBorder(grid, r, c, R, C, visited))
				grid[r][c] = color;
		}
	}
	return grid;
}

void dfs(vector<vector<int>> &grid, int r, int c, int R, int C, vector<vector<bool>> &visited, vector<pair<int,int>> &islands)
{
	if (!isValidPixel(r, c, R, C) || visited[r][c] || grid[r][c] == 1 )
		return;

	islands.push_back(make_pair(r,c));
	visited[r][c] = true;

	int dr[4] {0, -1, +1, 0};
	int dc[4] {-1, 0, 0, +1};

	for (int i = 0; i < 4; i++)
		dfs(grid,r + dr[i],c + dc[i], R, C, visited, islands);
	
}
// hw1 p3
// https://leetcode.com/problems/number-of-closed-islands/
int closedIsland(vector<vector<int>> &grid)
{
	int R = (int) grid.size();
	if (R == 0)
		return 0;

	int C = grid[0].size();

	int count = 0;
	vector<vector<bool>> visited(R, vector<bool>(C));
	for (int r = 0; r < R; r++)
		for (int c = 0; c < C; c++) {
			if (!visited[r][c] && grid[r][c] == 0){
				vector<pair<int,int>> islands;
				dfs(grid,r,c,R,C,visited,islands);
				bool isclosed = true;
				for(auto &p:islands)
					if(p.first == 0 || p.second ==0 || p.first == R-1 || p.second == C - 1){
						isclosed = false;
						break;
					}
				
				if (isclosed)
					count++;
			}
		}


	return count;
}

// hw2 p4
// https://leetcode.com/problems/detect-cycles-in-2d-grid/
class Solution1559 {
	int dr[4] { -1, 0, 1, 0 };
	int dc[4] { 0, 1, 0, -1 };
public:
	bool isValid(int r, int c, int R, int C) {
		if (r < 0 || c < 0 || r >= R || c >= C)
			return false;
		return true;
	}
	bool dfs(vector<vector<char>>& grid,int r, int c, char val, vector<vector<bool>> &visited, int  r0 = -1, int c0 = -1) {

		
		visited[r][c] = true;

		for (int d = 0; d < 4; d++) {
			if (isValid(r + dr[d] ,c + dc[d] ,grid.size(), grid[0].size()) && grid[r + dr[d]][c + dc[d]] == val) {
				if (!visited[r + dr[d]][c + dc[d]]) {
					bool res = dfs(grid, r + dr[d], c + dc[d], val, visited, r, c);
					if (res)
						return true;
				}
				else { // this neighbor has already been visited
					if (r0 != r + dr[d] && c0 != c + dc[d]){
						return true;
					}
				}
			} 
		}
		return false;
	}
    bool containsCycle(vector<vector<char>>& grid) {
        int R = grid.size();
		
		if (R == 0)
			return false;

		int C = grid[0].size();

		vector<vector<bool>> visited(R, vector<bool>(C));

		for (int r = 0; r < R; r++){
			for (int c = 0; c < C; c++) {
				if (!visited[r][c]) {
					bool res = dfs(grid, r, c, grid[r][c], visited);
					if (res)
						return true;
				}
			}
		}
		return false;
    }
};

// https://leetcode.com/problems/restore-the-array-from-adjacent-pairs/
class Solution1743 {
public:
	void dfs(GRAPHMP &graph, unordered_set<int> &visited, int node, vector<int> &arr) {
		visited.insert(node);
		arr.push_back(node);
		for (auto adj : graph[node]) {
			if (!visited.count(adj))
				dfs(graph, visited, adj, arr);
		}
	}
    vector<int> restoreArray(vector<vector<int>>& adjacentPairs) {
        GRAPHMP graph;

		for (auto p : adjacentPairs) {
			graph[p[0]].push_back(p[1]);
			graph[p[1]].push_back(p[0]);
		}

		int start_node;
		for (auto it : graph) {
			if (it.second.size() == 1){
				start_node = it.first;
				break;
			}
		}
		cout << endl;
		unordered_set<int> visited;
		vector<int> arr;
		dfs(graph, visited, start_node, arr);

		return arr;
    }
};

// https://leetcode.com/problems/smallest-string-with-swaps/ TLE!
class Solution1202 {
	GRAPH graph;
	vector<vector<int>> reachability;

	void dfs(int node, vector<bool> &visited, vector<int> &reachable) {
		visited[node] = true;
		for (int adj : graph[node]) {
			if (!visited[adj]) {
				reachable.push_back(adj);
				dfs(adj, visited, reachable);
			}
		}
	}

	void getReachability() {
		
		for (int i = 0; i <(int) graph.size(); i++) {
			vector<bool> visited(graph.size());
			vector<int> vec;
			dfs(i, visited, vec);
			reachability[i] = vec;
		}
	}
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
		graph = vector<vector<int>>(s.size(), vector<int>());
		reachability = vector<vector<int>>(s.size(), vector<int>());

		for (auto p : pairs) {
			graph[p[0]].push_back(p[1]);
			graph[p[1]].push_back(p[0]);
		}

		getReachability();
		
		for (int i = 0; i < (int) graph.size(); i++) {
			for (auto r : reachability[i]) {
				if (r < i && s[i] < s[r])
					swap(s[r], s[i]);
				if (r > i && s[r] < s[i])
					swap(s[r], s[i]);
			}
		}
		
		return s;
    }
};

// https://leetcode.com/problems/longest-consecutive-sequence/
class Solution128 {
public:
	void dfs(GRAPHMP &graph, int node, unordered_set<int> &visited, int &len) {
		visited.insert(node);
		len++;
		for (int adj : graph[node]) {
			if (!visited.count(adj))
				dfs(graph, adj, visited, len);
		}
	}
    int longestConsecutive(vector<int>& nums) {
		GRAPHMP graph;
		for (auto n : nums) {
			graph[n] = {};
		}

		for (auto n : nums) {
			if (graph.count(n - 1)) {
				graph[n - 1].push_back(n);
			}
			if (graph.count(n + 1)) {
				graph[n + 1].push_back(n);
			}
		}
		unordered_set<int> visited;
		int longest = 0;
		for (auto n : nums) {
			if (!visited.count(n)) {
				int len = 0; 
				dfs(graph, n, visited, len);
				if (len > longest)
					longest = len;
			}
		}
		return longest;
    }
};

// hw4 p1
// https://leetcode.com/problems/is-graph-bipartite/
class Solution785 {
public:
	bool dfs(vector<vector<int>>& graph, int node, vector<bool> &visited, vector<bool> &group, bool isSetA) {
		visited[node] = true;
		group[node] = isSetA;
		for (int adj : graph[node]) {
			if (!visited[adj]) {
					if (!dfs(graph, adj, visited, group,!isSetA) )
						return false;
			}
			else {
				if (group[adj] == isSetA)
					return false;
			}
		}
		return true;
	}
    bool isBipartite(vector<vector<int>>& graph) {
        vector<bool> visited(graph.size());
		vector<bool> group(graph.size());

		for (int i = 0; i < (int) graph.size(); i++) {
			if (!visited[i]) {
				if (!dfs(graph, i, visited, group, true))			
					return false;
			}
		}
		return true;
    }
};

// hw4 p2
// https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/
class Solution1466 {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        
    }
};

// hw4 p3
// https://leetcode.com/problems/path-with-minimum-effort/
class Solution1631 {
	int dr[4] {0, -1, +1 , 0};
	int dc[4] {-1, 0, 0 , +1};


	bool isValid(int r, int c, vector<vector<int>> &heights){
		if (r < 0 || c < 0 || r >= heights.size() || c >= heights[0].size())
			return false;

		return true;
	}
	// int dfs(vector<vector<int>> &heights, int r, int c, vector<vector<bool>> &visited) {
	// 	visited[r][c] = true;
		
	// 	if (r == (int) heights.size() - 1 && c == (int) heights[0].size() - 1)
	// 		return 0;
		
	// 	int minEffort = (int) 1e6;
	// 	for (int d = 0; d < 4; d++) {
	// 		int nr = r + dr[d], nc = c + dc[d];
	// 		if (isValid(nr, nc, heights) && !visited[nr][nc]) {
	// 			int effort = dfs(heights, nr, nc, visited);

	// 			effort = max(abs(heights[r][c] - heights[nr][nc]), effort);

	// 			cout << r << ", " << c << " : "<< effort << endl;
	// 			minEffort = min(effort, minEffort);
	// 		}	
	// 	}
	// 	return minEffort;
	// }
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
		// vector<vector<bool>> visited(heights.size(), vector<bool>(heights[0].size()));
		// return dfs(heights, 0, 0, visited);
    }
};

// https://leetcode.com/problems/graph-valid-tree/ [premium]



// https://leetcode.com/problems/redundant-connection/
class Solution684 {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        
    }
};

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
	// hw2 p 1 
	vector<vector<int>> grid1 = {{1,1,1,0,0},{0,1,1,1,1},{0,0,0,0,0},{1,0,0,0,0},{1,1,0,1,1}}; 
	vector<vector<int>> grid2 = {{1,1,1,0,0},{0,0,1,1,1},{0,1,0,0,0},{1,0,1,1,0},{0,1,0,1,0}};
	grid1 = {{1,0,1,0,1},{1,1,1,1,1},{0,0,0,0,0},{1,1,1,1,1},{1,0,1,0,1}};
	grid2 = {{0,0,0,0,0},{1,1,1,1,1},{0,1,0,1,0},{0,1,0,1,0},{1,0,0,0,1}};
	print(grid1);
	cout<<"\n";
	print(grid2);
	cout << countSubIslands(grid1, grid2)<<endl;
	// hw2 p2
	vector<vector<int>> grid = {{1,1},{1,2}};
	int row = 0, col = 0, color = 3;
	grid = {{1,1,1},{1,1,1},{1,1,1}};
	row = 1, col = 1, color = 2;

	grid = {{2,1,3,2,1,1,2},{1,2,3,1,2,1,2},{1,2,1,2,2,2,2},{2,1,2,2,2,2,2},{2,3,3,3,2,1,2}};
	row = 4, col = 4, color = 3;
	print(grid);
	cout<<endl;
	grid = colorBorder(grid,row, col, color);
	print(grid);
	grid = {{2,1,3,2,1,1,3},{1,2,3,1,3,1,3},{1,2,1,3,2,3,3},{2,1,3,3,2,3,3},{2,3,3,3,3,1,3}};
	cout<<endl;
	print(grid);
	// hw 2 p3
	vector<vector<int>> hw2p3 = {{1,1,1,1,1,1,1},
								{1,0,0,0,0,0,1},
								{1,0,1,1,1,0,1},
								{1,0,1,0,1,0,1},
								{1,0,1,1,1,0,1},
								{1,0,0,0,0,0,1},
								{1,1,1,1,1,1,1}};
	print(hw2p3);
	cout << closedIsland(hw2p3) << endl;
	
	vector<vector<char>> hw2p4 = {	{'a','b','b'},
									{'b','z','b'},
									{'b','b','a'}};
	
	print(hw2p4);
	Solution1559 s1559;
	cout << s1559.containsCycle(hw2p4) << endl;

	// hw3 p1
	Solution1743 s1743;
	vector<vector<int>> hw3p1 = {{-3,-9},{-5,3},{2,-9},{6,-3},{6,1},{5,3},{8,5},{-5,1},{7,2}};
	auto v1743 = s1743.restoreArray(hw3p1);
	print(v1743);
	// hw3 p2
	Solution1202 s1202;
	string s = "dcab" ;
	vector<vector<int>> pairs = {{0,3},{1,2}} ;
	cout << s1202.smallestStringWithSwaps(s, pairs) << endl;

	// hw3 p3
	Solution128 s128;
	vector<int> hw3p3 = {100,4,200,1,3,2};
	cout << s128.longestConsecutive(hw3p3) << endl;

	vector<vector<int>> hw4p3 = {{1,2,2},{3,8,2},{5,3,5}};
	Solution1631 s1631;

	cout << s1631.minimumEffortPath(hw4p3) << endl;

    return 0;
}


