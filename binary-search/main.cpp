#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>

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

// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
vector<int> searchRange(vector<int>& nums, int target) 
{
    int start = 0, end = (int) nums.size() - 1;

    int start_range = -1;
    int end_range = -1;
    int mid = -1;
    
    while (nums[start] != target || nums[end] != target) {

    }

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

    return 0;
}
