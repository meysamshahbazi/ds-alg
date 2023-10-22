#include <iostream>
#include <vector>
#include<algorithm>
#include <string>
#include <numeric>

using namespace std;

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

    return 0;
}
