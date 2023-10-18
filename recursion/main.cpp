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

    return (double) arr[len-1]/len + average(arr, len-1)*(len-1.0f)/len;
}

void array_increment(int arr[], int len)
{
    if (len == 1)
        return;

    arr[len - 1] += len - 1;
    array_increment(arr, len - 1);
}

void accumulate_arr(int arr[], int len)
{
    if (len == 1)
        return;
    
    accumulate_arr(arr, len - 1);
    arr[len - 1] += arr[len -2];
}

void left_max(int arr[], int len)
{
    if (len == 1)
        return;

    left_max(arr, len - 1);
    arr[len - 1] = max(arr[len - 1], arr[len - 2]);
}

void right_max(int arr[], int len, int start_position = 0)
{
    if (start_position == len - 1)
        return;
    
    right_max(arr, len, start_position+1);
    arr[start_position] = max(arr[start_position], arr[start_position + 1]);
}

int suffix_sum(int arr[], int len, int N)
{
    if (N == 1)
        return arr[len - 1];

    return arr[len-1] + suffix_sum(arr, len - 1, N - 1);
}

int prefix_sum(int arr[], int len, int N, int start_pos = 0)
{
    if (N == 1)
        return arr[start_pos];
    
    return arr[start_pos] + prefix_sum(arr, len - 1, N - 1, start_pos + 1);
}
bool is_palindrome(int arr[], int len, int start_pos = 0)
{
    if (len == 1)
        return true;
    if (len == 2)
        return arr[start_pos] == arr[start_pos + 1];
    if (arr[start_pos] != arr[start_pos + len - 1])
        return false;

    return is_palindrome(arr, len - 2, start_pos + 1);
}

bool is_prefix(string main, string prefix, int start_pos = 0)
{
    if ((int) prefix.size() - 1 < start_pos)
        return true;

    if(main[start_pos] != prefix[start_pos])
        return false;
    
    return is_prefix(main, prefix, start_pos + 1);
}
void do_something1(int n) {	// print number digit by digit reversed
	if (n) {
		cout << n % 10;
		do_something1(n / 10);
	}
}

void do_something2(int n) {
	if (n) {
		do_something2(n / 10);
		cout << n % 10;
	}
}

bool is_prime(int num)
{
    for (int i = 2; i <= sqrt(num); i++)
        if (num % i == 0)
            return false;

    return true;
}

int count_primes(int start, int end)
{
    if (end == start)
        return 0;

    if (is_prime(end))
        return 1 + count_primes(start, end - 1);
    
    return count_primes(start, end - 1);
}

int path_sum(int grid[100][100], int row, int col, int ROWS, int COLS)
{
    if (row == ROWS - 1 && col == COLS - 1)
        return grid[row][col];
    
    if ( row == ROWS - 1)
        return grid[row][col] + path_sum(grid, row, col + 1, ROWS, COLS);
    
    if ( col == COLS - 1)
        return grid[row][col] + path_sum(grid, row + 1, col, ROWS, COLS);


    if (grid[row + 1][col] > grid[row][col + 1] && grid[row + 1][col] > grid[row + 1][col + 1])
        return grid[row][col] + path_sum(grid, row + 1, col, ROWS, COLS);

    if (grid[row][col + 1] > grid[row + 1][col] && grid[row][col + 1] > grid[row + 1][col + 1])
        return grid[row][col] + path_sum(grid, row, col + 1, ROWS, COLS);

    return grid[row][col] + path_sum(grid, row + 1, col + 1, ROWS, COLS);
}

int fibonacci(int n)
{
    if (n == 0 || n == 1)
        return 1;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    // hw1 p1
    cout<<length_3n_plus_1(6)<<endl;
    // hw1 p2
    cout<<my_pow(7, 3)<<endl;
    // hw1 p3
    int my_arr[6] = {1,2,11,8,7,9};
    cout<<arr_max(my_arr, 6)<<endl;
    // hw1 p4
    int arr2[] = {1, 8, 2, 10, 3};
    cout<<sum(arr2, 5)<<endl;
    // p5
    cout<<average(arr2, 5)<<endl;
    // p6
    array_increment(arr2, 5);
    for(int i = 0; i < 5; i++)
        cout<<arr2[i]<<", ";
    cout<<endl;

    // hw1 p7 
    accumulate_arr(arr2, 5);
    for(int i = 0; i < 5; i++)
        cout<<arr2[i]<<", ";
    cout<<endl;

    // hw1 p8
    int arr3[6] = {1,3,5,7,4,2};
    left_max(arr3, 6);
    for(int i = 0; i < 6; i++)
        cout<<arr3[i]<<", ";
    cout<<endl;

    // hw1 p9
    int arr4[6] = {1,3,5,7,4,2};
    right_max(arr4, 6);
    for(int i = 0; i < 6; i++)
        cout<<arr4[i]<<", ";
    cout<<endl;
    // hw1 p10
    int arr10[] = {1, 3, 4, 6, 7};
    cout<<suffix_sum(arr10, 5, 3)<<endl;
    // p11
    cout<<prefix_sum(arr10, 5, 3)<<endl;
    // p12
    int arr12[] = { 1, 8, 2, 8, 1 };
    cout<<is_palindrome(arr12,5)<<endl;
    // p13
    cout<<"abcd: "<<is_prefix("abcdefgh", "abcd")<<endl;
    cout<<": "<<is_prefix("abcdefgh", "")<<endl;
    cout<<"abd: "<<is_prefix("abcdefgh", "abd")<<endl;
    // p14 wasnt code practice!
    do_something1(123456);
	cout << "\n";
	do_something2(123456);
    cout << "\n";
    // p15
    cout<<count_primes(10,20)<<endl;
    // p16
    int grid[100][100];
    grid[0][0] = 1;grid[0][1] = 7;grid[0][2] = 8;
    grid[1][0] = 2;grid[1][1] = 10;grid[1][2] = 11;
    grid[2][0] = 20;grid[2][1] = 5;grid[2][2] = 9;
    cout<<path_sum(grid, 0, 0, 3, 3)<<endl;
    // p17
    for (int i = 0; i < 20; i++)
        cout<<fibonacci(i)<<", ";
    cout<<endl;
    return -1;
}
