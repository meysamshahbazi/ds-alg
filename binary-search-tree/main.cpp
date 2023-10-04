#include <iostream>
#include <cassert>
#include <string.h>
#include <stack>
#include <queue>
#include <math.h>
#include <bits/stdc++.h>
#include <utility>
using namespace std;

 class BinarySearchTree {
private:
    int data;
    BinarySearchTree *left {};
    BinarySearchTree *right{};
public:    
    BinarySearchTree() : data(0), left(nullptr), right(nullptr) {}
    BinarySearchTree(int x) : data(x), left(nullptr), right(nullptr) {}
    BinarySearchTree(int x, BinarySearchTree *left, BinarySearchTree *right) : data(x), left(left), right(right) {}

    void print_inorder() 
    {
		if (left)
			left->print_inorder();
		cout << data << " ";
		if (right)
			right->print_inorder();
	}
    bool search(int target)
    {
        if (target == data)
            return true;

        if (target < data)
            return left && left->search(target);

        return right && right->search(target);
    }
 };

int main()
{
    return 0;
}


