

#include <iostream>
#include <vector>
#include <algorithm>	// fill
using namespace std;

typedef long long ll;
vector<ll> memory;

ll fib(int n) {
	if (n <= 1)
		return 1;

	if (memory[n] != -1)
		return memory[n];
	return memory[n] = fib(n - 1) + fib(n - 2);
}
int main() {
	int n = 80;
	memory.resize(n + 1);
	fill(memory.begin(), memory.end(), -1);

	cout<<fib(80)<<"\n";	// 37889062373143906

	return 0;
}

