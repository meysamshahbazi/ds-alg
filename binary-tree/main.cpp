#include <iostream>
#include <cassert>
#include <string.h>
#include <stack>
#include <queue>

using namespace std;

struct Node
{
    int data{};
    Node* left;
    Node* right;
    Node(int data): data{data} 
    {
    }
};

int main()
{
    // Create Nodes
	Node* root = new Node(1);
	Node* node2 = new Node(2);
	Node* node3 = new Node(3);
	Node* node4 = new Node(4);
	Node* node5 = new Node(5);
	Node* node6 = new Node(6);
	Node* node7 = new Node(7);
	Node* node8 = new Node(8);
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
    
    return 0;
}


