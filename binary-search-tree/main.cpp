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
    bool search_iterative(int target)
    {
        BinarySearchTree* cur = this;
        while (cur)
        {
            if (target==cur->data)
                return true;
            else if (target < cur->data)
                cur = cur->left;
            else 
                cur = cur->right;
        }
        return false;
        
    }
    void insert(int target)
    {
        if (target < data) {
            if(!left)
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
    int lowest_common_ancestor(int n1, int n2)
    {
        if (n1 <= data && n2 >=data)
            return data;
        if(n1<data && n2 <data)
            return left->lowest_common_ancestor(n1,n2);
        if(n1>data && n2>data)
            return right->lowest_common_ancestor(n1,n2);
    }
    int min_value()
    {
        BinarySearchTree* cur = this;
        while(cur && cur->left)
            cur = cur->left;
        return cur->data;
    }
    bool find_chain(vector<BinarySearchTree*> &ancestors, int target)
    {
        ancestors.push_back(this);
        if(target == data)
            return true;
        if (target < data)
            return  left && left->find_chain(ancestors, target);
        
        return right && right->find_chain(ancestors, target);
    }
    BinarySearchTree* get_next(vector<BinarySearchTree*> &ancestors)
    {
        if(ancestors.size() == 0)
            return nullptr;
        BinarySearchTree* node = ancestors.back();
        ancestors.pop_back();
        return node;
    }
    pair<bool, int> successor(int target)
    {
        vector<BinarySearchTree*> ancestors;

        if(!find_chain(ancestors, target))
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


 };


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
    pair<bool, int> suc_pair =  tree.successor(60);
    cout<<suc_pair.second<<endl;
    return 0;
}


