#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> twoSum1(vector<int>& nums,int target)
    {
        for (int i =0; i <nums.size(); i++) {
            for (int j=i+1;j<nums.size(); j++) {
                if(nums[i]+nums[j] == target)
                    return vector<int> {i,j};
            }
        }
        return vector<int> {};
    }
    vector<int> twoSum(vector<int>& nums,int target)
    {
        sort(nums.begin(),nums.end());
        int left = 0;
        int right = nums.size()-1;
        while (left < right)
        {
            if(nums.at(left)+nums.at(right) == target)
                return vector<int>{left,right};
            else if (nums.at(left)+nums.at(right) < target)
                left ++;
            else if (nums.at(left)+nums.at(right) > target)
                right --;
        }
        return {};
    }
};


int main()
{
    vector<int> nums = {3,2,4};
    int target = 6;
    Solution sol;
    auto res = sol.twoSum(nums,target);

    cout<<res[0]<<" "<<res[1]<<endl;

    return 0;
}

