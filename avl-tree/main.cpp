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

    BinaryNode* root {};

    bool search(int target, BinaryNode* node)
    {
        if (!node)
            return false;
        
        if (target == node->data)
            return true;

        if (target < node->data)
            return search(target,node);
        
        return search(target, node);
    }
    BinaryNode* right_rotation(BinaryNode* Q)
    {
        cout << "right_rotation " << Q->data << "\n";
        BinaryNode* P = Q->left;
        Q->left = P->right;
        P->right = Q;
        Q->updata_height();
        P->updata_height();
        return P;
    }
    BinaryNode* left_rotation(BinaryNode* P)
    {
        cout << "left_rotation " << P->data << "\n";
        BinaryNode* Q = P->right;
        P->right = Q->left;
        Q->left = P;
        P->updata_height();
        Q->updata_height();
        return Q;   
    }
    BinaryNode* balance(BinaryNode* node)
    {
        if (node->balance_factor() == 2) {
            if (node->left->balance_factor() == -1)
                node->left = left_rotation(node->left);
            
            node = right_rotation(node);
        }
        else if (node->balance_factor() == -2) {
            if (node->right->balance_factor() == 1)
                node->right = right_rotation(node->right);

            node = left_rotation(node);
        }
        return node;
    }
    BinaryNode* insert_node(int target, BinaryNode* node)
    {
        if(target < node->data) {
            if(!node->left)
                node->left = new BinaryNode(target);
            else 
                node->left = insert_node(target, node->left);
        }
        else if (target > node->data) {
            if(!node->right)
                node->right = new BinaryNode(target);
            else 
                node->right = insert_node(target, node->right);
        }
        node->updata_height();
        return balance(node);
    }
    void verify()
    {
        
    }

public:
    AVLTree()
    {

    }
    void insert_value(int target)
    {
        if(!root)
            root = new BinaryNode(target);
        else 
            root = insert_node(target, root);

        verify();
    }


};

int main()
{
    AVLTree avl;
    return 0;
}


