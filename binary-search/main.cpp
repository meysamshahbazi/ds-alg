#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <cmath>
#include <climits>
#include <map>

using namespace std;

template<class T>
void print(vector<T> &v)
{
    for (int i = 0; i < (int) v.size(); ++i) {
		cout << v[i] << " ";
	}
    cout << endl;
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

// hw1 p1
// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
class Solution34 {
public:
    int binary_search_left(vector<int> &nums, int val) {
        int start = 0, end = (int) nums.size() - 1;

        while (start <= end) {
            int mid = start + (end - start) / 2;

            if (nums[mid] == val) {
                if (mid == 0 || nums[mid - 1] < val)
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

    int binary_search_right(vector<int> &nums, int val) {
        int start = 0, end = (int) nums.size() - 1;

        while (start <= end) {
            int mid = start + (end - start) / 2;

            if (nums[mid] == val) {
                if (mid == (int) nums.size() - 1 || nums[mid + 1] > val)
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
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = binary_search_left(nums, target);
        int right = binary_search_right(nums, target);
        return {left, right};
    }
};

class Solution34_1 {
public:
    int BSfindFirst(vector<int> &nums, int val) {
        int start = 0, end = (int) nums.size() - 1;

        while (start < end) {
            int mid = start + (end - start) / 3;
            if (nums[mid] < val)
                start = mid + 1;
            else if (nums[mid] > val)
                end = mid -1;
            else 
                end = mid;
        }
        if (start <= 0 || start >= (int)nums.size())
            return -1;
        return nums[start] == val? start : -1;
    }
    int BSfindLast(vector<int> &nums, int val) {
        int start = 0, end = (int) nums.size() - 1;

        while (start < end) {
            int mid = start + (end - start + 1) / 2;

            if (nums[mid] < val)
                start = mid + 1;
            else if (nums[mid] > val)
                end = mid -1;
            else 
                start = mid;
        }

        if (start < 0 || start >= (int) nums.size())
            return -1;
        return nums[start] == val ? start : -1;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        return {BSfindFirst(nums, target), BSfindLast(nums, target)};
    }   
};

// better aproach . try to use this style!!
class Solution34_2 {
public:
    int BSfindFirst(vector<int> &nums, int val) {
        int start = 0, end = (int) nums.size() - 1, pos = -1;

        while (start <= end) {
            int mid = start + (end - start) / 2;
            if (nums[mid] < val) 
                start = mid + 1;
            else if (nums[mid] > val) 
                end = mid - 1;
            else {
                pos = mid;
                end = mid - 1;
            }
        }
        return pos;
    }
    int BSfindLast(vector<int> &nums, int val) {
        int start = 0, end = (int) nums.size() - 1, pos = -1;

        while (start <= end) {
            int mid =  start + (end - start) / 2;
            if (nums[mid] < val)
                start = mid + 1;
            else if (nums[mid] > val)
                end = mid - 1;
            else 
                pos = mid, start = mid + 1; 
        }
        return pos;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        return {BSfindFirst(nums, target), BSfindLast(nums, target)};
    }   
};

// using stl
class Solution34_3 {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        auto p = equal_range(nums.begin(), nums.end(), target);

        if (p.first == nums.end())
            return {-1, -1};

        int x = p.first - nums.begin();
        int y = p.first - nums.begin();

        if (nums[x] != target)
            return {-1, -1};
        
        return {x, y - 1};
    }
};

// hw1 p2
// https://leetcode.com/problems/find-right-interval/
class Solution436 { // based on stl!
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
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
};

class Solution436_1 {
public:
    int BSfindFirst(vector<vector<int>> &startings, int eval) {
        int start = 0, end = (int) startings.size() - 1, pos = -1;

        while (start <= end) {
            int mid = start + (end - start) / 2;
            if (startings[mid][0] < eval) 
                start = mid + 1;
            else if (startings[mid][0] >= eval)
                end = mid - 1, pos = mid;
        }
        return pos;
    }

    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        vector<vector<int>> startings;
        for (int i = 0; i < intervals.size(); ++i)
            startings.push_back({intervals[i][0], i});

        sort(startings.begin(), startings.end());

        vector<int> ans(intervals.size(), -1);
        for (int i = 0; i < (int) intervals.size(); i++) {
            int idx = BSfindFirst(startings, intervals[i][1]);
            if (idx != -1)
                ans[i] = startings[idx][1];
        }
        return ans;
    }
};

class Solution436_2 { // based on STL map lower_bound
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        map<int, int> mp;
        
        for (int i = 0; i < (int) intervals.size(); i++)
            mp[intervals[i][0]] = i;


        vector<int> ans(intervals.size(), -1);
        for (int i = 0; i < (int) intervals.size(); i++) {
            auto it = mp.lower_bound(intervals[i][1]);
            
            if (it != mp.end())
                ans[i] = it->second;
        }
        return ans;
    }
};

// hw1 p3
// https://leetcode.com/problems/valid-triangle-number/
class Solution611 {
public:
    int triangleNumber(vector<int>& nums) {
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
};


// hw1 p4
// https://leetcode.com/problems/arranging-coins/
class Solution441 {
public:
    bool possible(int n, long long rows) {
        long sum = (rows * (rows + 1)) / 2;
        return n >= sum;
    }
    int arrangeCoins(int n) {
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
};
// https://leetcode.com/problems/first-bad-version/
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);
class Solution {
    bool isBadVersion(int version) {
        return true;
    }
public:
    int firstBadVersion(int n) {
        int left = 1, right = n, answer = 0;
        while (left <= right) {
            int mid = left + (right- left) / 2;
            if (isBadVersion(mid)) {
                right = mid - 1;
                answer = mid;
            }
            else 
                left = mid + 1;
        }
        return answer;
    }
};

// hw2 p1
// https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/
class Solution1283 {
public:
    bool divide_less_than(vector<int> &nums, double divisor, int threshold) {
        int sum = 0;

        for (auto &n: nums)
            sum += ceil(n / divisor);

        return sum <= threshold;
    }
    int smallestDivisor(vector<int>& nums, int threshold) {
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
};

// hw2 p2
// https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/
class Solution1482 {
public:
    bool PossibleToMakeBouquet(vector<int>& bloomDay, int m, int k, int day) {
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

    int minDays(vector<int>& bloomDay, int m, int k) {
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
};

// hw2 p3
// https://leetcode.com/problems/heaters/
class Solution475 {
public:
    bool canWarm(vector<int>& houses, vector<int>& heaters, int radius) {
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

    int findRadius(vector<int>& houses, vector<int>& heaters) {
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
};

// hw3 p1
// https://leetcode.com/problems/missing-element-in-sorted-array/ [premium]
int numOfMissing(vector<int> &nums, int left, int right) {
    return nums[right] - nums[left] - right + left;
}

int missingElement(vector<int> &nums, int k){

}

// int missingElement(vector<int> &nums, int k)
// {
//     int left = 0, right = (int) nums.size() - 1;
//     int answer;

//     k--;
//     while (left <= right) {
//         int mid = left + (right - left) / 2;
//         if (numOfMissing(nums, left, mid) > k) {
//             k -= numOfMissing(nums, left, mid);
//             left = mid + 1;   
//         }
//         else
//             right = mid;
//     }

//     cout << "right " << left << endl;
//     return answer;
// }

// hw3 p2
// https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/
class Solution668 {
public:
    int findKthNumber(int m, int n, int k) {
        int left = 1, right = m*n;

        int ans = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            int nb_of_less_than = 0;
            for (int i = 1; i <= mid && i <= n; i++){
                if (mid / i <= m)
                    nb_of_less_than += mid / i;
                else 
                    nb_of_less_than += m /i;
                // nb_of_less_than += min(mid, m); 
            }

            if (nb_of_less_than > k)
                left = mid + 1;
            else if (nb_of_less_than < k)
                right = mid - 1;
            else
                return mid;    
        }
        return -1;
    }
};

// hw4 p1
// https://leetcode.com/problems/sqrtx/
int mySqrt(int x)
{
    double EPS = 0.00001;
    double start = EPS, end = (double) 2*x;

    while (fabs(end - start) > EPS) {
        double mid = start + (end - start) / 2.0f;
        if (mid*mid - x < 0.0f)
            start = mid;
        else 
            end = mid;
    }
    return end; 
}

// https://www.spoj.com/problems/PIE/
double circle_area(double r) {
	const double PI = acos(-1.0);
	return PI * r * r;
}

bool onePeiceForEachOne(vector<double> &pie_volume, int people, double area)
{
	int people_count = 0;

	for (int i = 0; i < (int) pie_volume.size(); i++) {
		people_count += floor(pie_volume[i] / area);
		if (people_count >= people)
			return true;
	}
	return false;
}

double largest_area(vector<double> &pie_radius, int people) {

	vector<double> pie_volume(pie_radius.size());
	for (int i = 0; i < (int) pie_volume.size(); i++)
		pie_volume[i] = circle_area(pie_radius[i]);
	auto it = max_element(pie_volume.begin(), pie_volume.end());
	double start = 0, end = (double) *it;
	double mid;
	for (int i = 0; i < 100; i++) {
		mid = start + (end - start) / 2.0f;
        if (onePeiceForEachOne(pie_volume, people, mid))
            start = mid;
        else 
            end = mid;
	}

	return mid;
}

// https://leetcode.com/problems/binary-search/
class Solution704 {
public:
    int search(vector<int>& nums, int target) {
        int start = 0, end = (int) nums.size() - 1;

        while (start <= end) {
            int mid = start + (end - start) / 2;

            if (nums[mid] == target) 
                return mid;
            if (nums[mid] < target)
                start = mid + 1;
            else if (nums[mid] > target)
                end = mid - 1;
        }
        return -1;
    }
};

// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
class Solution153 {
public:
    inline int get_perv(int idx, int sz) {
        if (idx == 0)
            return sz - 1;
        return idx - 1;
    }
    int findMin(vector<int>& nums) {
        int start = 0, end = (int) nums.size() - 1;
        int sz = (int) nums.size();
        int mid;
        while (start <= end) {
            mid = start + (end - start)/2;
            int prv = get_perv(mid, sz);;
            if (nums[mid] < nums[prv])
                break;

            if (nums[end] > nums[mid])
                end = mid - 1;
            else 
                start = mid + 1;
        }
        return nums[mid];
    }
};

// https://leetcode.com/problems/search-in-rotated-sorted-array/
class Solution33 {
public:
    int search(vector<int>& nums, int target) {
        
    }
};

int main()
{
    Solution153 s153;
    vector<int> v153 = {4,5,6,7,0,1,2};
    cout << s153.findMin(v153) << endl;

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
    Solution34 s34;
    vector<int> hw1p1 = {5,7,7,8,8,10};
    vector<int> res_hw1p1  = s34.searchRange(hw1p1, 6);
    print(res_hw1p1);
    
    // hw1 p2
    vector<vector<int>> hw1p2 = {{3,4},{2,3},{1,2}};
    hw1p2 = {{1,2}};
    hw1p2 = {{1,4},{2,3},{3,4}};
    Solution436 s436;
    auto hw1p2_res = s436.findRightInterval(hw1p2);
    print(hw1p2_res);

    // hw1 p3
    vector<int> hw1p3 = {2,2,3,4};
    hw1p3 = {4,2,3,4};
    Solution611 s611;
    cout << s611.triangleNumber(hw1p3) << endl;
    // hw1 p4 
    Solution441 s441;
    cout << s441.arrangeCoins(8) << endl;
    
    // hw 2 p 1
    vector<int> hw2p1 = {1,2,5,9};
    Solution1283 s1283;
    cout << s1283.smallestDivisor(hw2p1, 6)<<endl;

    // hw2 p2
    Solution1482 s1482;
    vector<int> hw2p2 = {1,10,3,10,2};
    cout << s1482.minDays(hw2p2, 3, 1) << endl;
    // hw2 p3
    vector<int> houses = {1,5};
    vector<int> heaters = {10};
    // cout<<canWarm(houses,heaters, 1)<<endl;
    Solution475 s475;
    cout << s475.findRadius(houses, heaters)<<endl;

    // hw3 p1 
    // vector<int> hw3p1 = {4,7,9,10};
    // missingElement(hw3p1, 3);
    
    // hw3 p2
    Solution668 s668;
    cout << s668.findKthNumber(3, 3, 5) << endl;


    /*
    // hw4 p1
    cout<<mySqrt(36)<<endl;
    // hw4 p2
    vector<double> hw4p2 = {4, 3, 3};   
    cout<<largest_area(hw4p2,4)<<endl;
    */
    return 0;
}
