#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <bits/stdc++.h> 
#include <unordered_map>
#include <unordered_set>

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
int best_path_so_far = INT32_MAX;
int total_steps = 0;

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

void cntWaysExt(int r, int c) {
    if (r == rows -1 && c == cols - 1) {
        if (best_path_so_far > total_steps) {
            best_path_so_far = total_steps;
            total_paths = 1;
        }
        else if (best_path_so_far == total_steps)
            total_paths += 1;

        return;
    }

    for (int dir = 0; dir < 4; dir++) {
        int nr = r + dr[dir];
        int nc = c + dc[dir];

        if (!valid(nr, nc))
            continue;
        
        total_steps += 1;
        grid[nr][nc] = 'z';

        cntWaysExt(nr, nc);

        total_steps -= 1;
        grid[nr][nc] = '.';
    }
}

// https://leetcode.com/problems/partition-to-k-equal-sum-subsets/
class Solution698 {
    int sum{0};
    vector<vector<int>> partions;
    vector<int> sum_of_partions{0};
    int k;
    int partions_sum {0};
    vector<int> nums;
public:
    bool backtrack(int idx) {
        if (idx == nums.size() ) {
            for (auto p : sum_of_partions)
                if (p != partions_sum)
                    return false;
            
            return true;
        }
        for (int i = 0; i < k; i++) {
            if (sum_of_partions[i] + nums[idx] <= partions_sum) {
                sum_of_partions[i] += nums[idx];

                if ( backtrack(idx + 1) )
                    return true;

                sum_of_partions[i] -= nums[idx];
            }
        }
        return false;
    }
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0 || nums.size() < k)
            return false;
        
        partions_sum = sum / k;
        this->k = k;
        this->nums = nums;
        partions.resize(k);
        sum_of_partions = vector<int>(k);

        return backtrack(0);
    }
};

class Solution698_1 {
    vector<bool> visited;
    int partion_sum;
    int k;
    vector<int> m_nums;
public:
    bool backtrack(int partion_idx, int number_idx, int cur_sum) {
        if (partion_idx == k)
            return true;
        
        if (cur_sum == partion_sum)
            return backtrack(partion_idx + 1, 0, 0);

        if (number_idx == (int) m_nums.size())
            return false;
        
        if (!visited[number_idx] && cur_sum + m_nums[number_idx] <= partion_sum) {
            visited[number_idx] = true;

            if (backtrack(partion_idx, number_idx + 1, cur_sum + m_nums[number_idx])) // pick
                return true;
            
            visited[number_idx] = false;
        }

        if (backtrack(partion_idx, number_idx + 1, cur_sum)) // leave
            return true;

        return false;
    }
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0 || nums.size() < k)
            return false;

        this->k = k;
        m_nums = nums;
        partion_sum = sum / k;

        visited = vector<bool>(nums.size(), false);
        sort(m_nums.begin(),m_nums.end(),greater<int>());
        return backtrack(0, 0, 0);
    }
};

class Solution698_2 {
    vector<bool> visited;
    int partion_sum;
    int k;
    vector<int> m_nums;
public:
    bool backtrack(int partion_idx, int number_idx, int cur_sum) {
        if (partion_idx == k)
            return true;
        
        if (cur_sum == partion_sum)
            return backtrack(partion_idx + 1, 0, 0);

        if (number_idx == (int) m_nums.size())
            return false;
        
        for (int start = number_idx; start <(int) m_nums.size(); start++) {
            if (!visited[start] && cur_sum + m_nums[start] <= partion_sum ){
                visited[start] = true;

                if (backtrack(partion_idx, start + 1, cur_sum + m_nums[start]))
                    return true;
                
                visited[start] = false;
            }
        }

        return false;
    }
    bool try_partition(int parition_idx, int number_idx, int cur_sum) {	// O(k * 2^N)
        if (parition_idx == k)
            return true;

        if (cur_sum == partion_sum)
            return try_partition(parition_idx + 1, 0, 0);

        if (number_idx == (int) m_nums.size())
            return false;

        for(int start = number_idx; start < (int) m_nums.size(); start++) {
            if (!visited[start] && cur_sum + m_nums[start] <= partion_sum) {
                // partition_values[parition_idx].push_back(m_nums[start]);
                visited[start] = true;

                if (try_partition(parition_idx, start + 1, cur_sum + m_nums[start]))
                    return true;	// take it

                visited[start] = false;
                // partition_values[parition_idx].pop_back();
            }
        }

        return false;
    }
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0 || nums.size() < k)
            return false;

        this->k = k;
        m_nums = nums;
        partion_sum = sum / k;

        visited = vector<bool>(nums.size(), false);
        sort(m_nums.begin(),m_nums.end(),greater<int>());
        return backtrack(0, 0, 0);
    }
};

// https://leetcode.com/problems/all-paths-from-source-to-target/
class Solution797 {
    vector<vector<int>> m_graph;
    vector<vector<int>> all_paths;
    int n;
public:
    void backtrack(int node, vector<int> &cur_path) {
        if (node == n - 1) {
            all_paths.push_back(cur_path);
            return;
        }

        for (auto adj: m_graph[node]){
            cur_path.push_back(adj);
            backtrack(adj, cur_path);
            cur_path.pop_back();
        }
    }
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        m_graph = graph;
        n = (int) graph.size();
        all_paths.clear();
        vector<int> cur_path;
        cur_path.push_back(0);
        backtrack(0, cur_path);
        return all_paths;
    }
};



// https://leetcode.com/problems/n-queens/
class Solution51 {
    vector<vector<string>> all_sol;
    vector<vector<int>> chess;
    int n;
public:
    void IncAttack(int k, int l) {
        for (int i = 0; i < n; i++){
            chess[k][i]++;
            chess[i][l]++;

            if (k - i >= 0 && l - i >= 0) 
                chess[k - i][l - i]++;
            
            if (k + i < n && l + i < n) 
                chess[k + i][l + i]++;

            if (k + i < n && l - i >= 0) 
                chess[k + i][l - i]++;

            if (k - i >= 0 && l + i < n) 
                chess[k - i][l + i]++;
        }
    }

    void DecAttack(int k, int l) {
        for (int i = 0; i < n; i++){
            chess[k][i]--;
            chess[i][l]--;

            if (k - i >= 0 && l - i >= 0) 
                chess[k - i][l - i]--;
            
            if (k + i < n && l + i < n) 
                chess[k + i][l + i]--;

            if (k + i < n && l - i >= 0) 
                chess[k + i][l - i]--;

            if (k - i >= 0 && l + i < n) 
                chess[k - i][l + i]--;
        }
    }

    void backtrack(int q, vector<string> &cur_sol){
        if (q == n ) {
            auto it = find(all_sol.begin(), all_sol.end(), cur_sol);
            if (it == all_sol.end())
                all_sol.push_back(cur_sol);

            return;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (cur_sol[i][j] == '.' && chess[i][j] == 0) {
                    cur_sol[i][j] = 'Q';
                    IncAttack(i, j);

                    backtrack(q + 1, cur_sol);

                    DecAttack(i, j);
                    cur_sol[i][j] = '.';
                }
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        this->n = n;
        // each chess[i][j] number indicate that cell is attacket by how many queens!
        // so chess[i][j] = 0 means that no queens is currentlly attacks that cell
        chess = vector<vector<int>>(n, vector<int>(n, 0));
        all_sol.clear();
        vector<string> cur_sol(n, string(n, '.'));
        backtrack(0, cur_sol);
        return all_sol;
    }
};

// https://leetcode.com/problems/sudoku-solver/
class Solution37 {
    vector<vector<char>> board;
public:
    bool valid(char val, int k, int l) {
        for (int i = 0; i < 9; i++) {
            if (/* i != l && */ board[k][i] == val)
                return false;
        }

        for (int i = 0; i < 9; i++) {
            if (/* i != k && */ board[i][l] == val)
                return false;
        }

        int sub_r = k/3;
        int sub_c = l/3;

        for (int i = sub_r; i < sub_r + 3; i++)
            for (int j = sub_c; j < sub_c + 3; j++)
                if (/* i != k && j != l  && */ board[i][j] == val)
                    return false;

        return true;
    }

    bool backtrack() { 
        bool isFill = true;
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++) 
                if(board[i][j] == '.') 
                    isFill = false;

        if (isFill)
            return true;

        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') 
                    continue;

                for (char n = '1'; n <= '9'; n++) {
                    if (valid(n, i , j)) {
                        board[i][j] = n;
                        if (backtrack()) 
                            return true;
                        board[i][j] = '.';
                    }
                }
            }

        return false;
    }

    void solveSudoku(vector<vector<char>>& board) {
        this->board = board;
        backtrack();
        board = this->board;
    }
};

// https://leetcode.com/problems/permutations/
class Solution46 {
    vector<vector<int>> permutions;
    int n;
    vector<int> nums;
    vector<int> cur_per;
    vector<bool> picked;
public:
    void backtrack(int idx) {
        if (idx == n) {
            permutions.push_back(cur_per);
            return;
        }

        for (int i = 0; i < n; i++) {
            if (!picked[i]) {
                picked[i] = true;
                cur_per.push_back(nums[i]);
                backtrack(idx + 1);
                cur_per.pop_back();
                picked[i] = false;
            }
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        this->nums = nums;
        n = (int) nums.size();
        picked = vector<bool>(n, false);
        backtrack(0);
        return permutions;
    }
};
// for Tower of Hanoi
// https://www.hackerearth.com/practice/algorithms/dynamic-programming/introduction-to-dynamic-programming-1/practice-problems/algorithm/tower-of-hanoi-17/?purpose=login&source=problem-page&update=google

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
    cntWaysExt(0, 0);
	cout << total_paths << "\n";

    cout << "===============\n";
    Solution698 s689;
    vector<int> nums = {4,3,2,3,5,2,1};
    int k = 4;
    cout << s689.canPartitionKSubsets(nums, k) << endl;
    nums = {1,2,3,4};
    k = 3;
    cout << s689.canPartitionKSubsets(nums, k) << endl;
    nums = {960,3787,1951,5450,4813,752,1397,801,1990,1095,3643,8133,893,5306,8341,5246};
    k = 6;
    // cout << s689.canPartitionKSubsets(nums, k) << endl;

    cout << "===============\n";
    Solution698_1 s689_1;
    nums = {4,3,2,3,5,2,1};
    k = 4;
    cout << s689_1.canPartitionKSubsets(nums, k) << endl;
    nums = {1,2,3,4};
    k = 3;
    cout << s689_1.canPartitionKSubsets(nums, k) << endl;
    nums = {960,3787,1951,5450,4813,752,1397,801,1990,1095,3643,8133,893,5306,8341,5246};
    k = 6;
    cout << s689_1.canPartitionKSubsets(nums, k) << endl;

    cout << "===============\n";
    Solution698_2 s689_2;
    nums = {4,3,2,3,5,2,1};
    k = 4;
    cout << s689_2.canPartitionKSubsets(nums, k) << endl;
    nums = {1,2,3,4};
    k = 3;
    cout << s689_2.canPartitionKSubsets(nums, k) << endl;
    nums = {960,3787,1951,5450,4813,752,1397,801,1990,1095,3643,8133,893,5306,8341,5246};
    k = 6;
    cout << s689_2.canPartitionKSubsets(nums, k) << endl;
    // hw1 p1
    cout << "===============\n";
    vector<vector<int>> hw1p1;
    vector<vector<int>> hw1p1o;
    Solution797 s797;
    hw1p1 = {{4,3,1},{3,2,4},{3},{4},{}};
    hw1p1o = s797.allPathsSourceTarget(hw1p1);
    print(hw1p1o);
    cout << "===============\n";
    hw1p1 = {{1,2},{3},{3},{}};
    hw1p1o = s797.allPathsSourceTarget(hw1p1);
    print(hw1p1o);
    cout << "===============\n";
    Solution51 s51;
    vector<vector<string>> hw1p2;

    // for ( int n = 1; n < 10; n ++){
    //     cout << "for n : " << n << endl;
    //     hw1p2 = s51.solveNQueens(n);
    //     cout<<hw1p2.size()<<endl;
    //     print(hw1p2);

    // }
    Solution37 s37;    
    vector<vector<char>> board;
    // board = {{'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}};
    // print(board);
    // s37.solveSudoku(board);
    // cout << "\n";
    // print(board);

    // board = {{'5','3','.','6','7','8','9','1','2'},{'6','7','2','1','9','5','3','4','8'},{'1','9','8','3','4','2','5','6','7'},{'8','5','9','7','6','1','4','2','3'},{'4','2','6','8','5','3','7','9','1'},{'7','1','3','9','2','4','8','5','6'},{'9','6','1','5','3','7','2','8','4'},{'2','8','7','4','1','9','6','3','5'},{'3','4','5','2','8','6','1','7','9'}};
    // print(board);
    // s37.solveSudoku(board);
    // cout << "\n";
    // print(board);
    cout << "===============\n";
    Solution46 s46;
    vector<int> hw1p4;
    hw1p4 = {1,2,3};
    auto hw1p4o = s46.permute(hw1p4);
    print(hw1p4o);

    return 0;
}


