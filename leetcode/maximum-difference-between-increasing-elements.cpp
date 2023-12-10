// https://leetcode.com/problems/maximum-difference-between-increasing-elements/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// 1 <= nums[i] <= 10^9
class Solution2016 {
public:
    int maximumDifference1(vector<int>& nums) { // O(n^2)
        int dif = -1;
        for (int i = 0; i < (int) nums.size() - 1; i++)
            for (int j = i + 1; j < nums.size(); j++)
                if ( nums[j] > nums[i] && nums[j] - nums[i] > dif)
                    dif = nums[j] - nums[i];
        
        return dif;
    }

    int maximumDifference2(vector<int>& nums) {
        vector<int> mins(nums); 

        for (int i = 1; i < (int)nums.size(); i++)
            mins[i] = min(mins[i - 1], nums[i]);

        int dif = -1;
        for (int i = (int) nums.size() - 1; i > 0; i--)
            dif = max(dif, nums[i] - mins[i - 1]);

        if (dif == 0)
            return -1;

        return dif;
    }

    int maximumDifference(vector<int>& nums) {
        int min_so_far = nums.front();
        int dif = -1;
        // for (int i = 1; i < nums.size(); i++) {
        for (auto &n : nums) {
            dif = max(dif, n - min_so_far);
            min_so_far = min(min_so_far, n);
        }

        if (dif == 0)
            return -1;

        return dif;
    }
};

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/
class Solution121 {
public:
    int maxProfit(vector<int>& prices) {
        int min_so_far = prices.front();
        int dif = 0;

        for (auto &n : prices) {
            dif = max(dif, n - min_so_far);
            min_so_far = min(min_so_far, n);
        }

        return dif;
    }
};


int main() {

    Solution2016 s;
    vector<int> nums;
    
    nums = {7,1,5,4};
    cout << s.maximumDifference(nums) << endl;

    nums = {87,68,91,86,58,63,43,98,6,40};
    cout << s.maximumDifference(nums) << endl;

    return -1;
}

