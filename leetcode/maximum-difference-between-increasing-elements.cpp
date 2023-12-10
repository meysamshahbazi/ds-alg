// https://leetcode.com/problems/maximum-difference-between-increasing-elements/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// 1 <= nums[i] <= 10^9
class Solution {
    
public:
    int maximumDifference1(vector<int>& nums) { // O(n^2)
        int dif = -1;
        for (int i = 0; i < (int) nums.size() - 1; i++)
            for (int j = i + 1; j < nums.size(); j++)
                if ( nums[j] > nums[i] && nums[j] - nums[i] > dif)
                    dif = nums[j] - nums[i];
        
        return dif;
    }
    int maximumDifference(vector<int>& nums) {
        vector<pair<int,int>> nums_idx;
        
        for (int i = 0; i < nums.size(); i++)
            nums_idx.push_back({nums[i], i});

        sort(nums_idx.begin(), nums_idx.end());
        
        

        return -1;
    }
};



int main() {

    Solution s;
    vector<int> nums;
    
    nums = {7,1,5,4};
    s.maximumDifference(nums);
}