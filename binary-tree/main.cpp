#include <iostream>
#include <cassert>
#include <string.h>
#include <stack>
#include <queue>

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
    // cout<<current->left->data<<" ";
    // cout<<current->data<<" ";
    // cout<<current->right->data<<" ";
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
    Node<T>* root{};

public:
    BinaryTree(T root_value)
    {
        root = new Node<T>(root_value);
    }
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
    ~BinaryTree()
    {
        clear();
    }
    void clear()
    {
        clear(root);
    }
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
    void print_inorder_iterative() // without recursion
    {
        stack<Node<T>*> stk;
        Node<T>* cur = root;
        
    }
    void traverse_left_boundry()
    {
        Node<T>* cur = root;
        while(!isLeaf(cur)){
            if(cur->left){
                cout<<cur->data<<" ";
                cur = cur->left;
            }
            else if(cur->right){
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
    T tree_max(Node<T>* node)
    {
        if(!node->right && !node->left)
            return node->data;
        else if(node->right && !node->left){
            T max_sub = tree_max(node->right);
            if(max_sub > node->data)
                return max_sub;
            else 
                return node->data;
        }
        else if(!node->right && node->left){
            T max_sub = tree_max(node->left);
            if(max_sub > node->data)
                return max_sub;
            else 
                return node->data;
        }
        else {
            T max_right = tree_max(node->right);
            T max_left = tree_max(node->left);
            if(node->data >= max_right && node->data >= max_left)
                return node->data;
            if(max_right >= node->data && max_right >= max_left)
                return max_right;
            if(max_left >= max_right && max_left >= node->data)
                return max_left;

        }
        
    }
    int tree_max()
    {
        return tree_max(root);
    }
    bool isLeaf(Node<T>* node)
    {
        return !node->left && !node->right;
    }
    int tree_height(Node<T> *node)
    {
        if(!node)
            return 0;
        else if( isLeaf(node) )
            return 0;
        else
            return 1+max(tree_height(node->left),tree_height(node->right));

    }
    int tree_height()
    {
        return tree_height(root);
    }
    int total_nodes(Node<T> *node)
    {
        if(!node)
            return 0;
        return 1 + total_nodes(node->left) + total_nodes(node->right);
    }
    int total_nodes()
    {
        return total_nodes(root);
    }
    int total_leaves(Node<T>* node)
    {
        if(!node)
            return 0;
        else if( isLeaf(node) )
            return 1;
        return total_leaves(node->left)+total_leaves(node->right);

    }
    int total_leaves()
    {
        return total_leaves(root);
    }
    bool is_exists(int value,Node<T>* node)
    {
        if(!node)
            return false;
        return is_exists(value,node->left) || is_exists(value,node->right) || (node->data==value);
        
    }
    bool is_exists(T value)
    {
        return is_exists(value,root);
    }
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
            hieght_sum += 1+tree_height(node->left);
        }
        if(node->right){
            right_dim = get_diameter(node->right);
            hieght_sum += 1+tree_height(node->right);
        }
        return max(hieght_sum,max(left_dim,right_dim));

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
    exp_tree.print_inorder();
    return 0;
}


