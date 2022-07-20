#include <iostream>

using namespace std;

struct Node{
    int data;
    Node * next;

    Node(int data):data(data){}

};

void print1(Node *head)
{
    while (head != nullptr)
    {
        cout<<head->data<<" ";
        head = head->next;
    }
    cout<<endl; 
}
void print2(Node *head)
{
    if(head != nullptr)
    {
        cout<<head->data<<" ";
        print2(head->next);
    }
    else
    {
        cout<<endl;
        return;
    }
}
void print_reversed(Node *head)
{
    if(head != nullptr)
    {
        
        print_reversed(head->next);
        cout<<head->data<<" ";

    }
    
    return;
}
class LinkedList
{
private:
    Node *head {nullptr};
    Node *tail {nullptr};
public:
    void print()
    {
        Node * temp_head = head;
        while (temp_head != nullptr)
        {
            cout<<temp_head->data<<" ";
            temp_head = temp_head->next;
        }
        cout<<endl;   
    }
    void insert_end(int value)
    {
        Node * node = new Node(value);
        node->next = nullptr;
        if (head == nullptr)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
        

    }
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


    print1(node1);
    print2(node1);
    print_reversed(node1);
    cout<<"\n";
    LinkedList list;
    list.insert_end(4);
    list.insert_end(3);
    list.insert_end(2);
    list.insert_end(1);
    list.print();

    return 0;
}