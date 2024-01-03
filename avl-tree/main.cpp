#include <iostream>
#include <cassert>
#include <string.h>
#include <stack>
#include <queue>
#include <math.h>
#include <bits/stdc++.h>
#include <utility>
using namespace std;

class AVLTree {
private:
    struct BinaryNode {
        int data { };
        int height { };
        BinaryNode* left { };
        BinaryNode* right { };

        BinaryNode(int data) : data(data) 
        { }
        int ch_height(BinaryNode* node) {
            if (!node)
                return -1;
            return node->height;
        }
        int update_height() {
            return height = 1 + max(ch_height(left), ch_height(right));
        }
        int balance_factor() {
            return ch_height(left) - ch_height(right);
        }
    };

    BinaryNode* root {};

    bool search(int target, BinaryNode* node) {
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
        Q->update_height();
        P->update_height();
        return P;
    }
    BinaryNode* left_rotation(BinaryNode* P)
    {
        cout << "left_rotation " << P->data << "\n";
        BinaryNode* Q = P->right;
        P->right = Q->left;
        Q->left = P;
        P->update_height();
        Q->update_height();
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
        node->update_height();
        
        return balance(node);
    }

    BinaryNode* min_node(BinaryNode* cur) {
        while (cur && cur->left)
            cur = cur->left;
        return cur;
    }
    BinaryNode* delete_node(int target, BinaryNode* node) {
        if (!node)
            return nullptr;
        if (target < node->data)
            node->left = delete_node(target, node->left);
        else if (target > node->data)
            node->right = delete_node(target, node->right);
        else {
            BinaryNode* tmp = node;
            if (!node->left && !node->right)
                node = nullptr;
            else if (!node->right)
                node = node->left;
            else if (!node->left)
                node = node->right;
            else {
                BinaryNode* mn = min_node(node->right);
                node->data = mn->data;
                node->right = delete_node(node->data, node->right);
                tmp = nullptr;
            }
            if (tmp)
                delete tmp;
        }
        if (node) {
            node->update_height();
            node = balance(node);
        }
        return node;
    }
    bool is_bst(BinaryNode* node) {
        bool left_bst = !node->left || node->data > node->left->data && is_bst(node->left);

        if (!left_bst)
            return false;
        
        bool right_bst = !node->right || node->data < node->right->data && is_bst(node->right);

        return right_bst;
    }
    void verify()
    {
        assert(abs(root->balance_factor()) <= 1);
        assert(is_bst(root)); 
    }
	void print_inorder(BinaryNode* node) {
		if(!node)
			return;

		print_inorder(node->left);
		cout << node->data << " ";
		print_inorder(node->right);
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

    void insert_value(vector<int> &vec) {
        for (auto v : vec)
            insert_value(v);
    }

    void delete_value(int target) {
		if (root) {
			root = delete_node(target, root);
			verify();
		}
	}

	bool search(int target) {
		return search(target, root);
	}

	void print_inorder() {
		print_inorder(root);
        cout << endl;
	}

	void level_order_traversal() {
		if (!root)
			return;

		cout << "******************\n";
		queue<BinaryNode*> nodes_queue;
		nodes_queue.push(root);

		int level = 0;
		while (!nodes_queue.empty()) {
			int sz = nodes_queue.size();

			cout << "Level " << level << ": ";
			while (sz--) {
				BinaryNode*cur = nodes_queue.front();
				nodes_queue.pop();

				cout << cur->data << " ";
				if (cur->left)
					nodes_queue.push(cur->left);
				if (cur->right)
					nodes_queue.push(cur->right);
			}
			level++;
			cout << "\n";
		}
	}
    // hw1 p1
    BinaryNode* lower_bound(BinaryNode* node, int target) {
        if (!node)
            return nullptr;

        if (target <= node->data) {
            BinaryNode* ans = lower_bound(node->left, target);
            if (ans)
                return ans;
            return node;
        }
        return lower_bound(node->right, target);
    }
    pair<bool, int> lower_bound(int target) {
        BinaryNode* ans = lower_bound(root, target);
        if (ans) 
            return {true, ans->data};
        return {false, -1};
    }
    // hw1 p2
    BinaryNode* upper_bound(BinaryNode* node, int target) {
        if (!node)
            return nullptr;

        if (target < node->data) {
            BinaryNode* ans = upper_bound(node->left, target);
            if (ans)
                return ans;
            return node;
        }
        return upper_bound(node->right, target);
    }
    pair<bool, int> upper_bound(int target) {
        BinaryNode* ans = upper_bound(root, target);
        if (ans) 
            return {true, ans->data};
        return {false, -1};
    }
    
    int count_inversions(const vector<int> &arr) {

    }
};

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// https://leetcode.com/problems/balance-a-binary-search-tree/
class Solution1382 {
public:
    TreeNode* balanceBST(TreeNode* root) {

    }
};




// https://leetcode.com/problems/balanced-binary-tree/
class Solution110 {
public:
    int get_height(TreeNode* node) {
        if (!node)
            return 0;
        return 1 + max(get_height(node->left), get_height(node->right));
    }
    bool isBalanced(TreeNode* root) {
        if (!root)
            return true;

        int bf = get_height(root->left) - get_height(root->right);
        
        if (abs(bf) > 1)
            return false;

        return isBalanced(root->left) && isBalanced(root->right);
    }
};

int main()
{
    AVLTree avl;
    // avl.insert_value(3); avl.insert_value(5); avl.insert_value(9); 

    // for (int i = 0; i <= 32; i++) {
    //     avl.insert_value(i);
    //     avl.level_order_traversal();
    // }

    vector<int> hw1p1 = {2, 5, 10, 13, 15, 20, 40, 50, 70};
    avl.insert_value(hw1p1);
    avl.print_inorder(); 
    // hw1 p1
    cout << avl.lower_bound(50).second << endl;
    // hw1 p2
    cout << avl.upper_bound(50).second << endl;

    AVLTree hw1p3;

    cout << hw1p3.count_inversions({5,4,3,2,1}) << endl;
    return 0;
}


