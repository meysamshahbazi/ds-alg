#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <stack>
#include <queue>
#include<climits>

using namespace std;

template<class T>
void print(vector<T> &v)
{
    for (int i = 0; i < (int) v.size(); ++i) {
		cout << v[i] << " ";
	}
    cout<<endl;
}

void insertion_sort(vector<int> &nums)
{
    for (int i = 1; i < (int) nums.size(); i++) {
        int key = nums[i];
        int j = i - 1;
        while (j >=0 && nums[j] > key) {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = key;
    }
}
// hw1 p1
void insertion_sort_v2(vector<int> &nums)
{
    for (int i = 1; i < (int) nums.size(); i++) {
        for (int j = i - 1; j >=0 && nums[j] < nums[j + 1]; j--)
            swap(nums[j + 1], nums[j]);
    }
}

void selection_sort(vector<int> &nums)
{
    int n = nums.size();

    for (int i = 0; i < n - 1; i++){
        int mn_idx = i;
        for (int j = i + 1; j < n; j++)
            if (nums[j] < nums[mn_idx])
                mn_idx = j;

        swap(nums[i], nums[mn_idx]);
    }
}

void count_sort(vector<int> &array)
{
    int size = array.size();
    int mxValue = array[0];
    for (int i = 1; i < size; i++)
        if (array[i] > mxValue)
            mxValue = array[i];

    vector<int> count(mxValue + 1);
    for (int i = 0; i < size; i++)
        count[array[i]] += 1;

    int idx = 0;
    for (int i = 0; i < mxValue; i++)
        for (int j = 0; j < count[i]; j++, idx++)
            array[idx] = i;
}

// hw1 p2 p3
// https://leetcode.com/problems/sort-an-array/
vector<int> count_sort_v2(vector<int> &nums)
{
    int size = nums.size();
    int mxValue = nums[0];
    for (int i = 1; i < size; i++)
        if (nums[i] > mxValue)
            mxValue = nums[i];

    int mnValue = nums[0];
    for (int i = 1; i < size; i++)
        if (nums[i] < mnValue)
            mnValue = nums[i];

    vector<int> count(mxValue - mnValue + 1);
    for (int i = 0; i < size; i++)
        count[nums[i] - mnValue] += 1;

    int idx = 0;
    for (int i = mnValue; i < mxValue + 1; i++)
        for (int j = 0; j < count[i - mnValue]; j++, idx++)
            nums[idx] = i;
        
    return nums;
}
// hw1 p4
void count_sort_string_v1(vector<string> &array)
{
    int size = array.size();
    int mxValue = array[0].front();
    
    for (int i = 1; i < size; i++)
        if (array[i].front() > mxValue)
            mxValue = array[i].front();

    vector<vector<string>> count(mxValue + 1);
    for (int i = 0; i < size; i++)
        count[array[i].front()].push_back(array[i]);

    int idx = 0;
    for (int i = 0; i < mxValue; i++)
        for (int j = 0; j < count[i].size(); j++, idx++)
            array[idx] = count[i][j];
}

int str2index(string &str)
{
    return (str[0] - 'a') * 26 + (str[1] - 'a');
}
// hw1 p5
void count_sort_string_v2(vector<string> &array)
{
    int size = array.size();
    int mxValue = 26*26;

    vector<vector<string>> count(mxValue);
    for (int i = 0; i < size; i++)
        count[str2index(array[i])].push_back(array[i]);

    int idx = 0;
    for (int i = 0; i < mxValue; i++)
        for (int j = 0; j < count[i].size(); j++, idx++)
            array[idx] = count[i][j];
}
// hw1 p6
vector<int> count_sort_hw1p6(const vector<int> &array)
{
    int size = array.size();
    int mxVal = array[0];
    for (int i = 1; i < size; i++)
        if(array[i] > mxVal)
            mxVal = array[i];

    vector<int> count(mxVal + 1);
    for (int i = 0; i < size; i++)
        count[array[i]] += 1;

    for (int i = 1; i < size; i++)
        count[i] += count[i - 1];

    vector<int> output(size);

    for (int i = size - 1; i >= 0; --i) {
        output[count[array[i]] - 1] = array[i];
        count[array[i]] -= 1;
    }
    return output;
}


// hw2 p1
// https://leetcode.com/problems/minimum-absolute-difference/
vector<vector<int>> minimumAbsDifference(vector<int>& arr)
{
    vector<vector<int>> output;
    
    if (arr.size() == 1)
        return output;
    
    sort(arr.begin(), arr.end());

    if (arr.size() == 2) {
        output.push_back({arr[0], arr[1]});
        return output;
    }

    int mnValue = arr[1] - arr[0];
    for(int i = 1; i < (int) arr.size() - 1; ++i) {
        if(arr[i + 1] - arr[i] < mnValue) {
            mnValue = arr[i + 1] - arr[i];
        }
    }

    for(int i = 0; i < (int) arr.size() - 1; ++i) {
        if(arr[i + 1] - arr[i] == mnValue) {
            output.push_back({arr[i], arr[i + 1]});
        }
    }

    return output;
}
// hw2 p2
// https://leetcode.com/problems/largest-perimeter-triangle/
int largestPerimeter(vector<int>& nums)
{
    sort(nums.begin(), nums.end());

    for (int i = nums.size() - 1; i >= 2; i--) {
        if (nums[i] < nums[i - 1] + nums[i - 2])
            return nums[i] + nums[i - 1] + nums[i - 2]; 
    }
    return 0;
}
// hw2 p3
// https://leetcode.com/problems/array-partition/
int arrayPairSum(vector<int>& nums)
{
    sort(nums.begin(), nums.end());

    int sum = 0;

    for (int i = 0; i < (int) nums.size() / 2; ++i) 
        sum += nums[2 * i];
    return sum;
}

// https://leetcode.com/problems/wiggle-sort/ [premium]
class Solution280 {
public:
	// O(nlogn) time and O(1) space
	void wiggleSort1(vector<int> &nums) {
		sort(nums.begin(), nums.end());

		for (int i = 1; i + 1 < (int) nums.size(); i += 2)
			swap(nums[i], nums[i + 1]);
	}

	// O(nlogn) time and O(n) space
	void wiggleSort2(vector<int> &nums) {
		sort(nums.begin(), nums.end());

		vector<int> ans;	// O(n) extra memory

		int left = 0, right = nums.size()-1;
		while (left <= right) {
			ans.push_back(nums[left]);
			if(left != right)	// don't add same position twice
				ans.push_back(nums[right]);
			left += 1;
			right -= 1;
		}
		nums = ans;
	}
};


// https://leetcode.com/problems/wiggle-sort-ii/
void wiggleSort(vector<int> &nums)
{

}

// https://leetcode.com/problems/eliminate-maximum-number-of-monsters/
int eliminateMaximum(vector<int>& dist, vector<int>& speed)
{
    vector<double> time(dist.size());

    for (int i = 0;  i < (int) dist.size(); i ++)
        time[i] = dist[i]/static_cast<double>(speed[i]);
    

    sort(time.begin(), time.end());

    int num = 0;
    for (int i = 0; i < (int) time.size(); i++) {
        if (time[i] > i) 
            num++;
        else 
            break;
    }

    return num; 
}

// https://leetcode.com/problems/maximize-sum-of-array-after-k-negations/
int largestSumAfterKNegations(vector<int>& nums, int k)
{
    sort(nums.begin(), nums.end());

    int idx = 0;
    for (int i = 0; i < nums.size() && idx < k; i++ ) {
        if (nums[i] < 0) {
            nums[i] = -nums[i];
            idx++;
        }
        else 
            break;
    }

    sort(nums.begin(), nums.end());

    while (idx < k) {
        nums[0] = -nums[0];
        idx++;    
    }

    return accumulate(nums.begin(), nums.end(), 0);
}

// hw3 p2
// https://leetcode.com/problems/shortest-unsorted-continuous-subarray/
int findUnsortedSubarray_v1(vector<int> &nums)
{
    // O(nlogn)
    vector<int> sorted(nums);
    
    sort(nums.begin(), nums.end());

    int len = nums.size();

    for (int i = 0; i < (int) nums.size(); i++) {
        if (nums[i] == sorted[i])
            len--;
        else 
            break;
    }

    if (len == 0) 
        return len;

    for (int i = (int) nums.size() - 1; i >= 0; i--) {
        if (nums[i] == sorted[i])
            len--;
        else 
            break;
    }
    return len;
}

// O(n)
// https://leetcode.com/problems/shortest-unsorted-continuous-subarray/
class Solution581 {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int mx = INT_MIN;
        int mn = INT_MAX;
        int left = -1, right = -1;

        for (int i = 0; i < (int)nums.size(); i++) {
            mx = max(mx, nums[i]);
            if (mx > nums[i])
                right = i;
        }

        for (int i = (int) nums.size() - 1; i >= 0; i--) {
            mn = min(mn, nums[i]);
            if (mn < nums[i])
                left = i;
        }
        if (right == -1)
            return 0;

        return right - left + 1;
    }
};

bool sortbysec(const pair<int,int> &a,const pair<int,int> &b)
{
    return (a.second < b.second);
}

// https://leetcode.com/problems/most-profit-assigning-work/
int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker)
{
    sort(worker.begin(), worker.end());

    int n = (int) difficulty.size();
    int m = (int) worker.size();

    vector<pair<int,int>> difficulty_profit(n);
    
    for (int i = 0; i < n; i++)
        difficulty_profit[i] = make_pair(difficulty[i], profit[i]);
    
    sort(difficulty_profit.begin(), difficulty_profit.end(), sortbysec);

    int total_profit = 0;

    int idx_tasks = n - 1;
    int i = m - 1;

    while (i >=0 && idx_tasks >= 0) {
        if (worker[i] >= difficulty_profit[idx_tasks].first) {
            total_profit += difficulty_profit[idx_tasks].second;
            i--;
        }
        else 
            idx_tasks--;
    }

    return total_profit;

}

// hw3 p3
// https://leetcode.com/problems/reduction-operations-to-make-the-array-elements-equal/
class Solution1887 {
public:
    int reductionOperations(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int size = nums.size();
        int total_change = 0;

        int right = size - 1;

        for (int i = size - 2; i >= 0; --i)
            if (nums[i] != nums[i + 1])
                total_change += size - i - 1;

        return total_change;
    }
};

vector<int> read_vector() {
	int n;
	cin >> n;

	vector<int> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i];

	return v;
}

int main()
{
    // vector<int> v = read_vector();
	// insertion_sort(v);
    // selection_sort(v);
    // count_sort(v);
    vector<int> v = {5,8,1,6,2,0};
    // hw1 p 1
    insertion_sort_v2(v);
	for (int i = 0; i < (int) v.size(); ++i) {
		cout << v[i] << " ";
	}
    cout<<endl;
    // hw1 p2 p3
    vector<int> hw1p2 = {5,2,3,1};
    print(hw1p2);
    hw1p2 = count_sort_v2(hw1p2);
    print(hw1p2);
    // hw1 p4
    vector<string> hw1p4 = {"ziad", "belal", "adam", "baheir", "ali"};
    print(hw1p4);
    count_sort_string_v1(hw1p4);
    print(hw1p4);
    // hw1 p5
    vector<string> hw1p5 = {"axz", "axa", "zzz", "abc", "abe"};
    print(hw1p5);
    count_sort_string_v2(hw1p5);
    print(hw1p5);

    // hw2 p1
    vector<int> hw2p1 = {4,2,1,3};
    minimumAbsDifference(hw2p1);

    // hw2 p2
    vector<int> hw2p2 = {2,1,2};
    cout<<largestPerimeter(hw2p2)<<endl;
    
    //hw2 p3
    vector<int> hw2p3 = {1,4,3,2};
    cout<<arrayPairSum(hw2p3)<<endl;

    //hw2 p4 
    vector<int> hw2p4 = {3,5,2,1,6,4};
    hw2p4 = {1,5,1,1,6,4};
    hw2p4 = {1,1,2,1,2,2,1};
    wiggleSort(hw2p4);
    print(hw2p4);
    
    hw2p4 = {6,6,5,6,3,8};
    wiggleSort(hw2p4);
    print(hw2p4);

    // hw2 p5
    vector<int> dist = {3,2,4};
    vector<int> speed = {5,3,2};
    cout<<eliminateMaximum(dist,speed)<<endl;
    
    // hw2 p6
    vector<int> hw2p6 = {3,-1,0,2};
    cout<<largestSumAfterKNegations(hw2p6, 3)<<endl;

    cout << endl;

    // hw3 p1
    Solution581 s581;
    vector<int> hw3p1 = {2,6,4,8,10,9,15};
    hw3p1 = {1,3,2,2,2};
    print(hw3p1);
    // cout << findUnsortedSubarray_v1(hw3p1)<<endl;
    cout << s581.findUnsortedSubarray(hw3p1) << endl;
    hw3p1 = {1,2,3,4};
    // cout << findUnsortedSubarray_v1(hw3p1)<<endl;
    cout << s581.findUnsortedSubarray(hw3p1) << endl;
    
    // hw3 p2
    vector<int> difficulty = {2,4,6,8,10}, profit = {10,20,30,40,50}, worker = {4,5,6,7};
    cout << maxProfitAssignment(difficulty, profit, worker) << endl;
     cout << endl;
    // hw3 p3
    Solution1887 s1887;

    vector<int> hw3p3 = {5,1,3};
    cout << s1887.reductionOperations(hw3p3) << endl;
    hw3p3 = {1,1,1};
    cout << s1887.reductionOperations(hw3p3) << endl;
    hw3p3 = {1,1,2,2,3};
    cout << s1887.reductionOperations(hw3p3) << endl;
    
    return -1;
}


