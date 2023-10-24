#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <cmath>

using namespace std;

template<class T>
void print(vector<T> &v)
{
    for (int i = 0; i < (int) v.size(); ++i) {
		cout << v[i] << " ";
	}
    cout<<endl;
}

int binary_search(vector<int> &nums, int val)
{
    int start = 0, end = (int) nums.size() - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (nums[mid] == val) 
            return mid;
        if (nums[mid] < val)
            start = mid + 1;
        else if (nums[mid] > val)
            end = mid - 1;
    }
    return -1;
}

int binary_search_left(vector<int> &nums, int val)
{
    int start = 0, end = (int) nums.size() - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (nums[mid] == val) {
            if( mid == 0 || nums[mid - 1] < val)
                return mid;
            else 
                end = mid - 1;
        }
        if (nums[mid] < val)
            start = mid + 1;
        else if (nums[mid] > val)
            end = mid - 1;
    }
    return -1;
}

int binary_search_right(vector<int> &nums, int val)
{
    int start = 0, end = (int) nums.size() - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (nums[mid] == val) {
            if( mid == (int) nums.size() - 1 || nums[mid + 1] > val)
                return mid;
            else 
                start = mid + 1;
        }
        if (nums[mid] < val)
            start = mid + 1;
        else if (nums[mid] > val)
            end = mid - 1;
    }
    return -1;
}

// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
vector<int> searchRange(vector<int>& nums, int target) 
{
    int left = binary_search_left(nums, target);
    int right = binary_search_right(nums, target);

    return {left, right};
}

// https://leetcode.com/problems/find-right-interval/
vector<int> findRightInterval(vector<vector<int>>& intervals) 
{
    int size = (int) intervals.size();

    vector<int> right_intervals(size);

    vector<pair<int,int>> starts_with_idx(size);
    for (int i = 0; i < size; i++)
        starts_with_idx[i] = make_pair(intervals[i][0], i);

    sort(starts_with_idx.begin(), starts_with_idx.end());

    vector<int> starts(size);
    for (int i = 0; i < size; i++)
        starts[i] = starts_with_idx[i].first;

    for (int i = 0; i < size ; i++) {
        int end_i = intervals[i][1];
        auto it = lower_bound(starts.begin(), starts.end(), end_i);
        
        if (it != starts.end())
            right_intervals[i]  = starts_with_idx[it - starts.begin()].second;
        else 
            right_intervals[i] = -1;
    }

    return right_intervals;
}

// https://leetcode.com/problems/valid-triangle-number/
int triangleNumber(vector<int>& nums)
{
    sort(nums.begin(), nums.end());

    vector<int> pos_nums;
    for (auto p:nums)
        if (p > 0)
            pos_nums.push_back(p);

    int total = 0;
    
    for (int i = 0; i < (int) pos_nums.size() - 2; i++) {
        for (int j = i + 1; j < (int) pos_nums.size() - 1; j++) {
            auto it = lower_bound(pos_nums.begin() + j + 1, pos_nums.end(), pos_nums[i] + pos_nums[j]);
            int index =  it - pos_nums.begin() - j - 1;
            total += index;
        }
    }
    return total;
}

bool possible(int n, long long rows)
{
    long sum = (rows * (rows + 1)) / 2;
    return n >= sum;
}
// https://leetcode.com/problems/arranging-coins/
int arrangeCoins(int n) 
{
    int left = 0, right = n, answer = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (possible(n, mid)){
            left = mid + 1;
            answer = mid;
        }
        else 
            right = mid - 1;
    }
    return answer;
}

// https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/
/**
 * @brief Given an array of integers nums and an integer threshold,
 *  we will choose a positive integer divisor, divide all the array by it, and sum the division's result.
 *  Find the smallest divisor such that the result mentioned above is less than or equal to threshold.
 * Each result of the division is rounded to the nearest integer greater than or equal to that element. (For example: 7/3 = 3 and 10/2 = 5).

The test cases are generated so that there will be an answer.
 * 
 * @param nums 
 * @param threshold 
 * @return int 
 */
bool divide_less_than(vector<int> &nums, double divisor, int threshold)
{
    int sum = 0;
    for (auto &n: nums)
        sum += ceil(n / divisor);
    

    return sum <= threshold;
}
int smallestDivisor(vector<int>& nums, int threshold) 
{
    
    auto it = max_element(nums.begin(), nums.end());
    int start = 1, end = *it, answer = 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (divide_less_than(nums, mid, threshold) ) {
            end = mid - 1;
            answer = mid;
        }
        else 
            start = mid + 1;
    }
    
    return answer;
}

bool PossibleToMakeBouquet(vector<int>& bloomDay, int m, int k, int day)
{
    int bouquets = 0;
    
    int i = 0;

    while (i < (int) bloomDay.size() - k + 1) {
        bool bouquet_i = true;
        int j;
        for (j = i; j < i + k; j++) 
            if (bloomDay[j] > day){
                bouquet_i = false;
                break;
            }
        
        if (bouquet_i) {
            bouquets += 1;
            i += k;
        }
        else 
            i = j + 1;
        
        if (bouquets >= m)
            return true;
    }
    
    return false;
}

/**
 * @brief You are given an integer array bloomDay, an integer m and an integer k.
 * You want to make m bouquets. To make a bouquet, you need to use k adjacent flowers from the garden.
 * The garden consists of n flowers, the ith flower will bloom in the bloomDay[i] and then can be used in exactly one bouquet.
 * Return the minimum number of days you need to wait to be able to make m bouquets from the garden. If it is impossible to make m bouquets return -1.
 * https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/
 * @param bloomDay 
 * @param m 
 * @param k 
 * @return int 
 */
int minDays(vector<int>& bloomDay, int m, int k)
{
    if (m * k > (int) bloomDay.size())
        return -1;

    auto it = max_element(bloomDay.begin(), bloomDay.end());
    int start = 1, end = *it, answer = -1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (PossibleToMakeBouquet(bloomDay, m, k, mid) ) {
            end = mid - 1;
            answer = mid;
        }
        else 
            start = mid + 1;
    }
    
    return answer;
}

bool canWarm(vector<int>& houses, vector<int>& heaters, int radius)
{
    int idx = 0;
    int i = 0;
    while (i < (int) houses.size()) {
        if ( houses[i] <= heaters[idx] + radius && houses[i] >= heaters[idx] - radius ) {
            i++;
            continue;
        }
        else {
            if (idx < (int) heaters.size() - 1)
                idx++;
            else 
                return false;
        }
    }
    return true;
}

// https://leetcode.com/problems/heaters/
int findRadius(vector<int>& houses, vector<int>& heaters)
{
    sort(houses.begin(), houses.end());
    sort(heaters.begin(), heaters.end());

    int start = 0, end = houses.back() + heaters.back(), answer = 0;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (canWarm(houses, heaters, mid) ) {
            end = mid - 1;
            answer = mid;
        }
        else 
            start = mid + 1;
    }
    
    return answer;  
}

int main()
{
    vector<int> v { 2, 2, 2, 3, 4, 9, 17, 17, 17, 20 };
    cout << binary_search(v, 9) << endl;

    vector<int>::iterator it = lower_bound(v.begin(), v.end(), 17);

    if (it != v.end() ) {
        cout << "first element >= 17: " << *it << endl;
        cout << "\tindex: " << it - v.begin() << endl;
    }

    it = upper_bound(v.begin(), v.end(), 17);
    if (it != v.end())
        cout << "first element > 17: " << *it << endl;

    auto p = equal_range(v.begin(), v.end(), 17);
    cout << p.first - v.begin() << ", " << p.second - v.begin() << endl;

    // hw1 p1
    vector<int> hw1p1 = {5,7,7,8,8,10};
    vector<int> res_hw1p1  = searchRange(hw1p1, 6);
    print(res_hw1p1);
    
    // hw1 p2
    vector<vector<int>> hw1p2 = {{3,4},{2,3},{1,2}};
    hw1p2 = {{1,2}};
    hw1p2 = {{1,4},{2,3},{3,4}};
    auto hw1p2_res = findRightInterval(hw1p2);
    print(hw1p2_res);

    // hw1 p3
    vector<int> hw1p3 = {2,2,3,4};
    hw1p3 = {4,2,3,4};
    cout<<triangleNumber(hw1p3)<<endl;
    // hw1 p4 
    cout<<arrangeCoins(8)<<endl;
    
    // hw 2 p 1
    vector<int> hw2p1 = {1,2,5,9};
    cout<<smallestDivisor(hw2p1, 6)<<endl;

    // hw2 p2
    vector<int> hw2p2 = {1,10,3,10,2};
    cout<<minDays(hw2p2, 3,1)<<endl;
    // hw2 p3

    vector<int> houses = {1,5};
    vector<int> heaters = {10};
    // cout<<canWarm(houses,heaters, 1)<<endl;
    cout<<findRadius(houses, heaters)<<endl;

    return 0;
}
