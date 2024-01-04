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
        int count { 1 };
        BinaryNode* left { };
        BinaryNode* right { };

        BinaryNode(int data) : data(data) 
        { }
        int ch_height(BinaryNode* node) {
            if (!node)
                return -1;
            return node->height;
        }
        int ch_count(BinaryNode* node) {
            if (!node)
                return 0;
            return node->count;
        }
        int update_height() {
            count = 1 + ch_count(left) + ch_count(right);
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

    int upper_bound_count(int target, BinaryNode* node) {
        if (!node)
            return 0;
        
        if (target < node->data) {
            int sum = 1;
            if (node->right)
                sum += node->right->count;
            return sum + upper_bound_count(target, node->left);
        }
        return upper_bound_count(target, node->right);
        
    }
    int count_inversions(const vector<int> &arr) {
        int sum = 0;
        for (int i = 0; i < arr.size(); i++) {
            insert_value(arr[i]);
            sum += upper_bound_count(arr[i], root);
        }
        return sum;
    }
    int min_nodes_rec(int height) {
        if (height == 0)
            return 1;
        if (height == 1)
            return 2;
         
        return 1 + min_nodes_rec(height - 1) + min_nodes_rec(height - 2);
    }
    int min_nodes_it(int height) {
        if (height == 0)
            return 1;
        if (height == 1)
            return 2;
        
        height--;
        int a = 1;
        int b = 2, c;
        while (height--) 
            c = a + b + 1, a = b, b = c;
        
        return c;
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

class PriorityQueue {
    struct BinaryNode {
        int priority { };
        int height { };
        vector<int> task_ids { };
        BinaryNode* left { };
        BinaryNode* right { };

        BinaryNode(int task_id, int priority) :
                priority(priority) {
            task_ids.push_back(task_id);
        }

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
    bool search(int targrt, BinaryNode* node) {
        if (!node)
            return false;

        if (targrt == node->priority)
            return true;
        
        if (targrt < node->priority)
            return search(targrt, node->left);
        return search(targrt, node->right);
    }

    BinaryNode* right_rotation(BinaryNode* Q) {
        BinaryNode* P = Q->left;
        Q->left = P->right;
        P->right = Q;
        Q->update_height();
        P->update_height();
        return P;
    }
    BinaryNode* left_rotation(BinaryNode* P) {
        BinaryNode* Q = P->right;
        P->right = Q->left;
        Q->left = P;
        P->update_height();
        Q->update_height();
        return Q;
    }
    BinaryNode* balance(BinaryNode*node) {
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
    BinaryNode* insert_node(int task_id, int priority, BinaryNode* node) {
        if (priority < node->priority) {
            if (!node->left)
                node->left = new BinaryNode(task_id, priority);
            else 
                node->left = insert_node(task_id, priority, node->left);
        }
        else if (priority > node->priority) {
            if (!node->right)
                node->right = new BinaryNode(task_id, priority);
            else 
                node->right = insert_node(task_id, priority, node->right);
        }
        else 
            node->task_ids.push_back(task_id);
        node->update_height();
        return balance(node);
    }
    BinaryNode* min_node(BinaryNode* cur) {
        while (cur && cur->left)
            cur = cur->left;
        return cur;
    }
    BinaryNode* max_node(BinaryNode* cur) {
        while (cur && cur->right)
            cur = cur->right;
        return cur;
    }

    BinaryNode* delete_node(int priority, BinaryNode* node) {
        if (!node) 
            return nullptr;

        if (priority < node->priority)
            node->left = delete_node(priority, node->left);
        else if (priority > node->priority)
            node->right = delete_node(priority, node->right);
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
                node->priority = mn->priority;
                node->right = delete_node(node->priority, node->right);
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
public:
    void enqueue(int task_id, int priority) {
        if (!root)
            root = new BinaryNode(task_id, priority);
        else 
            root = insert_node(task_id, priority, root);

    }
    int dequeue() {
        assert(!isEmpty());
        BinaryNode* mx = max_node(root);
        assert(mx->task_ids.size() > 0);
        int ret = mx->task_ids.back();
        mx->task_ids.pop_back();
        if (mx->task_ids.size() == 0)
            root = delete_node(mx->priority, root);
        
        return ret;
    }
    bool isEmpty() {
        return root == nullptr;
    }
};

class AVLDictionary {
    struct BinaryNode {
        string data { };
        bool is_full_word { };
        int height;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(string data, bool is_full_word) :
                data(data), is_full_word(is_full_word) {

        }

        int ch_height(BinaryNode* node) {	// child height
			if (!node)
				return -1;			// -1 for null
			return node->height;	// 0 for leaf
		}
		int update_height() {	// call in end of insert function
			return height = 1 + max(ch_height(left), ch_height(right));
		}
		int balance_factor() {
			return ch_height(left) - ch_height(right);
		}
    };

    BinaryNode *root { };

	///////////////////////////
	BinaryNode* right_rotation(BinaryNode* Q) {
		BinaryNode* P = Q->left;
		Q->left = P->right;
		P->right = Q;
		Q->update_height();
		P->update_height();
		return P;
	}

	BinaryNode* left_rotation(BinaryNode* P) {
		BinaryNode* Q = P->right;
		P->right = Q->left;
		Q->left = P;
		P->update_height();
		Q->update_height();
		return Q;
	}

	BinaryNode* balance(BinaryNode* node) {
		if (node->balance_factor() == 2) { 			// Left
			if (node->left->balance_factor() == -1)	// Left Right?
				node->left = left_rotation(node->left);	// To Left Left

			node = right_rotation(node);	// Balance Left Left
		} else if (node->balance_factor() == -2) {
			if (node->right->balance_factor() == 1)
				node->right = right_rotation(node->right);

			node = left_rotation(node);
		}
		return node;
	}

	// -1 (not exist), 0 exist as prefix, 1 exist as full word
	int search(string target, BinaryNode* node) {
		if(!node)
			return -1;

		if (target == node->data)
			return node->is_full_word;

		if (target < node->data)
			return search(target, node->left);

		return search(target, node->right);
	}

    BinaryNode* insert_node(string target, bool is_full_word, BinaryNode* node) {
		if (target < node->data) {
			if (!node->left)
				node->left = new BinaryNode(target, is_full_word);
			else	// change left. update left as it might be balanced
				node->left = insert_node(target, is_full_word, node->left);
		} else if (target > node->data) {
			if (!node->right)
				node->right = new BinaryNode(target, is_full_word);
			else
				node->right = insert_node(target, is_full_word, node->right);
		}
		else if (is_full_word)	// if existed before but this is full_word, mark it
			node->is_full_word = 1;
		node->update_height();
		return balance(node);
	}

	void insert_value(string target, int is_full_word) {
		if (!root)
			root = new BinaryNode(target, is_full_word);
		else
			root = insert_node(target, is_full_word, root);
	}

public:
    void insert_string(string str) {
        if (str == "")
            return;
        
        string cur = "";
        for (int i = 0; i < str.size(); i++) {
            cur += str[i];
            insert_value(cur, i == (int) str.size() - 1);
        }
    }
    bool word_exist(string str) {
        return search(str, root) == 1;
    }
    bool prefix_exist(string str) {
        return search(str, root) != -1;
    }
};

int main()
{
    AVLTree avl;
    avl.insert_value(3); avl.insert_value(5); avl.insert_value(9); 

    for (int i = 0; i <= 32; i++) {
        avl.insert_value(i);
        avl.level_order_traversal();
    }

    vector<int> hw1p1 = {2, 5, 10, 13, 15, 20, 40, 50, 70};
    avl.insert_value(hw1p1);
    avl.print_inorder(); 
    // hw1 p1
    cout << avl.lower_bound(50).second << endl;
    // hw1 p2
    cout << avl.upper_bound(50).second << endl;
    // hw1 p3
    AVLTree hw1p3;

    cout << hw1p3.count_inversions({5,4,3,2,1}) << endl;
    cout << hw1p3.count_inversions({10,5,8,2,12,6}) << endl;
    cout << endl;
    // hw1 p4
    PriorityQueue tasks;

	tasks.enqueue(1131, 1);
	tasks.enqueue(3111, 3);
	tasks.enqueue(2211, 2);
	tasks.enqueue(3161, 3);
	tasks.enqueue(7761, 7);

	cout << tasks.dequeue() << "\n";	// 7761
	cout << tasks.dequeue() << "\n";	// 3161

	tasks.enqueue(1535, 1);
	tasks.enqueue(2815, 2);
	tasks.enqueue(3845, 3);
	tasks.enqueue(3145, 3);

	// 3145 3845 3111 2815 2211 1535 1131
	while (!tasks.isEmpty())
		cout << tasks.dequeue() << " "<<flush;
    cout << endl<< endl;
    // hw1 p5
    for (int i = 0; i < 10; ++i)
        cout << avl.min_nodes_rec(i) << " ";
    
    cout << endl<< endl;    

    // hw1 p6
    AVLDictionary avld;

	avld.insert_string("abcd");
	avld.insert_string("xyz");

	cout<<avld.word_exist("abcd")<<"\n";	// 1
	cout<<avld.word_exist("ab")<<"\n";		// 0
	cout<<avld.prefix_exist("ab")<<"\n";	// 1

	avld.insert_string("ab");

	cout<<avld.word_exist("ab")<<"\n";		// 1
	cout<<avld.word_exist("cd")<<"\n";		// 0
	cout<<avld.word_exist("abcde")<<"\n";	// 0

    cout << endl<< endl;    

    return 0;
}


