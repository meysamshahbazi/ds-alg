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
    cout<<current->data<<" ";
}

void clear(Node<char>* current)
{
    if(!current)
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
    /**
     * @brief Construct a new Binary Tree object
     * 
     * @param preorder_queue 
     */
    BinaryTree(queue<pair<int, int>> &preorder_queue)
    {
        root = generateNode(preorder_queue);
    }
    Node<T>* generateNode(queue<pair<int, int>> &preorder_queue)
    {

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
        
        if(node->left)
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

    void print_inorder(Node<T>* current)
    {
        if(!current)
            return;
        if(current->left) cout<<"(";
        print_inorder(current->left);
        cout<<current->data<<" ";
        print_inorder(current->right);
        if(current->right) cout<<")";
    }
    void print_inorder()
    {
        print_inorder(root);
        cout<<"\n";
    }
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
        return 1 + total_nodes1(node->left) + total_nodes(node->right);
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

        if(node->left){
            left_dim = get_diameter(node->left);
            hieght_sum += 1 + tree_height(node->left);
        }
        if(node->right){
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
        while(!q.empty()){
            int sz = q.size();
            cout<<"levle "<<level<<": ";

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
    void level_order_traversal_recursive()
    {
        level_order_traversal_recursive(root);
    }
    void level_order_traversal_recursive(Node<T>* node)
    {
        
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
    /* 
    tree.level_order_traversal1();
    tree.level_order_traversal2();
    // hw 3 p2
    tree.level_order_traversal_spiral();
    // hw 3 p3
    cout<<tree.is_complete()<<endl;
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
    tree1.level_order_traversal2();
    tree1.print_inorder();
    // hw4 p2
    cout<<"----------------------\n";
    queue<pair<int, int>> preorder_queue;
    preorder_queue.push(make_pair(1,0));
    preorder_queue.push(make_pair(2,1));
    preorder_queue.push(make_pair(3,1));
    BinaryTree<int> tree2(preorder_queue);
    tree2.level_order_traversal2();
    tree2.print_inorder();
    cout<<"----------------------\n";
    // TODO: solve this!
    // https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
    tree.print_preorder_complete();
    cout<<tree2.parenthesize()<<endl;
    cout<<tree.parenthesize()<<endl;
    cout<<tree.parenthesize_canonical()<<endl;
    // hw5 p1
    cout<<tree.is_symmetric()<<endl;
    cout<<tree1.is_symmetric()<<endl;
    cout<<tree2.is_symmetric()<<endl;
    // hw5 p2
    cout<<tree.is_flip_equiv(&tree1)<<endl; */
    return 0;
}


