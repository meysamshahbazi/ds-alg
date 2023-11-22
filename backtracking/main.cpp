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

const int MAX = 100;
char grid[MAX][MAX];
int rows, cols;
int total_paths = 0;

void print(char grid[MAX][MAX])
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            cout << " " <<grid[i][j] << " ";
        cout<<endl;
    }
}

int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

bool valid(int r, int c) {
    if (r < 0 || r >= rows || c < 0 || c >= cols)
        return false;

    if (grid[r][c] != '.')
        return false;

    return true;
}

void cntWays(int r, int c) {
    if (r == rows - 1 && c == cols - 1) {
        total_paths += 1;
        return;
    }

    for (int dir = 0; dir < 4; dir++) {
        int nr = r + dr[dir];
        int nc = c + dc[dir];

        if (!valid(nr, nc))
            continue;
        
        grid[nr][nc] = 'z';
        cntWays(nr, nc);
        grid[nr][nc] = '.';
    }
}


int main()
{
    vector<string> data;
    data = {
        ".......",
        ".xxxxx.",
        "...x...",
        ".x....x",
        "..x.x.." };
    rows = data.size();
    cols = data[0].size();
    cout<< rows << ", "<< cols << endl;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			grid[i][j] = data[i][j];
		}
	}
    
    print(grid);
	// mark first cell to not revisit
	grid[0][0] = 'z';
    cntWays(0, 0);
	cout << total_paths << "\n";
    return 0;
}


