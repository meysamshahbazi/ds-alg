#include <iostream>
#include <vector>
#include <cstring>
#include <climits>
#include <bits/stdc++.h> 
#include <unordered_map>
#include <unordered_set>

using namespace std;

template<class T>
void print(vector<T> &v)
{
    for (int i = 0; i < (int) v.size(); ++i) {
		cout << v[i] << " ";
	}
    cout<<endl;
}

template<class T>
void print(vector<vector<T>> &vec){
	for(auto &v : vec)
		print(v);
}

vector<int> tmp;	// Create with lst size

void merge_sorted_subarrays(vector<int> &array, int start, int mid, int end) {
	for (int i = start, j = mid + 1, k = start; k <= end; k++) {
		if (i > mid)
			tmp[k] = array[j++];
		else if (j > end) 
			tmp[k] = array[i++];
		else if (array[i] < array[j])
			tmp[k] = array[i++];
		else 
			tmp[k] = array[j++];
	}
	for (int i = start; i <= end; i++)
		array[i] = tmp[i];
}

void merge_sort(vector<int> &arr, int start, int end) {
	if (start == end)
		return;

	int mid = start + (end - start) / 2;
	merge_sort(arr, start, mid);
	merge_sort(arr, mid + 1, end);

	merge_sorted_subarrays(arr, start, mid, end);
}

void merge_sort(vector<int> &arr) {
	tmp = arr;
	merge_sort(arr, 0, (int) arr.size() - 1);
}

int make_pivot(vector<int> &vec, int start, int end) {
	int mid = start + (end - start) / 2;
	int pivot = vec[mid];
	int count = 0;
	for (int i = start; i <= end; i++)
		if (vec[i] < pivot)
			count += 1;

	int pivot_idx = start + count;
	swap(vec[pivot_idx], vec[mid]);

	for (int s = start, e = end; s < pivot_idx && pivot_idx < e; s += 1, e -= 1) {
		while (vec[s] < pivot)
			s += 1;
		
		while (vec[e] > pivot )
			e -= 1;
		
		if (s < pivot_idx && pivot_idx < e)
			swap(vec[s], vec[e]);
	}

	return pivot_idx;
}

void quicksort(vector<int> &vec, int start, int end) {
	if (start >= end)
		return;

	int pivot_idx = make_pivot(vec, start, end);
	quicksort(vec, start, pivot_idx - 1);
	quicksort(vec, pivot_idx + 1, end);
}

void quicksort(vector<int> &vec) {
	quicksort(vec, 0, (int) vec.size() - 1);
}


int make_pivot2(vector<int> &vec, int start, int end) {
	int mid = start + (end - start) / 2;
	int pivot = vec[mid];
	int count = 0;
	for (int i = start; i <= end; i++)
		if (vec[i] < pivot)
			count += 1;

	int pivot_idx = start + count;
	swap(vec[pivot_idx], vec[mid]);

	for (int s = start, e = end; s < pivot_idx && pivot_idx < e; s += 1, e -= 1) {
		while (vec[s] < pivot)
			s += 1;
		
		while (vec[e] >= pivot )
			e -= 1;
		
		if (s < pivot_idx && pivot_idx < e)
			swap(vec[s], vec[e]);
	}

	return pivot_idx;
}

void quicksort2(vector<int> &vec, int start, int end) {
	if (start >= end)
		return;

	int pivot_idx = make_pivot(vec, start, end);
	quicksort2(vec, start, pivot_idx - 1);
	quicksort2(vec, pivot_idx + 1, end);
}

void quicksort2(vector<int> &vec) {
	quicksort2(vec, 0, (int) vec.size() - 1);
}

// https://leetcode.com/problems/global-and-local-inversions/
class Solution775 {
public:
    bool isIdealPermutation(vector<int>& nums) {
		int start = 0;
		int end = (int) nums.size() - 1;

		while (start < end) {
			if (nums[start] > nums[start + 1]) {
				swap(nums[start], nums[start + 1]);
				start += 2;
			}
			else {
				start++;
			}
		}

		for (start = 0; start <= end; start++) {
			if (nums[start] != start)
				return false;
		}

		return true;
    }
};

// https://leetcode.com/problems/powx-n/
class Solution50 {
public:
    double myPow(double x, int n) {
        if (n == 0)
			return 1.0;
		if ( n == 1)
			return x;

		if ( n < 0 )
			return myPow(1 / x, -n); // cast to long long!

		double res = myPow(x, n / 2);
		if ( n %2 == 0) {
			return res * res;
		}
		
		return res * res * x;
    }
};

// https://leetcode.com/problems/largest-rectangle-in-histogram/
class Solution84 {
	static const int MAXN = 100; //100002;
	typedef long long ll;
	int Log[MAXN];
	ll stable[MAXN][17];
	ll arr[MAXN];
	int n;
public:
	void build() {
		int cnt = -1;
		for (int i = 0; i < n; i++) {
			if (!((i + 1) & i))
				cnt++;
			stable[i][0] = i;
			Log[i + 1] = cnt;
		}
		for (int j = 1; (1 << j) <= n; j++) {
			for (int i = 0; (i + (1 << j)) <= n; i++) {
				int a = stable[i][j - 1];
				int b = stable[i + (1 << (j - 1))][j - 1];
				stable[i][j] = ((arr[a] < arr[b]) ? a : b);
			}
		}
	}

	int getMinIdx(int st, int en) {
		int L = Log[en - st + 1];
		int a = stable[st][L], b = stable[en - (1 << L) + 1][L];
		return ((arr[a] < arr[b]) ? a : b);
	}

	void prepare(vector<int> &heights) {
		n = heights.size();
		for (int i = 0; i < n; ++i)
			arr[i] = heights[i];

		build();
	}

	int largestRectangleArea(vector<int>& heights, int start, int end) {
		if (start > end )
			return 0;

		if (end == start)
			return heights[start];
		
		int min_idx = getMinIdx(start, end);

		int area_with_min = heights[min_idx] * (end - start + 1);
		int left_area = largestRectangleArea(heights, start, min_idx - 1);
		int right_area = largestRectangleArea(heights, min_idx + 1, end); 
		return  max(max(left_area, right_area), area_with_min);
	}
    int largestRectangleArea(vector<int>& heights) {
		prepare(heights);
        return largestRectangleArea(heights, 0, (int) heights.size() - 1);
    }
};

// https://codeforces.com/contest/560/problem/D
string canonical(string str) {
	int n = str.size();

	if (n % 2 == 1)
		return str;
	
	string s1 = str.substr(0, n / 2);
	string s2 = str.substr(n / 2, n / 2);

	s1 = canonical(s1);
	s2 = canonical(s2);

	if (s1 < s2)
		return s1 + s2;

	return s2 + s1;
}

bool isEquivalent(string str1, string str2) {
	return canonical(str1) == canonical(str2);
}


// Definition for singly-linked list.
struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* push_back(ListNode* list, ListNode* other){
	if (!list) 
		return  new ListNode(other->val);

	ListNode *head = list;
	while (head->next) {
		head = head->next;
	}

	head->next = new ListNode(other->val);
	
	return list;
}

// https://leetcode.com/problems/merge-k-sorted-lists/
class Solution23 {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
		int sz = (int) lists.size();
		
		if ( sz == 0)
			return nullptr;

		if (sz == 1) 
			return lists[0];

		ListNode *head1, *head2;

		if (sz == 2) {
			head1 = lists[0];
			head2 = lists[1]; 
		}
		else { // divide it for more than two linkedlists
			vector<ListNode*> lists1(lists.begin(), lists.begin() + sz / 2 + 1);
			vector<ListNode*> lists2(lists.begin() + sz / 2 + 1, lists.end());
			head1 = mergeKLists(lists1);
			head2 = mergeKLists(lists2);
		}

		ListNode* res = nullptr;

		while (head1 || head2) {
			if (!head1) {
				res = push_back(res, head2);
				head2 = head2->next;
			}
			else if (!head2) {
				res = push_back(res, head1);
				head1 = head1->next;
			}
			else if (head1->val < head2->val) {
				res = push_back(res, head1);
				head1 = head1->next;
			}
			else {
				res = push_back(res, head2);
				head2 = head2->next;
			}
		}
		return res;
    }
};

int main()
{
    vector<int> arr = {12, 26, 35, 87, 7, 9, 28};
	print(arr);
	tmp = arr;
	merge_sorted_subarrays(arr, 0, 3, 6);
	print(arr);
	vector<int> lst{ 12, 35, 87, 26, 9, 28, 7 };
	print(lst);
	merge_sort(lst);
	print(lst);
	vector<int>  arr2 = {12, 26, 35, 87, 7, 9, 28};
	quicksort(arr2);
	print(arr2);
	// hw1 p 1
	Solution775 s775;
	vector<int> hw1p1 = {1, 0, 2};
	cout<< s775.isIdealPermutation(hw1p1) << endl;
	hw1p1 = {1, 2, 0}; 
	cout<< s775.isIdealPermutation(hw1p1) << endl;
	hw1p1 = {2,0,1};
	cout<< s775.isIdealPermutation(hw1p1) << endl;

	vector<int>  hw1p2 = {12, 26, 26, 26, 26, 35, 35, 87, 7, 9, 28};
	quicksort2(hw1p2);
	print(hw1p2);

	Solution84 s84;
	vector<int> hw1p4;
	hw1p4 = {2,1,5,6,2,3};

	cout << s84.largestRectangleArea(hw1p4) << endl;

	string hw1p51, hw1p52;
	hw1p51 = "aaba";
	hw1p52 = "abaa";
	cout << isEquivalent(hw1p51, hw1p52) << endl;

	hw1p51 = "aabb";
	hw1p52 = "abab";
	cout << isEquivalent(hw1p51, hw1p52) << endl;

	
    return 0;
}
