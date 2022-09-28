#include <iostream>
#include <cassert>
#include <climits>

#include <sstream>
#include <algorithm>

using namespace std;

struct Node
{
    int data{};
    Node* next{nullptr};
    Node* prev{nullptr};

    Node(int data): data(data) {}

    void set(Node *next,Node * prev)
    {
        this->next = next;
        this->prev = prev;
    }
    ~Node() {}
};

void link(Node* first, Node* second)
{
    if(first)
        first->next = second;
    if(second)
        second->prev = first;
}
class LinkedList
{
private:
    Node *head{};
    Node * tail{};

public:
    LinkedList() {}
    LinkedList(const LinkedList&) = delete;
    LinkedList &operator=(const LinkedList &) = delete;
    void insert_end(int value)
    {
        Node *item = new Node(value);
        if(!head)
            head = tail= item;
        else
        {
            link(tail,item);
            tail = item;
        }
    }
    void insert_front(int value)
    {
        Node *item = new Node(value);
        if(!head)
            head = tail= item;
        else
        {
            link(item,head);
            head = item;
        }
    }
    void print()
    {
        for(Node *cur=head; cur; cur=cur->next)
            cout<<cur->data<<" ";
        cout<<endl;
    }
};

int main()
{       
    LinkedList l;
    l.insert_end(1);l.insert_end(2);l.insert_end(3);
    l.print(); 
    l.insert_front(44);l.insert_front(55);l.insert_front(66);
    l.print();
    return 0;
}



