#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <bits/stdc++.h> 
#include <unordered_map>

using namespace std;

const int MAX = 2000 + 1;
int memory[MAX][MAX];

int knapsack(int idx, int remain_capacity, vector<int> &sizes, vector<int> &values)
{
	if (remain_capacity <= 0)
		return 0;

	if (idx == (int) sizes.size())
		return 0;

	auto &ret = memory[idx][remain_capacity];

	if (sizes[idx] > remain_capacity) { // dont pick!
		return ret = knapsack(idx + 1, remain_capacity, sizes, values);
	}

	int pick_choice = values[idx] + knapsack(idx + 1, remain_capacity - sizes[idx], sizes, values);
	int leave_choice = knapsack(idx + 1, remain_capacity, sizes, values);

	return ret = max(pick_choice, leave_choice);
}

// https://leetcode.com/problems/longest-increasing-subsequence/
class Solution300 {
	vector<int> nums;
	const static int MAX = 2500 + 1;
	int memory[MAX][MAX];
public:
	int lis(int idx, int min_idx) {
		if (idx == nums.size())
			return 0;

		auto &ret = memory[idx][min_idx];
		if (ret != -1)
			return ret;


		int choice1 = lis(idx + 1, min_idx); // leave choice
		int choice2 = 0;
		
		if ( min_idx >= nums.size() || nums[idx] > nums[min_idx]) // we can pick
			choice2 = 1 + lis(idx + 1, idx);
		
		return ret = max(choice1, choice2);

	}

    int lengthOfLIS(vector<int>& nums) {
		this->nums = nums;
		memset(memory, -1, sizeof(memory));
		return lis(0, nums.size());
    }
};

int main() 
{
	freopen("../data.txt", "rt", stdin);
	memset(memory, -1, MAX*MAX);

	int capacity, N;
	cin >> capacity >> N;

	vector<int> sizes;
	vector<int> values;

	while (N--) {
		int s, v;
		cin >> s >> v;

		sizes.push_back(s);
		values.push_back(v);
	}
	
	cout << knapsack(0, capacity, sizes, values) << endl;
	//

	vector<int> nums = {10,9,2,5,3,7,101,18};
	Solution300 s300;
	cout << s300.lengthOfLIS(nums) << endl;

	return 0;
}

