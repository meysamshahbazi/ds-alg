#include <iostream>
#include <cassert>
#include <string.h>
#include <stack>
#include <queue>
#include <math.h>
#include <bits/stdc++.h>
#include <utility>
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


class BinarySearchTree {
private:
    int data;
    BinarySearchTree *left {};
    BinarySearchTree *right{};
    BinarySearchTree *parent{nullptr};
public:    
    BinarySearchTree() 
    : data(0), left(nullptr), right(nullptr), parent{nullptr} {}
    BinarySearchTree(int x) 
    : data(x), left(nullptr), right(nullptr), parent{nullptr} {}
    BinarySearchTree(int x, BinarySearchTree *left, BinarySearchTree *right) 
    : data(x), left(left), right(right), parent{nullptr} {}

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
    // hw1 p1
    bool search_iterative(int target)
    {
        BinarySearchTree* cur = this;
        while (cur) {
            if (target == cur->data)
                return true;
            
            if (target < cur->data)
                cur = cur->left;
            else 
                cur = cur->right;
        }
        return false;
    }
    void insert(int target)
    {
        if (target < data) {
            if (!left)
                left = new BinarySearchTree(target);
            else 
                left->insert(target);
        }
        else if (target > data) {
            if (!right)
                right =  new BinarySearchTree(target);
            else 
                right->insert(target);
        }
        // otherwise target == data and already exist!
    }
    void insert2(int target) // with parent!
    {
        if (target < data) {
            if(!left){
                left = new BinarySearchTree(target);
                left->parent = this;
            }
            else 
                left->insert2(target);
        }
        else if (target > data) {
            if (!right){
                right =  new BinarySearchTree(target);
                right->parent = this;
            }
            else 
                right->insert2(target);
        }
        // otherwise target == data and already exist!
    }
    // hw1 p2
    bool is_bst()
    {
        if (!left && !right)
            return true;

        if (!left)  
            return (data < right->data) && right->is_bst();
        
        if (!right)
            return (data > left->data) && left->is_bst();

        if(data > right->data || data < left->data)
            return false;

        return left->is_bst() && right->is_bst();
    }
    // hw1 p3
    static BinarySearchTree* build_balanced_bst_tree(vector<int> &values)
    {
        vector<int> values_left;
        vector<int> values_right;

        for(int i=0; i<values.size()/2; ++i)
            values_left.push_back(values[i]);
        
        for(int i=values.size()/2+1; i<values.size(); ++i)
            values_right.push_back(values[i]);

        BinarySearchTree* bst = new BinarySearchTree(values[values.size()/2]);
        
        if(values_left.size())
            bst->left = build_balanced_bst_tree(values_left);
        
        if(values_right.size())
            bst->right = build_balanced_bst_tree(values_right);
        
        return bst;
    }
    int total_nodes(BinarySearchTree *node)
    {
        if(!node)
            return 0;
        return 1 + total_nodes(node->left) + total_nodes(node->right);
    }
    int total_nodes() {
        return total_nodes(this);
    }
    // hw1 p4
    int kth_smallest(int k)
    {
        int total_nodes_on_left = total_nodes(left);
        int total_nodes_on_right = total_nodes(right);
        int total_nodes = total_nodes_on_left+total_nodes_on_right+1;
        if(k <= total_nodes_on_left)
            return left->kth_smallest(k);
        if (k == total_nodes_on_left+1)
            return data;
        if (k<=total_nodes)
            return right->kth_smallest(k-total_nodes_on_left-1);
        return -1234;
    }
    // hw1 p5
    int lowest_common_ancestor(int n1, int n2)
    {
        if (n1 <= data && n2 >=data)
            return data;
        if (n1 < data && n2 < data)
            return left->lowest_common_ancestor(n1, n2);
        if (n1 > data && n2 > data)
            return right->lowest_common_ancestor(n1, n2);
    }
    // ----------------------------------------
    int min_value()
    {
        BinarySearchTree* cur = this;
        while (cur && cur->left)
            cur = cur->left;
        return cur->data;
    }
    bool find_chain(vector<BinarySearchTree*> &ancestors, int target)
    {
        ancestors.push_back(this);
        
        if (target == data)
            return true;
        
        if (target < data)
            return left && left->find_chain(ancestors, target);
        
        return right && right->find_chain(ancestors, target);
    }
    BinarySearchTree* get_next(vector<BinarySearchTree*> &ancestors)
    {
        if (ancestors.size() == 0)
            return nullptr;
        BinarySearchTree* node = ancestors.back();
        ancestors.pop_back();
        return node;
    }
    pair<bool, int> successor(int target)
    {
        vector<BinarySearchTree*> ancestors;

        if (!find_chain(ancestors, target))
            return make_pair(false,-1);

        BinarySearchTree* child = get_next(ancestors);

        if (child->right)
            return make_pair(true, child->right->min_value());

        BinarySearchTree* parent = get_next(ancestors);

        while (parent && parent->right == child) {
            child = parent;
            parent = get_next(ancestors);
        }

        if (parent)
            return make_pair(true, parent->data);
        
        return make_pair(false, -1);
    }
    BinarySearchTree* find_Node(int target)
    {
        if(target == data)
            return this;
        if (target < data){
            if (left)
                return left->find_Node(target);
            else 
                return nullptr;
        }
        if(!right)
            return nullptr;
        return right->find_Node(target);
    }
    // hw2 p1
    pair<bool, int> successor2(int target)
    {
        BinarySearchTree* cur_child = find_Node(target);
        
        if(!cur_child)
            return make_pair(false,-1);
            
        BinarySearchTree* cur_parent = cur_child->parent;
        
        if (cur_child->right){
            return make_pair(true, cur_child->right->min_value());
        }

        while (cur_parent && cur_parent->right == cur_child ) {
            cur_child = cur_parent;
            cur_parent = cur_parent->parent;
        }
        
        if (cur_parent)
            return make_pair(true, cur_parent->data);
        
        return make_pair(false, -1);
    }
    // hw2 p2
    void queries_of_ancestors(deque<int> &q, vector<int> &answer, vector<int> &traversal) {
        if (q.empty())
            return;

        if (left && q.front() < data) {
            left->queries_of_ancestors(q, answer, traversal);

            if (q.empty())
                return;
        }

        if (!traversal.empty() && traversal.back() == q.front()) {
            answer.push_back(data);
            q.pop_front();

            if (q.empty())
                return;
        }
        traversal.push_back(data);

        if (right && q.front() >= data) 
            right->queries_of_ancestors(q, answer, traversal);
    }
    // hw2 p3
    // https://www.geeksforgeeks.org/check-if-each-internal-node-of-a-bst-has-exactly-one-child/
    bool is_degenerate(vector<int> &preorder) {
        if (preorder.size() <=  2)
            return true;

        int mn = 1, mx = 1000;

        for (int i = 1; i < (int) preorder.size(); i++)  {
            if (preorder[i] < mn || preorder[i] > mx)
                return false;
            if (preorder[i] > preorder[i - 1])
                mn = preorder[i - 1] + 1;
            else 
                mx = preorder[i - 1] - 1;
        }
        return true;
    }
    bool is_degenerate1(vector<int> &preorder)
    {
        vector<BinarySearchTree*> bst_vec;

        BinarySearchTree* parent = new BinarySearchTree(preorder[0]);
        BinarySearchTree* child = new BinarySearchTree(preorder[1]);

        if (preorder[1] > preorder[0])
            parent->right = new BinarySearchTree(preorder[1]);
        else 
            parent->left = new BinarySearchTree(preorder[1]);

        bst_vec.push_back(parent);
        bst_vec.push_back(child);

        for (int i = 2; i < preorder.size(); i++) { 
            if (bst_vec[i - 2]->left && preorder[i] > bst_vec[i - 2]->data) 
                    return false;
            if (bst_vec[i - 2]->right && preorder[i] < bst_vec[i - 2]->data) 
                return false;
    
            BinarySearchTree* child = new BinarySearchTree(preorder[i]);
            if (preorder[i] > bst_vec[i-1]->data)             
                bst_vec[i-1]->right = child;
            else 
                bst_vec[i-1]->left = child;
            bst_vec.push_back(child);
        }
        return true;
    }
    // hw3 p1
    BinarySearchTree(deque<int> &preorder, int start = 0, int end = -1) {
		if (end == -1)
			end = (int) preorder.size() - 1;

		// next preorder is the current root
		data = preorder[start];

		for (int split = start+1; split <= end+1; ++split) {
			if (split == end+1 || preorder[split] > data) {
				if (start+1 <= split-1)	// there is a left tree
					left = new BinarySearchTree(preorder, start+1, split - 1);
				if (split <= end)
					right = new BinarySearchTree(preorder, split, end);
				break;
			}
		}
	}
    // hw3 p2
    vector<int> next_greater_idx(vector<int>& vec) {   
        stack<int> greaters_index;
        vector<int> answer(vec.size());
        for (int i = (int) vec.size() - 1; i >= 0; i--) {      
            while (!greaters_index.empty() && vec[i] >= vec[greaters_index.top()]) {
                greaters_index.pop();
            }

            if (greaters_index.empty())
                answer[i] = 0;
            else 
                answer[i] = greaters_index.top() - i;

            greaters_index.push(i);
        }
        return answer;
    }
    BinarySearchTree(deque<int> &preorder, const vector<int> &next_greater, int start = 0, int end = -1) {
		if (end == -1)
			end = (int) preorder.size() - 1;

		// next preorder is the current root
		data = preorder[start];

		int split = next_greater[start];

		if(split > end)	// next is after our end OR doesn't exist, reset our split end
			split = end + 1;

		if (start + 1 <= split - 1)	// there is a left tree
			left = new BinarySearchTree(preorder, next_greater, start + 1, split - 1);
		if (split <= end)
			right = new BinarySearchTree(preorder, next_greater, split, end);
	}

    // hw3 p3
    bool next_between(deque<int> &preorder, int min, int max) {
		if (preorder.empty())
			return false;
		return min < preorder[0] && preorder[0] < max;
	}
    BinarySearchTree(deque<int> &preorder, int min = 0, int max = 1001)  {
        if (preorder.empty())
            return;

        data = preorder.front();
        preorder.pop_front();
        if (next_between(preorder, min, data))
            left = new BinarySearchTree(preorder, min, data);
        if (next_between(preorder, data, max))
            right = new BinarySearchTree(preorder, data, max);
    }
    // hw3 p4
    BinarySearchTree(deque<int> level_order) {
        
    }

    BinarySearchTree* buildFromLevelOrder(deque<int> level_order) {
        if (level_order.empty())
            return nullptr;
        
        BinarySearchTree* root = new BinarySearchTree(level_order.front());
        
        while (!level_order.empty()) {
            
        }
    }
    void BinarySearchTree1(deque<int> &preorder) { // O(n^2) tree from preorder+inorder
        deque<int> inorder = preorder;
        sort(inorder.begin(), inorder.end());
        BinarySearchTree * thiz =  generateNode(preorder, inorder);
        this->left = thiz->left;
        this->right = thiz->right;
        this->data = thiz->data;
    }
    BinarySearchTree* generateNode(deque<int> &preorder, deque<int> &inorder)
    {
        if (preorder.size() == 0) 
            return nullptr;

        int value = preorder.front();
        preorder.pop_front();
        BinarySearchTree* node = new BinarySearchTree(value);
        deque<int> left_inorder;
        deque<int> right_inorder;
        deque<int> left_preorder;
        deque<int> right_preorder;
        while (inorder.front() != value) {
            left_inorder.push_back(inorder.front());
            left_preorder.push_back(preorder.front());
            inorder.pop_front();
            preorder.pop_front();
        }

        while (inorder.back() != value) {
            right_inorder.push_front(inorder.back());
            right_preorder.push_front(preorder.back());
            inorder.pop_back();
            preorder.pop_back();
        }
        inorder.pop_back();
        assert(inorder.empty());
        node->left = generateNode(left_preorder, left_inorder);
        node->right = generateNode(right_preorder, right_inorder);
        
        return node;
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

// https://leetcode.com/problems/validate-binary-search-tree/
class Solution98 {
public:
    bool isBst(TreeNode* node, int mn = INT32_MIN, int mx = INT32_MAX) {
        bool status = mn < node->val && node->val < mx;
        if (!status)
            return false;

        status = !node->left || isBst(node->left, mn, node->val);
        
        if (!status)
            return false;

        return !node->right || isBst(node->right, node->val, mx);
    }
    bool isValidBST(TreeNode* root) {
        return isBst(root);
    }
};

// https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
class Solution108 {
public:
    TreeNode* build_balanced_bst_tree(vector<int> &values, int start = 0, int end = -10) {
        if (end == -10)
            end = (int) values.size() - 1;

        if (start > end)
            return nullptr;

        int mid = (start + end) / 2;
        TreeNode *left = build_balanced_bst_tree(values, start, mid - 1);
        TreeNode *right = build_balanced_bst_tree(values, mid + 1, end);
        TreeNode *root = new TreeNode(values[mid], left, right);

        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return build_balanced_bst_tree(nums);
    }
};

// https://leetcode.com/problems/find-mode-in-binary-search-tree/
class Solution501 {
public:
    vector<int> findMode(TreeNode* root) {

    }
};

// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
class Solution235 {
public:
    TreeNode* lca(TreeNode* root, int m, int n) {
        if (root->val == m || root->val == n)
            return root;

        if (root->val > m && root->val < n)
            return root;
        
        if (m > root->val)
            return lca(root->right, m, n);
        return lca(root->left, m, n);
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int m = min(p->val, q->val);
        int n = max(p->val, q->val);
        return lca(root, m, n);
    }
};

// https://leetcode.com/problems/kth-smallest-element-in-a-bst/
class Solution230_1 {
        vector<int> nums;
        int k;
public:
    void traverse(TreeNode* node) {
        if (!node)
            return;

        if (nums.size() > k)
            return;
            
        traverse(node->left);
        nums.push_back(node->val);
        traverse(node->right);
    }
    int kthSmallest(TreeNode* root, int k) {
        this->k = k;
        traverse(root);
        return nums[k-1];
    }
};

class Solution230 {
        int k;
        int cnt = 0;
        int num;
public:
    void traverse(TreeNode* node) {
        if (!node)
            return;
        
        if (cnt > k)
            return;
            
        traverse(node->left);
        cnt++;
        if (cnt == k)
            num = node->val;
        traverse(node->right);
    }
    int kthSmallest(TreeNode* root, int k) {
        this->k = k;
        traverse(root);
        return num;
    }
};

// https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/
class Solution1008 {
public:
    bool next_between(deque<int> &preorder, int min, int max) {
		if (preorder.empty())
			return false;
		return min < preorder[0] && preorder[0] < max;
	}

    TreeNode* bstFromPreorder(deque<int>& preorder, int mn, int mx) {
        int value = preorder.front();
        TreeNode* root = new TreeNode(value);
        preorder.pop_front();

        if (next_between(preorder, mn, value))
            root->left = bstFromPreorder(preorder, mn, value);
        if (next_between(preorder, value, mx))
            root->right = bstFromPreorder(preorder, value, mx);
        return root;
    }

    TreeNode* bstFromPreorder(vector<int>& preorder) {
        deque<int> dq;
        for (auto p : preorder)
            dq.push_back(p);

        return bstFromPreorder(dq, 0, 1001);
    }
};

class Solution1008_3 {
    vector<int> next_greaters;
public:
    void next_greater_idx(vector<int>& vec) {   
        stack<int> greaters_index;
        next_greaters = vector<int>(vec.size());
        for (int i = (int) vec.size() - 1; i >= 0; i--) {      
            while (!greaters_index.empty() && vec[i] >= vec[greaters_index.top()]) {
                greaters_index.pop();
            }

            if (greaters_index.empty())
                next_greaters[i] = -1;
            else 
                next_greaters[i] = greaters_index.top();

            greaters_index.push(i);
        }
    }
    TreeNode* bstFromPreorder(vector<int>& preorder, int start, int end) {
        if (end == -1)
            end = (int) preorder.size() - 1;
        
        TreeNode* root = new TreeNode(preorder[start]);
        
        int split = next_greaters[start];
        
        if (split == -1 && start + 1 <= end)
            root->left = bstFromPreorder(preorder, start + 1, end);
        if (split != -1 && start + 1 <= split - 1)
            root->left = bstFromPreorder(preorder, start + 1, split - 1);
        if (split != -1 && split <= end)
            root->right= bstFromPreorder(preorder, split, end);
        
        return root;
    }
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        next_greater_idx(preorder);
        return bstFromPreorder(preorder, 0,  -1);
    }
};

class Solution1008_2 {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder, int start, int end) {
        TreeNode* root = new TreeNode(preorder[start]);

        int split = start + 1;
        for (int split = start + 1; split <= end + 1; split++) {
            if (split == end + 1 || preorder[split] > preorder[start]) {
                if (start + 1 <= split - 1)
                    root->left = bstFromPreorder(preorder, start + 1, split - 1);
                if (split <= end)
                    root->right= bstFromPreorder(preorder, split, end);
                break;
            }
        }
        return root;
    }
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int end = (int) preorder.size() - 1;
        return bstFromPreorder(preorder, 0, end);
    }
};

class Solution1008_1 {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        vector<int> inorder = preorder;
        sort(inorder.begin(), inorder.end());
        deque<int> preorder_dq, inorder_dq;
        for (int i = 0; i < (int) inorder.size(); i++) {
            preorder_dq.push_back(preorder[i]);
            inorder_dq.push_back(inorder[i]);
        }
        return generateNode(preorder_dq, inorder_dq);
    }
    TreeNode* generateNode(deque<int> &preorder, deque<int> &inorder)
    {
        if(preorder.size() == 0) 
            return nullptr;

        int value = preorder.front();
        preorder.pop_front();
        TreeNode* node = new TreeNode(value);
        deque<int> left_inorder;
        deque<int> right_inorder;
        deque<int> left_preorder;
        deque<int> right_preorder;
        while (inorder.front() != value) {
            left_inorder.push_back(inorder.front());
            left_preorder.push_back(preorder.front());
            inorder.pop_front();
            preorder.pop_front();
        }

        while (inorder.back() != value) {
            right_inorder.push_front(inorder.back());
            right_preorder.push_front(preorder.back());
            inorder.pop_back();
            preorder.pop_back();
        }
        inorder.pop_back();
        
        node->left = generateNode(left_preorder, left_inorder);
        node->right = generateNode(right_preorder, right_inorder);
        
        return node;
    }
};

// https://leetcode.com/problems/recover-binary-search-tree/

// https://leetcode.com/problems/balance-a-binary-search-tree/



int main()
{
    BinarySearchTree tree(50);
	tree.insert(20);
	tree.insert(45);
	tree.insert(70);
	tree.insert(73);
	tree.insert(35);
	tree.insert(15);
	tree.insert(60);

	tree.print_inorder(); cout<<endl;
    // hw1 p1
    cout<<tree.search(60)<<endl;
    cout<<tree.search_iterative(60)<<endl;

    cout<<tree.search(100)<<endl;
    cout<<tree.search_iterative(100)<<endl;
    // hw1 p2
    cout<<tree.is_bst()<<endl;
    // hw1 p3
    vector<int> values = {0,1,2,3,4,5,6,7,8,9};
    BinarySearchTree* tree2 = BinarySearchTree::build_balanced_bst_tree(values);
    tree2->print_inorder(); cout<<"\n";
    // hw1 p4
    tree.print_inorder(); cout<<endl;
    cout<<tree.kth_smallest(1)<<endl;
    cout<<tree.kth_smallest(2)<<endl;
    cout<<tree.kth_smallest(3)<<endl;
    cout<<tree.kth_smallest(4)<<endl;
    cout<<tree.kth_smallest(5)<<endl;
    cout<<tree.kth_smallest(6)<<endl;
    cout<<tree.kth_smallest(7)<<endl;
    cout<<tree.kth_smallest(8)<<endl;
    cout<<tree.kth_smallest(9)<<endl;
    // hw1 p5
    BinarySearchTree tree3(50);
	tree3.insert(20);
    tree3.insert(60);
    tree3.insert(15);
    tree3.insert(45);
    tree3.insert(58);
    tree3.insert(70);
    tree3.insert(16);
    tree3.insert(35);
    tree3.insert(36);
    tree3.insert(73);
    tree3.insert(76);
    cout<<tree.lowest_common_ancestor(45,36)<<endl;
    tree.print_inorder(); cout<<endl;
    pair<bool, int> suc_pair =  tree.successor(35);
    cout<<suc_pair.second<<endl;
    // hw2 p1
    BinarySearchTree tree4(50);
	tree4.insert2(20);
	tree4.insert2(45);
	tree4.insert2(70);
	tree4.insert2(73);
	tree4.insert2(35);
	tree4.insert2(15);
	tree4.insert2(60);
    tree4.print_inorder(); cout<<endl;
    // hw2 p1
    pair<bool, int> suc_pair2 =  tree4.successor2(35);
    cout<<suc_pair2.second<<endl;

    // hw2 p3
    cout << "hw2 p3--------------\n";
    vector<int> preorder = {25, 8, 11, 13, 12};
    cout<<tree.is_degenerate(preorder)<<endl;
    preorder = {100, 70, 101};
    cout<<tree.is_degenerate(preorder)<<endl;
    preorder = {100, 70, 60, 75};
    cout<<tree.is_degenerate(preorder)<<endl;
    preorder = {100, 70, 60, 65};
    cout<<tree.is_degenerate(preorder)<<endl;
    preorder = {9, 8, 7, 6, 5, 4, 3};
    cout<<tree.is_degenerate(preorder)<<endl;
    preorder = {500, 400, 300, 200 , 250 , 275, 260};
    cout<<tree.is_degenerate(preorder)<<endl;
    preorder = {500, 400, 300, 200 , 250 , 275, 260, 280};
    cout<<tree.is_degenerate(preorder)<<endl;
    //
    cout << "--------------------\n";
    // vector<int> v1008 = {8,5,1,7,10,12};
    vector<int> v1008 = {4, 2};
    Solution1008 s1008;
    auto n1008 = s1008.bstFromPreorder(v1008);

    return 0;
}


