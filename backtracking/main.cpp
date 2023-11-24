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

    Solution698 s689;
    vector<int> nums = {4,3,2,3,5,2,1};
    int k = 4;
    cout << s689.canPartitionKSubsets(nums, k) << endl;
    nums = {1,2,3,4};
    k = 3;
    cout << s689.canPartitionKSubsets(nums, k) << endl;
    nums = {960,3787,1951,5450,4813,752,1397,801,1990,1095,3643,8133,893,5306,8341,5246};
    k = 6;
    cout << s689.canPartitionKSubsets(nums, k) << endl;
    return 0;
}


