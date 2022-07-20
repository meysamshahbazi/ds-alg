#include <iostream>

using namespace std;

struct Node{
    int data;
    Node * next;

    Node(int data):data(data){}

};

int main()
{
    Node * node1 = new Node(5);
    Node * node2 = new Node(8);
    Node * node3 = new Node(4);
    Node * node4 = new Node(1);

    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = nullptr;
    
    return 0;
}