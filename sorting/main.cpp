#include <iostream>
#include <vector>

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
	insertion_sort(v);

	for (int i = 0; i < (int) v.size(); ++i) {
		cout << v[i] << " ";
	}
    cout<<endl;
    return -1;
}


