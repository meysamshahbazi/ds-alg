#include <iostream>
#include <vector>
#include<algorithm>
#include <string>

using namespace std;

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

void insertion_sort_v2(vector<int> &nums)
{
    for (int i = 1; i < (int) nums.size(); i++) {
        for ( int j = i - 1; j >=0 && nums[j] < nums[j + 1]; j--)
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

// https://leetcode.com/problems/array-partition/
int arrayPairSum(vector<int>& nums)
{
    sort(nums.begin(), nums.end());

    int sum = 0;

    for (int i = 0; i < (int) nums.size() / 2; ++i) 
        sum += nums[2 * i];
    return sum;
}

vector<int> read_vector() {
	int n;
	cin >> n;

	vector<int> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i];

	return v;
}
template<class T>
void print(vector<T> &v)
{
    for (int i = 0; i < (int) v.size(); ++i) {
		cout << v[i] << " ";
	}
    cout<<endl;
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

    // hw2 p 1
    vector<int> hw2p1 = {4,2,1,3};
    minimumAbsDifference(hw2p1);

    // hw2 p2
    vector<int> hw2p2 = {2,1,2};
    cout<<largestPerimeter(hw2p2)<<endl;
    
    //hw2 p3
    vector<int> hw2p3 = {1,4,3,2};
    cout<<arrayPairSum(hw2p3)<<endl;
    return -1;
}


