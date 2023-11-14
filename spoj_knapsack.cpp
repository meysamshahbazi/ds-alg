// https://www.spoj.com/problems/KNAPSACK/

#include <iostream>
using namespace std;

#include <vector>
int knapsack(int idx, int remain_capacity, vector<int> &sizes, vector<int> &values)
{
	if (remain_capacity <= 0)
		return 0;

	if (idx == (int) sizes.size())
		return 0;

	if (sizes[idx] > remain_capacity) { // dont pick!
		return knapsack(idx + 1, remain_capacity, sizes, values);
	}

	int pick_choice = values[idx] + knapsack(idx + 1, remain_capacity - sizes[idx], sizes, values);
	int leave_choice = knapsack(idx + 1, remain_capacity, sizes, values);

	return max(pick_choice, leave_choice);
}

int main() 
{
	int capacity, N;
	cin >> capacity >> N;
	vector<int> sizes;
	vector<int> values;
	while (N--)
	{
		int s, v;
		cin >> s >> v;

		sizes.push_back(s);
		values.push_back(v);
	}
	
	cout<<knapsack(0, capacity, sizes, values)<<endl;

	return 0;
}

