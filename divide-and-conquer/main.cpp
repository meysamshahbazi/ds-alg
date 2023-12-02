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

int main()
{
    vector<int> arr = {12, 26, 35, 87, 7, 9, 28};
	print(arr);
	tmp = arr;
	merge_sorted_subarrays(arr, 0, 3, 6);
	print(arr);
	vector<int> lst { 12, 35, 87, 26, 9, 28, 7 };
	print(lst);
	merge_sort(lst);
	print(lst);
    return 0;
}
