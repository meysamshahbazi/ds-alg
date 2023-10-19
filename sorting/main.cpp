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
	for (int i = 0; i < (int) v.size(); ++i) {
		cout << v[i] << " ";
	}
    cout<<endl;
    return -1;
}


