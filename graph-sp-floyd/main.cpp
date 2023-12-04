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



