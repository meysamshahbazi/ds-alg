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


class LinkedList
{
private:
    Node *head{};
    Node * tail{};

public:
    LinkedList() {}
    LinkedList(const LinkedList&) = delete;
    LinkedList &operator=(const LinkedList &) = delete;

    void link(Node* first, Node* second)
    {
        if(first)
            first->next = second;
        if(second)
            second->prev = first;
    }

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
    void embed_after(Node* befor,int value)
    {
        Node* item = new Node(value);
        if(befor->next)
        {
            Node * after = befor->next;
            link(befor,item);
            link(item,after);
        }
        else 
        {
            insert_end(value);
        }
    }
    Node* get_head(){return head;}
    Node* get_tail(){return tail;}
    void insert_sorted(int value)
    {
        if(!head || value<= head->data)
        {
            insert_front(value);
            return;
        }
        if(value >= tail->data)
        {
            insert_end(value);
            return;
        }
        for(Node *cur=head;cur;cur=cur->next)
        {
            if(value>=cur->data)
                embed_after(cur->prev,value);
                return;
        }

    }
};

int main()
{       
    LinkedList l;
    /*
    l.insert_end(1);l.insert_end(2);l.insert_end(3);
    l.print(); 
    l.insert_front(44);l.insert_front(55);l.insert_front(66);
    l.print();
    l.embed_after(l.get_head(),111);
    l.print();
    cout<<"tail "<<l.get_tail()<<" |"<<l.get_tail()->data<<endl;
    l.embed_after(l.get_tail(),0);
    l.print();
    cout<<"tail "<<l.get_tail()<<" |"<<l.get_tail()->data<<endl;
    */
//    l.insert_end(0);
   l.insert_sorted(5);l.insert_sorted(50);l.insert_sorted(2);l.insert_sorted(1);
   l.print();
    return 0;
}



