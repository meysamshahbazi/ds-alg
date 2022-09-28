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
    void delete_front()
    {
        if(!head) return; // if we have no item in list just return
        if(!head->next) // if there is just one item in list:
        {
            delete head;
            head = tail = nullptr;
            return;
        }
        // otherwise we have atleast 2 node in list 
        Node* new_head = head->next;
        delete head;
        head = new_head;
        new_head->prev = nullptr;
    }
    void delete_end()
    {
        if(!head) return; // if we have no item in list just return
        if(!head->next) // if there is just one item in list:
        {
            delete head;
            head = tail = nullptr;
            return;
        }
        // otherwise we have atleast 2 node in list 
        Node* new_tail = tail->prev;
        delete tail;
        tail = new_tail;
        tail->next = nullptr;
    }
    
    Node* delete_and_link(Node* cur)
    {
        Node* new_cur = cur->prev;
        link(cur->prev,cur->next);
        delete cur;
        return new_cur;
    }
    void delete_node_with_key(int val)
    {
        if(!head) return;
        if(head->data == val) 
        {
            delete_front();
            return;
        }
        for(Node* cur=head;cur;cur=cur->next)
        {
            if(cur->data==val)
            {
                delete_and_link(cur);
                if(!cur->next)
                    tail = cur;
                return;
            }
        }
    }
    void delete_all_nodes_with_key(int val)
    {
        if(!head) return;
        
        Node* cur=head;
        while (cur)
        {
            if(cur->data==val)
            {
                if(cur == head)
                {
                    delete_front();
                    cur = head;
                }
                else
                {
                    cur = delete_and_link(cur);

                }
            }
            else 
                cur = cur->next;
        }
    }
    void delete_even_positions()
    {
        if(!head->next) return; // return for one node
        Node* cur=head->next;
        while (cur)
        {
            cur = delete_and_link(cur);
            if(!cur->next || !cur->next->next) return;
            cur = cur->next->next;
        }
    }

    void delete_odd_positions()
    {
        // this function has bug!!!fix itS
        if(!head->next)
        {
            delete_front();
            return; // return for one node
        }
        Node* new_head = head->next;
        Node* cur=head;
        while (cur)
        {
            cur = delete_and_link(cur);
            if(!cur->next || !cur->next->next) break;
            cur = cur->next->next;
        }
        head = new_head;
    }
    bool is_palindrome()
    {
        Node *cur=head;
        Node *rcur=tail;
        while (cur && rcur)
        {
            if(cur->data!=rcur->data)
                return false;
            
            cur=cur->next;
            rcur=rcur->prev;
        }
        return true;
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


    // l.insert_sorted(5);l.insert_sorted(50);l.insert_sorted(2);l.insert_sorted(1);
    /*
    l.print();
    l.delete_front();
    l.print();
    l.delete_front();
    l.print();
    l.delete_front();
    l.print();
    l.delete_front();
    l.print();
    */
    
    /*
    l.print();
    l.delete_end();
    l.print();
    l.delete_end();l.print();
    l.delete_end();l.print();
    l.delete_end();l.print();*/
    /*
    Node * temp = l.get_head()->next->next;
    l.print();
    cout<<temp->data<<endl;
    temp = l.delete_and_link(temp);
    l.print();
    cout<<temp->data<<endl;*/
    /*
    l.print();
    l.delete_node_with_key(5);l.print();
    l.delete_node_with_key(2);l.print();
    l.delete_node_with_key(1);l.print();
    l.delete_node_with_key(50);l.print();
    */
    /*
    l.insert_end(1);l.insert_end(1);l.insert_end(1);l.insert_end(2);
    l.insert_end(4);l.insert_end(3);l.insert_end(1);l.insert_end(3);
    l.print();
    l.delete_all_nodes_with_key(1);
    l.print();*/
    /*
    l.insert_end(1);l.insert_end(2);l.insert_end(3);l.insert_end(4);
    l.insert_end(5);l.insert_end(6);l.insert_end(7);l.insert_end(8);
    l.print();
    l.delete_even_positions();
    l.print();*/ 
    /*
    l.insert_end(1);l.insert_end(2);l.insert_end(3);l.insert_end(4);
    l.insert_end(5);l.insert_end(6);l.insert_end(7);l.insert_end(8);
    l.print();
    l.delete_odd_positions();
    l.print();
    */
    /*
    l.insert_end(1);l.insert_end(3);l.insert_end(3);l.insert_end(1);
    l.print();
    cout<<l.is_palindrome()<<endl;*/

    


    return 0;
}



