#include <iostream>
#include <vector>
#include<algorithm>

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
    vector<int> v = read_vector();
	// insertion_sort(v);
    selection_sort(v);
    count_sort(v);
	for (int i = 0; i < (int) v.size(); ++i) {
		cout << v[i] << " ";
	}
    cout<<endl;
    return -1;
}


