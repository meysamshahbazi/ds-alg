

#include <iostream>
#include <vector>
#include <algorithm>	// fill
using namespace std;

typedef long long ll;
vector<ll> memory;

ll fib1(int n) {
	if (n <= 1)
		return 1;

	if (memory[n] != -1)
		return memory[n];

	return memory[n] = fib1(n - 1) + fib1(n - 2);
}

ll fib(int n) {
	if (n <= 1)
		return 1;

	ll &ret = memory[n];
	
	if (ret != -1)
		return ret;
	
	return ret = fib(n - 1) + fib(n - 2);
}

void fib_tabulation() {
	const int MAX {80 + 1};
	ll fib[MAX] {1, 1};

	for (int i = 2; i < MAX; ++i)
		fib[i] = fib[i - 1] + fib[i - 2];

	cout << "Tabulation: " << fib[80] << endl;
}
int main() {
	int n = 80;
	memory.resize(n + 1);
	fill(memory.begin(), memory.end(), -1);

	cout<<fib(80)<<"\n";
	fib_tabulation();
	return 0;
}

