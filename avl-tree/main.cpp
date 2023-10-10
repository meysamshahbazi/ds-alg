#include <iostream>
#include <cassert>
#include <string.h>
#include <stack>
#include <queue>
#include <math.h>
#include <bits/stdc++.h>
#include <utility>
using namespace std;

class AVLTree
{
private:
    struct BinaryNode
    {
        int data{};
        int height{};
        BinaryNode* left{};
        BinaryNode* right{};

        BinaryNode(int data) :data(data) 
        {
        }
        int ch_height(BinaryNode* node)
        {
            if(!node)
                return -1;
            return node->height;
        }
        int updata_height()
        {
            return height = 1 + max(ch_height(left), ch_height(right));
        }
        int balance_factor()
        {
            return ch_height(right) - ch_height(left);
        }
    };

    BinaryNode* root;

    // bool search(int target, BinaryNode* node);

    
public:

};

int main()
{
    
    return 0;
}


