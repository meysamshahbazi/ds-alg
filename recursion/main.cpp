#include<iostream>
#include<cstring>	// memset
#include<vector>
#include <algorithm>
#include<map>
#include <bits/stdc++.h>

using namespace std;

int length_3n_plus_1(int n)
{
    if (n == 1)
		return 1;

    if (n%2 == 0)
        return 1 + length_3n_plus_1(n / 2);
    else  
        return 1 + length_3n_plus_1(3  * n + 1);
}
int my_pow(int value, int p = 2)
{
    if (p == 0)
        return 1;

    return value * my_pow(value, p - 1);
}

int arr_max(int arr[], int len)
{
    if (len == 1)
        return arr[0];
    
    return max(arr[len - 1], arr_max(arr, len - 1));
}

int sum(int arr[], int len)
{
    if (len == 1)
        return arr[0];
    
    return arr[len - 1] + sum(arr, len - 1);
}

double average(int arr[], int len)
{
    if (len == 1)
        return arr[0];
    
    
}

int main()
{
    // hw1 p1
    cout<<length_3n_plus_1(6)<<endl;
    // hw1 p2
    cout<<my_pow(7, 3)<<endl;
    // hw1 p3
    int my_arr[6] = {1,2,11,8,7,9};
    cout<<arr_max(my_arr,6)<<endl;
    // hw1 p4
    int arr2[] = {1, 8, 2, 10, 3};
    cout<<sum(arr2, 5)<<endl;
}
