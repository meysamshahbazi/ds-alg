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
struct Node
{
    T data{};
    Node<T>* left{nullptr};
    Node<T>* right{nullptr};
    Node(T data): data{data} 
    {
    }
};

void print_inorder(Node<char>* current)
{
    if(!current)
        return;

    print_inorder(current->left);
    cout<<current->data<<" ";
    print_inorder(current->right);
}

void print_postorder(Node<char> *current)
{
    if(!current)
        return;
    print_postorder(current->left);
    print_postorder(current->right);
    cout << current->data << " ";
}

void clear(Node<char>* current)
{
    if (!current)
        return;

    clear(current->left);
    current->left = nullptr;
    clear(current->right);
    current->right = nullptr;
    delete current;
}

template <class T>
class BinaryTree
{

public:
    Node<T>* root{};
    BinaryTree(T root_value)
    {
        root = new Node<T>(root_value);
    }
    // hw2 p5
    BinaryTree(string postfix)
    {
        stack<Node<char>*> stk;
        for(char c:postfix){
            Node<char>* node = new Node<char>(c);
            // if(stk.size()==2){
            if(!isdigit(c)){
                node->right = stk.top();
                stk.pop();
                node->left = stk.top();
                stk.pop();
            }
            stk.push(node);
        }
        root = stk.top();
    }
    // hw4 p1
    BinaryTree(deque<int> &preorder, deque<int> &inorder)
    {
        root = generateNode(preorder, inorder);
    }
    Node<T>* generateNode(deque<int> &preorder, deque<int> &inorder)
    {
        if(preorder.size() == 0) 
            return nullptr;

        T value = preorder.front();
        preorder.pop_front();
        Node<T>* node = new Node<T>(value);
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
    // HW4 p2
    BinaryTree(queue<pair<int, int>> &preorder_queue)
    {
        root = generateNode(preorder_queue);
    }
    Node<T>* generateNode(queue<pair<int, int>> &preorder_queue)
    {
        if (preorder_queue.empty())
            return nullptr;
        pair<int,int> top_pair = preorder_queue.front();
        preorder_queue.pop();
        Node<T>* node = new Node<T>(top_pair.first);

        if (top_pair.second)
            return node;
        
        node->left = generateNode(preorder_queue);
        node->right = generateNode(preorder_queue);

        return node;
    }

    ~BinaryTree()
    {
        clear();
    }
    void clear()
    {
        clear(root);
    }
    // hw2 p1
    void clear(Node<T>* current)
    {
        if(!current)
            return;

        clear(current->left);
        current->left = nullptr;
        clear(current->right);
        current->right = nullptr;
        delete current;
        current = nullptr;
    }
    // hw2 p2
    void print_inorder_iterative() // without recursion
    {
        stack<pair<Node<T>*, bool> > nodes;
        nodes.push(make_pair(root,false));

        while (!nodes.empty()) {
            Node<T>* cur = nodes.top().first;
            bool is_done = nodes.top().second;
            nodes.pop();

            if (is_done)
                cout << cur->data << " ";
            else {
                if (cur->right) 
                    nodes.push(make_pair(cur->right, false));

                nodes.push(make_pair(cur, true));

                if (cur->left)
                    nodes.push(make_pair(cur->left,false));
            }
        }
        cout << "\n";

    }
    string parenthesize()
    {
        return parenthesize(root);
    }
    string parenthesize(Node<T>* node)
    {
        string repr = "(" + to_string(node->data);
        
        if (node->left)
            repr += parenthesize(node->left);
        else 
            repr += "()";
        
        if (node->right)
            repr += parenthesize(node->right);
        else 
            repr += "()";

        repr += ")";

        return repr;
    }
    // hw5 p1
    bool is_symmetric() {
        return is_mirror(root->left,root->right);
    }
    // https://leetcode.com/problems/symmetric-tree/
    bool is_mirror(Node<T>* first,Node<T>* second)
    {
        if(!first && !second)
            return true;
        if( (!first && second) || (first && !second))
            return false;
        if (first->data != second->data)
            return false;
        
        return is_mirror(first->left,second->right) && is_mirror(first->right,second->left);
    }
    // hw5 p2 
    bool is_flip_equiv(BinaryTree<T>* other)
    {
        return flipEquiv(this->root,other->root);
    }
    // https://leetcode.com/problems/flip-equivalent-binary-trees/
    bool flipEquiv(Node<T>* root1, Node<T>* root2)
    {
         if( !root1 && !root2)
            return true;

        if( (!root1 && root2) || (root1 && !root2))
            return false;

        if(root1->data != root2->data)
            return false;

        return  ( flipEquiv(root1->left,root2->left) && flipEquiv(root1->right,root2->right) ) ||
                ( flipEquiv(root1->left,root2->right) && flipEquiv(root1->right,root2->left) );
    }
    //hw 5 p3 is donde with Solution652!
    string parenthesize_canonical()
    {
        return parenthesize_canonical(root);
    }

    string parenthesize_canonical(Node<T>* node)
    {
        string repr = "(" + to_string(node->data);
        vector<string> v;

        if(node->left)
            v.push_back(parenthesize(node->left));
        else 
            v.push_back("()");
        
        if (node->right)
            v.push_back(parenthesize(node->right));
        else 
            v.push_back("()");

        sort(v.begin(),v.end());
        
        for (auto &s:v)
            repr += s;

        repr += ")";
        return repr;
    }

    void print_preorder_complete()
    {
        print_preorder_complete(root);
        cout<<"\n";
    }
    void print_preorder_complete(Node<T>* node)
    {
        cout<<node->data<<" ";
        if(node->left)
            print_preorder_complete(node->left);
        else 
            cout<<"-1 ";
        
        if(node->right)
            print_preorder_complete(node->right);
        else 
            cout<<"-1 ";
    }
    // hw2 p3
    void traverse_left_boundry()
    {
        Node<T>* cur = root;
        while (!isLeaf(cur)) {
            if (cur->left){
                cout<<cur->data<<" ";
                cur = cur->left;
            }
            else if (cur->right){
                cout<<cur->data<<" ";
                cur = cur->right;
            }
        }
        cout<<cur->data<<" \n";
    }

    void print_inorder1(Node<T>* current)
    {
        if(!current)
            return;
        if(current->left) cout<<"(";
        print_inorder1(current->left);
        cout<<current->data<<" ";
        print_inorder1(current->right);
        if(current->right) cout<<")";
    }
    // -------------------------------------------------
    void print_inorder(Node<T>* node) {
		if (node->left)
			print_inorder(node->left);
		cout << node->data << " ";
		if (node->right)
			print_inorder(node->right);
	}
    void print_inorder() {
        cout << "in: \t";
        print_inorder(root);
        cout<<"\n";
    }
    // -------------------------------------------------
	void print_preorder(Node<T>* node) {
		cout << node->data << " ";
		// traversal.push_back(data);
		if (node->left)
			print_preorder(node->left);
		if (node->right)
			print_preorder(node->right);
	}
    void print_preorder() {
        cout << "pre: \t";
        print_preorder(root);
        cout << endl;
    }
    // -------------------------------------------------
	void print_postorder(Node<T>* node) {
		if (node->left)
			print_postorder(node->left);
		if (node->right)
			print_postorder(node->right);
		cout << node->data << " ";
	}
    void print_postorder() {
        cout << "post: \t";
        print_postorder(root);
        cout << endl;
    }
    // -------------------------------------------------
    void add(vector<T> values,vector<char> direction)
    {
        assert(values.size()==direction.size());
        Node<T>* current = this->root;
        for(T i=0; (int) i<values.size();i++){
            if(direction[i]=='L'){
                if(!current->left)
                    current->left = new Node<T>(values[i]);
                else
                    assert(current->left->data == values[i]);
                current = current->left;
            }
            else { // Right
                if(!current->right)
                    current->right = new Node<T>(values[i]);
                else
                    assert(current->right->data == values[i]);
                current = current->right;
            }
        }
    }
    // hw1 p1
    T tree_max(Node<T>* node) {
        T mx = node->data;
        if (node->left) 
            mx = max(mx, tree_max(node->left));
        if (node->right)
            mx = max(mx, tree_max(node->right));
        return mx;
    }
    int tree_max()
    {
        return tree_max(root);
    }
    bool isLeaf(Node<T>* node)
    {
        return !node->left && !node->right;
    }
    // hw1 p2
    int tree_height(Node<T> *node) {
        int h = 0;
        if (node->left) 
            h = 1 + tree_height(node->left);
        if (node->right)
            h = max(h, 1 + tree_height(node->right));
        return h;
    }

    int tree_height()
    {
        return tree_height(root);
    }
    int total_nodes1(Node<T> *node)
    {
        if(!node)
            return 0;
        return 1 + total_nodes1(node->left) + total_nodes1(node->right);
    }
    // hw1 p3
    int total_nodes(Node<T> *node) {
        int n = 1;
        if (node->left)
            n += total_nodes(node->left);
        if (node->right)
            n += total_nodes(node->right);
        return n;
    }
    int total_nodes()
    {
        return total_nodes(root);
    }
    // hw1 p4
    int total_leaves(Node<T>* node)
    {
        if (!node)
            return 0;
        else if (isLeaf(node))
            return 1;
        return total_leaves(node->left) + total_leaves(node->right);
    }
    int total_leaves()
    {
        return total_leaves(root);
    }
    bool is_exists1(int value, Node<T>* node)
    {
        if(!node)
            return false;
        return is_exists1(value, node->left) || is_exists1(value,node->right) || (node->data==value);
    }
    // hw1 p5
    bool is_exists(int value, Node<T>* node) {
        bool res = node->data == value;
        if (node->left)
            res = res || is_exists(value, node->left);
        if (node->right)
            res = res || is_exists(value, node->right);
        return res;
    }
    bool is_exists(T value)
    {
        return is_exists(value,root);
    }
    // hw1 p6
    bool is_perfect(Node<T>* node)
    {
        if(!node) 
            return true;
        else if( (!node->left && node->right) || (node->left && !node->right) )
            return false;
        return is_perfect(node->right) && is_perfect(node->left);
    }
    bool is_perfect()
    {
        return is_perfect(root);
    }
    // hw2 p4
    // https://leetcode.com/problems/diameter-of-binary-tree/
    int get_diameter()
    {
        return get_diameter(root);
    }
    int get_diameter(Node<T>* node)
    {
        int left_dim = 0;
        int right_dim = 0;
        int hieght_sum = 0;

        if (node->left){
            left_dim = get_diameter(node->left);
            hieght_sum += 1 + tree_height(node->left);
        }
        if (node->right){
            right_dim = get_diameter(node->right);
            hieght_sum += 1 + tree_height(node->right);
        }
        return max(hieght_sum, max(left_dim, right_dim));
    }
    void level_order_traversal1()
    {
        queue<Node<T>*> q;
        q.push(root);
        while(!q.empty()){
            Node<T>* cur = q.front();
            q.pop();
            cout<<cur->data<<" ";
            if(cur->left)
                q.push(cur->left);
            if(cur->right)
                q.push(cur->right);
        }
        cout<<endl;
    }

    void level_order_traversal2()
    {
        queue<Node<T>*> q;
        q.push(root);
        int level = 0;
        while (!q.empty()){
            int sz = q.size();
            cout << "level " << level << ": ";

            while(sz--){
                Node<T>* cur = q.front();
                q.pop();

                cout<<cur->data<<" ";
                
                if(cur->left)
                    q.push(cur->left);
                if(cur->right)
                    q.push(cur->right);
            }
            level++;
            cout<<"\n";
        }
        cout<<endl;
    }
    // hw3 p1
    void level_order_traversal_recursive()
    {
        int h = tree_height();
        for (int level = 0; level <= h; level++)
            level_order_traversal_recursive(root, level);
    }
    void level_order_traversal_recursive(Node<T>* node, int level)
    {
        if (level == 0)
            cout << node->data << " ";
        else if (level) {
            if (node->left)
                level_order_traversal_recursive(node->left, level - 1);
            if (node->right)
                level_order_traversal_recursive(node->right, level - 1);
        }
    }
    // hw3 p2
    // https://leetcode.com/problems/check-completeness-of-a-binary-tree/
    bool is_complete()
    {
        queue<Node<T>*> q;
        queue< Node<T>*> nodes;
        q.push(root); 
        while(!q.empty()){
            int sz = q.size();
            while(sz--) {
                Node<T>* cur = q.front();
                q.pop();
                if(cur->left){
                    q.push(cur->left);
                    nodes.push(cur->left);
                }
                else {
                    nodes.push(nullptr);
                }
                if(cur->right){
                    q.push(cur->right);
                    nodes.push(cur->right);
                }
                else {
                    nodes.push(nullptr);
                }
            } 
        }
        while (!nodes.empty()) {
            Node<T>* node = nodes.front();
            nodes.pop();
            if(!node) {
                while (!nodes.empty()) {
                    Node<T>* right = nodes.front();
                    nodes.pop();
                    if(right)
                        return false;
                }
            }
        }
        return true;
    }
    // hw3 p3
    void level_order_traversal_spiral()
    {
        deque<Node<T>*> q;
        q.push_front(root);
        int level = 0;
        while(!q.empty()){
            int sz = q.size();
            cout<<"levle "<<level<<": ";

            if(level%2==0){
                while(sz--){
                    Node<T>* cur = q.front();
                    q.pop_front();

                    cout<<cur->data<<" ";
                    
                    if(cur->left)
                        q.push_back(cur->left);
                    if(cur->right)
                        q.push_back(cur->right);
                }
            }
            else {
                while(sz--){
                    Node<T>* cur = q.back();
                    q.pop_back();

                    cout<<cur->data<<" ";
                    
                    if(cur->right)
                        q.push_front(cur->right);
                    if(cur->left)
                        q.push_front(cur->left);
                }
            }
            level++;
            cout<<"\n";
            
        }
        cout<<endl;
    }
    

};


// LeetCode Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// "1,2,3,4,5,null,7"

queue<string> parse(string str)
{
    queue<string> v;
    stringstream ss(str);
 
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        v.push(substr);
    }
    return v;
}

TreeNode* createFromString(string str)
{
    queue<string> nodes = parse(str);
    TreeNode* root;

    while (!nodes.empty())
    {
        string s = nodes.front();
        nodes.pop();
        TreeNode* cur{nullptr};
        if (s != "null"){
            cur = new TreeNode(atoi(s.c_str()));
    
        }
    }
}

// https://leetcode.com/problems/binary-tree-level-order-traversal/
class Solution102 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        if(root)
            q.push(root);
        vector<vector<int>> levels;
        while (!q.empty()) {
            int sz = q.size();
            vector<int> level;
            while (sz--) {
                TreeNode* cur = q.front();
                q.pop();
                level.push_back(cur->val);
               
                if (cur->left)
                    q.push(cur->left);

                if (cur->right)
                    q.push(cur->right);
            }
            levels.push_back(level);
        }
        return levels;
    }
};

// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
class Solution103 {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        deque<TreeNode*> q;
        if (root)
            q.push_front(root);

        vector<vector<int>> levels;
        int level = 0;
        while(!q.empty()){
            int sz = q.size();
            vector<int> cur_level;
            if (level % 2 == 0){
                while(sz--){
                    TreeNode* cur = q.front();
                    q.pop_front();
                    cur_level.push_back(cur->val);
                    if(cur->left)
                        q.push_back(cur->left);
                    if(cur->right)
                        q.push_back(cur->right);
                }
            }
            else {
                while(sz--){
                    TreeNode* cur = q.back();
                    q.pop_back();
                    cur_level.push_back(cur->val);
                    if(cur->right)
                        q.push_front(cur->right);
                    if(cur->left)
                        q.push_front(cur->left);
                }
            }
            level++;
            levels.push_back(cur_level);
        }
        return levels;
    }
};

// https://leetcode.com/problems/minimum-depth-of-binary-tree/
class Solution111 {
public:
    bool isLeaf(TreeNode* node){
        return !node->left && !node->right;
    }
    int minDepth(TreeNode* root) {
        queue<TreeNode*> q;
        int level = 0;
        if(root)
            q.push(root);
        vector<vector<int>> levels;
        while (!q.empty()) {
            int sz = q.size();
            level++;
            while (sz--) {
                TreeNode* cur = q.front();
                q.pop();
                if (isLeaf(cur))
                    return level;
               
                if (cur->left)
                    q.push(cur->left);

                if (cur->right)
                    q.push(cur->right);
            }
        }
        return level;
    }
};

// https://leetcode.com/problems/maximum-depth-of-binary-tree/
class Solution104 {
public:
    int maxDepth(TreeNode* root) {
        if (!root)
            return 0;
        int res = 1;
        if (root->left)
            res = max(res, 1 + maxDepth(root->left));
        if (root->right)
            res = max(res, 1 + maxDepth(root->right));
        return res;
    }
};

// https://leetcode.com/problems/binary-tree-preorder-traversal/
class Solution {
    vector<int> pre;
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if (!root)
            return pre;
        pre.push_back(root->val);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
        return pre;
    }
};

// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
class Solution105 {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        deque<int> preorder_dq;
        deque<int> inorder_dq;
        for(int i = 0; i < (int)preorder.size(); i++){
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

// https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
class Solution106 {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return generateNode(postorder, inorder);
    }
    TreeNode* generateNode(vector<int>& postorder, vector<int>& inorder, int in_start = 0, int in_end = -1) {
        if (in_end == -1)
            in_end = (int) inorder.size() - 1;

        int value = postorder.back();
        postorder.pop_back();

        TreeNode* node = new TreeNode(value);

        for (int split = in_start; split <= in_end; split++) {
            if (inorder[split] == value) {
                if (split < in_end)
                    node->right = generateNode(postorder, inorder, split + 1, in_end);
                if (in_start < split)
                    node->left = generateNode(postorder, inorder, in_start, split - 1);
                break;
            }
        }
        return node;
    }
};

// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
class Codec297 {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root)
            return "()";
    
        string repr = "(" + to_string(root->val);
        
        if (root->left)
            repr += serialize(root->left);
        else 
            repr += "()";
        
        if (root->right)
            repr += serialize(root->right);
        else 
            repr += "()";

        repr += ")";

        return repr;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        string str = data.substr(1, (int) data.size() - 2);
        return deserialize_(str);
    }
    TreeNode* deserialize_(string data) {
        if (data.size() == 0)
            return nullptr;
        
        cout << data << endl;
        int start = 0;
        int val;
        for (int split = 0; split < data.size(); split++) {
            if (data[split] == '(') {
                start = split;
                break;
            }
        }

        
        string str = data.substr(0, start);
        int value = atoi(str.c_str());
        TreeNode* node = new TreeNode(value);

        int closeness = 0; // ( +1, ) -1
        for (int split = start; split < data.size(); split++) {
            if (data[split] == '(') 
                closeness++;
            if (data[split] == ')')
                closeness--;
            if (closeness == 0) {
                node->left = deserialize_(data.substr(start + 1, split - start - 1));
                node->right = deserialize_(data.substr(split + 2, data.size() - split - 3));
                break;
            }
        }
        return node;
    }
};

// https://leetcode.com/problems/find-duplicate-subtrees/
class Solution652 {
    set<string> dupls;
public:
    string serialize(TreeNode* root, unordered_map<string, TreeNode*> &mp) {
        if (!root)
            return "()";
    
        string repr = "(" + to_string(root->val);
        
        if (root->left){
            string left_repr = serialize(root->left, mp);
            if (mp.count(left_repr))
                dupls.insert(left_repr);
            mp[left_repr] = root->left;
            repr += left_repr;
        }
        else 
            repr += "()";
        
        if (root->right) {
            string right_repr = serialize(root->right, mp);
            if (mp.count(right_repr))
                dupls.insert(right_repr);
            mp[right_repr] = root->right;
            repr += right_repr;
        }
        else 
            repr += "()";

        repr += ")";

        return repr;
    }
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        unordered_map<string, TreeNode*> mp;
        serialize(root, mp);
        vector<TreeNode*> duplicates;
        for (auto s: dupls)
            duplicates.push_back(mp[s]);
        return duplicates;
    }
};

// https://leetcode.com/problems/binary-tree-inorder-traversal/
class Solution94 {
    vector<int> inorder;
public:
    void traverse(TreeNode* root) {
        if (!root)
            return;
        traverse(root->left);
        inorder.push_back(root->val);
        traverse(root->right);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        traverse(root);
        return inorder;
    }
};

// https://leetcode.com/problems/invert-binary-tree/
class Solution226 {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root)
            return root;
        
        TreeNode* left = root->left;
        TreeNode* right = root->right;

        root->left = invertTree(right);
        root->right = invertTree(left);
        return root;
    }
};

int main()
{
    // Create Nodes
	Node<int>* root = new Node<int>(1);
	Node<int>* node2 = new Node<int>(2);
	Node<int>* node3 = new Node<int>(3);
	Node<int>* node4 = new Node<int>(4);
	Node<int>* node5 = new Node<int>(5);
	Node<int>* node6 = new Node<int>(6);
	Node<int>* node7 = new Node<int>(7);
	Node<int>* node8 = new Node<int>(8);
	// Link them!
	root->left = node2;
	root->right = node3;
	node2->left = node4;
	node2->right = node5;
	node5->right = node7;
	node3->right = node6;
	node6->left = node8;
	cout << root->left->right->right->data << "\n";	// 7
	cout <<      node2->right->right->data << "\n";	// 7
	cout <<             node5->right->data << "\n";	// 7
	cout <<                    node7->data << "\n";	// 7
	cout << root->right->right->data << "\n";		// 6
	cout << root->right->right->left->data << "\n";	// 8
	cout << root->right->right->right << "\n";		// 0x00
    //  ----------------------------------------------------------
    Node<char>* plus = new Node<char>('+');
    Node<char>* n2 = new Node<char>('2');
    Node<char>* n3 = new Node<char>('3');
    plus->left = n2;
    plus->right = n3;
    print_inorder(plus);
    cout<<"\n";

    Node<char> *mul = new Node<char>('*');
    Node<char>* n4 = new Node<char>('4');
    mul->left = plus;
    mul->right = n4;

    print_postorder(mul);
    cout<<"\n";
    print_inorder(mul); cout<<"\n";
    clear(mul);
    cout<<"print for second time\n";
    print_postorder(mul);cout<<"\n";

    BinaryTree<int> tree(1);
	tree.add( { 2, 4, 7 }, { 'L', 'L', 'L' });
	tree.add( { 2, 4, 8 }, { 'L', 'L', 'R' });
	tree.add( { 2, 15, 9 }, { 'L', 'R', 'R' });
	tree.add( { 3, 6, 10 }, { 'R', 'R', 'L' });

	tree.print_inorder();
    // hw1 p1
    cout<<tree.tree_max()<<endl;
    // hw1 p2
    cout<<tree.tree_height()<<endl;
    // hw1 p3
    cout<<tree.total_nodes()<<endl;
    // hw1 p4
    cout<<tree.total_leaves()<<endl;
    // hw1 p5
    cout<<tree.is_exists(2)<<endl;
    cout<<tree.is_exists(14)<<endl;
    // hw1 p6
    cout<<tree.is_perfect()<<endl;
    // hw2 p1 
    // tree.clear();
    // cout<<tree.is_exists(2)<<endl;
    // hw2 p2
    tree.print_inorder();
    tree.print_inorder_iterative();
    // hw2 p3
    tree.traverse_left_boundry();
    //hw2 p4 
    cout<<tree.get_diameter()<<endl;
    //hw2 p5
    string postfix;
    postfix = "23+4*";
    postfix = "51+2/";
    postfix = "534*2^+";
    BinaryTree<char> exp_tree(postfix);
    // hw2 p6
    exp_tree.print_inorder();
    // 
    cout << "hw3:-----------------------------------------\n";
    tree.level_order_traversal1();
    tree.level_order_traversal2();
    // hw3 p1
    tree.level_order_traversal_recursive(); cout << endl;
    // hw 3 p2
    tree.level_order_traversal_spiral();
    // hw 3 p3
    cout<<tree.is_complete()<<endl;
    cout << "hw4:-----------------------------------------\n";
    // hw4 p1
    vector<int> pre_vec {1,2,4,7,8,5,9,3,6,10};
    deque<int> preorder;
    for(auto p:pre_vec)
        preorder.push_back(p);

    vector<int> in_vec {7,4,8,2,5,9,1,3,10,6};
    deque<int> inorder;
    for(auto p:in_vec)
        inorder.push_back(p);

    BinaryTree<int> tree1(preorder, inorder);
    // tree1.level_order_traversal2();
    tree1.print_inorder();
    // tree1.print_preorder();
    tree1.print_postorder();
    // tree1.print();
    
    // hw4 p2
    cout<<"----------------------\n";
    queue<pair<int, int>> preorder_queue;
    preorder_queue.push(make_pair(1,0));
    preorder_queue.push(make_pair(2,1));
    preorder_queue.push(make_pair(3,1));
    BinaryTree<int> tree2(preorder_queue);
    tree2.level_order_traversal2();
    tree2.print_inorder();
    cout << "hw5:-----------------------------------------\n";

    tree2.print_preorder_complete();
    cout<<tree2.parenthesize()<<endl;
    Codec297 c297;
    auto tree297 = c297.deserialize("(1(2()())(3()()))");
    
    cout<<tree.parenthesize()<<endl;
    cout<<tree.parenthesize_canonical()<<endl;
    // hw5 p1
    cout<<tree.is_symmetric()<<endl;
    cout<<tree1.is_symmetric()<<endl;
    cout<<tree2.is_symmetric()<<endl;
    // hw5 p2
    cout<<tree.is_flip_equiv(&tree1)<<endl; 
    return 0;
}


