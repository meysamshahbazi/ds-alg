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
	const static int MAX = 100 + 1;
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

class Solution300_1 {
	vector<int> m_nums;
	int *memory{nullptr};
public:
	int lis(int idx) {
		if (idx == (int) m_nums.size())
			return 0;

		auto &ret = memory[idx];
		if (ret != -1)
			return ret;

		ret = 0;
		for (int i = idx + 1; i < m_nums.size(); i++)
			if (m_nums[i] > m_nums[idx])
				ret = max(ret, lis(i));
		
		ret += 1; // for including ith index
		return ret;
	}

    int lengthOfLIS(vector<int>& nums) {
		memory = new int[nums.size() + 1];
		memset(memory, -1,(nums.size() + 1)*sizeof(int));
		m_nums = nums;
		m_nums.insert(m_nums.begin(), INT32_MIN);
		int lis_0 = lis(0);
		delete[] memory;
		return lis_0 - 1;
    }
};

// https://leetcode.com/problems/longest-common-subsequence/
class Solution1143 {
	string m_text1, m_text2;
	const static int MAX = 1001;
	int memory[MAX][MAX];
public:
	int lcs(int idx1, int idx2)
	{
		if (idx1 == m_text1.size() || idx2 == m_text2.size())
			return 0;

		auto &ret = memory[idx1][idx2];
		if (ret != -1)
			return ret;

		if (m_text1[idx1] == m_text2[idx2])
			return 1 + lcs(idx1 + 1, idx2 + 1);
		
		int option1 = lcs(idx1 + 1, idx2);
		int option2 = lcs(idx1, idx2 + 1);
		return ret = max(option1, option2);
	}
    int longestCommonSubsequence(string text1, string text2) {
		memset(memory, -1,sizeof(memory));
		m_text1 = text1;
		m_text2 = text2;
		return lcs(0, 0);
    }
};

int mem_ss[500 + 1][2000 + 1];
vector<int> values_ss;

int subset_sum_dp(int idx, int target)
{
	if (idx == (int) values_ss.size() )
		return target == 0;

	auto &ret = mem_ss[idx][target];
	if (ret != -1)
		return ret;

	int leave = subset_sum_dp(idx + 1, target);
	int pick = 0;
	if (target >= values_ss[idx])
		pick = subset_sum_dp(idx + 1, target - values_ss[idx]);

	if (leave == 1 || pick == 1)
		return ret = 1;

	return ret = 0;
}

bool subset_sum(const vector<int> &values, int target)
{
	memset(mem_ss, -1, sizeof(mem_ss));
	values_ss = values;
	return subset_sum_dp(0, target) == 1;
}

// https://leetcode.com/problems/partition-equal-subset-sum/
class Solution416 {
	vector<int> m_nums;
	char mem[201][100*200+1]; // 1 we can 0 we cant, and -1 means not explored yet.
	int m_sum{0};
public:
	char diff(int idx, int picked_sum)
	{
		if (idx == (int) m_nums.size() )
			return 2 * picked_sum == m_sum;

		auto &ret = mem[idx][picked_sum];
		if (ret != -1)
			return ret;

		char leave = diff(idx + 1, picked_sum); // leave choice!
		char pick = diff(idx + 1, picked_sum + m_nums[idx]);

		if (leave == 1 || pick == 1)
			return ret = 1;

		return ret = 0;
	}
    bool canPartition(vector<int>& nums) {
		m_nums = nums;
		m_sum = accumulate(m_nums.begin(), m_nums.end(), 0);
		
		if (m_sum %2 != 0)
			return false;
			
		memset(mem, -1, sizeof(mem));

		return diff(0, 0) == 1;
    }
};

// https://leetcode.com/problems/maximum-height-by-stacking-cuboids/
class Solution1691 {
public:
    int maxHeight(vector<vector<int>>& cuboids) {
        
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

	vector<int> nums = {10,9,2,5,3,7,101,18};
	Solution300 s300;
	cout << s300.lengthOfLIS(nums) << endl;

	Solution300_1 s300_1;
	vector<int> nums_1 = {10,9,2,5,3,7,101,18};
	cout<<s300_1.lengthOfLIS(nums_1)<<endl;;
	// 
	Solution1143 s1143;
	cout << s1143.longestCommonSubsequence("abcde", "ace") << endl;
	// hw1 p 1
	vector<int> hw1p1 = {3, 12, 4, 12, 5, 2};
	cout << subset_sum(hw1p1, 9) << endl;
	hw1p1 = {3, 40, 4, 12, 5, 2};
	cout << subset_sum(hw1p1, 30) << endl;
	
	Solution416 s416;
	vector<int> hw1p2 = {1,5,11,5};
	cout<<s416.canPartition(hw1p2)<<endl;
	hw1p2 = {1,2,3,5};
	cout<<s416.canPartition(hw1p2)<<endl;
	return 0;
}

