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
	
	for (int i = 0; i < 4; i++){
		if (isValidPixel(r + dr[i], c + dc[i], R, C)) {	
			if (!visited[r + dr[i]][c + dc[i]] && grid2[r + dr[i]][c + dc[i]] == 1  /* && grid1[r + dr[i]][c + dc[i]] == 1 */ )
				dfs(grid1, grid2, r + dr[i], c + dc[i], R, C, visited, grid1_eq);
		}
	}
}

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
    return 0;
}


