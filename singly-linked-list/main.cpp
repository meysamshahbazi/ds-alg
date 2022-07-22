#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

// #define DEBUG

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
#ifdef DEBUG    
    int length {0};

    vector<Node*> debug_data;	// add/remove nodes you use

    void debug_add_node(Node* node) {
		debug_data.push_back(node);
	}
	void debug_remove_node(Node* node) {
		auto it = std::find(debug_data.begin(), debug_data.end(), node);
		if (it == debug_data.end())
			cout << "Node does not exist\n";
		else
			debug_data.erase(it);
	}
#endif
public:
    LinkedList() {}
    // ~LinkedList()
    // {
    //     Node * cur = head;
    //     Node * temp;
    //     while(cur)
    //     {
    //         temp = cur->next;
    //         delete cur;
    //         cur = temp;
    //     }     
    // }
    ~LinkedList()
    {
        Node * cur = head;
        while (head)
        {
            cur = head->next;
            delete head;
            head = cur;
        }
        
    }
    LinkedList (const LinkedList& ) = delete;
    LinkedList &operator=(const LinkedList& another) = delete;
#ifdef DEBUG
    void debug_print_address() 
    {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur << "," << cur->data << "\t";
		cout << "\n";
	}

	void debug_print_node(Node* node, bool is_seperate = false) {
		if (is_seperate)
			cout << "Sep: ";
		if (node == nullptr) {
			cout << "nullptr\n";
			return;
		}
		cout << node->data << " ";
		if (node->next == nullptr)
			cout << "X ";
		else
			cout << node->next->data << " ";

		if (node == head)
			cout << "head\n";
		else if (node == tail)
			cout << "tail\n";
		else
			cout << "\n";
	}
	void debug_print_list(string msg = "") {
		if (msg != "")
			cout << msg << "\n";
		for (int i = 0; i < (int) debug_data.size(); ++i)
			debug_print_node(debug_data[i]);
		cout << "************\n"<<flush;
	}

#endif
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
    void print_for()
    {
        for(Node * cur = head;cur; cur= cur->next)
        {
            cout<<cur->data<<" ";
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
    void insert_front(int value)
    {
        Node * new_head = new Node(value);
        
        if(head == nullptr)
        {
            head = new_head;
            tail = new_head;
        }
        else 
        {
            new_head->next = head;
            head = new_head;    
        }
    }
    void delete_front()
    {
        if(head == nullptr)
            return;

        else if (tail == nullptr)
        {
            head = nullptr;
            return;
        }
        else
        {
            Node * new_head = head->next;
            delete head;
            head = new_head;
        }
            
    }
    Node * get_nth(int n)
    {
        int cnt = 0;
        for(Node * cur = head;cur; cur= cur->next)
            if(cnt++ == n)
                return cur;
        
        return nullptr;
    }
    Node * get_nth_back(int n)
    {
        int cnt = 0;
        int len = get_lenght();

        // for(Node *cur = head; cur; cur = cur->next)
        //     if(cnt++ == (len-n-1))
        //         return cur;
        return get_nth(len-n-1);
    }
    int get_lenght() const
    {
        int len = 0;
        for(Node *cur = head; cur; cur = cur->next)
            len++;
            
        return len;
        
    }
    int search(int value)
    {
        int cnt {0};
        for(Node * cur = head;cur; cur= cur->next,cnt++)
            if(cur->data == value)
                return cnt;
        return -1;
    }
    bool is_same(const LinkedList & another)
    {
        int alen = another.get_lenght();
        if(this->get_lenght() != alen)
            return false;

        for(Node *cur=head,*acur=another.head;cur; cur= cur->next,acur=acur->next)
            if (cur->data != acur->data)
                return false;
            
        return true;
    }
    int improved_search(int value)
    {
        //the idea of this function is swapping nodes by changing the next attr
        // it goes pretty long so best practice is doing by changing data
        // but for huge data it may be usefull 
        int cnt {0};
        Node * cur = head;
        Node * perv = head;
        Node * perv2 = nullptr;
        while (cur)
        {
            
            if(cur->data == value)
            {
                if(cnt > 1)
                {
                    perv2->next = cur;
                    perv->next = cur->next;
                    cur->next= perv;
                }
                else if(cnt ==1 )
                {
                    perv->next = cur->next;
                    head = cur;
                    head->next = perv;
                }
                return cnt;
            }
            cnt++;
            perv2 = perv;
            perv = cur;
            cur = cur->next;
            
        }
        return -1;
    }
    int improved_search1(int value)
    {
        int cnt {0};
        Node * perv = nullptr;
        for(Node * cur = head;cur; cur= cur->next,cnt++)
        {
            if(cur->data == value)
            {
                if(!perv)
                {
                    return cnt;
                }
                int temp = cur->data;
                cur->data = perv->data;
                perv->data = temp;
                return cnt-1;
            }
            perv = cur;

        }
    }

    int improved_search2(int value)
    {
        int cnt {0};
        for(Node * cur = head,*perv = nullptr;cur;perv=cur,cur=cur->next,cnt++)
            if(cur->data == value)
            {
                if(!perv)
                {
                    return cnt;
                }
                int temp = cur->data;
                cur->data = perv->data;
                perv->data = temp;
                return cnt-1;
            }
        return -1;
    }
#ifdef DEBUG
    void debug_verify_data_integrity()
    {
		if (length == 0) 
        {
			assert(head == nullptr);
			assert(tail == nullptr);
		} 
        else 
        {
			assert(head != nullptr);
			assert(tail != nullptr);
			if (length == 1)
				assert(head == tail);
			else
				assert(head != tail);
			assert(!tail->next);
		}
		int len = 0;
		for (Node* cur = head; cur; cur = cur->next, len++)
			assert(len < 10000);	// Consider infinite cycle?
		assert(length == len);
		assert(length == (int)debug_data.size());   

    }
    string debug_to_string()
    {
        // if(length == 0)
        //     return " ";
        ostringstream oss;
        for(Node * cur =head; cur; cur=cur->next)
        {
            oss<<cur->data;
            if(cur->next)
                oss<<" ";
        }
        return oss.str();
    }
#endif
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
    list.print_for();
    cout<<list.get_nth(1)->data<<endl;
    cout<<list.search(1)<<endl;
    cout<<list.search(5)<<endl;
    cout<<list.search(4)<<endl;
    cout<<list.improved_search(1)<<endl;
    list.print();
    cout<<list.improved_search(1)<<endl;
    list.print();
    cout<<list.improved_search1(4)<<endl;
    list.print();
    cout<<list.improved_search1(2)<<endl;
    list.print();
    cout<<list.improved_search2(4)<<endl;
    list.print();
    cout<<list.improved_search2(1)<<endl;
    list.print();
    list.insert_front(5);
    list.print();
    list.insert_front(6);
    list.print();
    list.delete_front();
    list.print();
    list.delete_front();
    list.print();
    LinkedList list2;
    
    cout<<list.get_nth_back(3)->data<<endl;
    list2.insert_front(1);
    list2.print();
    list2.insert_front(2);
    list2.print();
    list2.insert_front(3);
    list2.print();
    list2.delete_front();
    list2.print();
    list2.delete_front();
    list2.print();
    list2.delete_front();
    list2.print();
    cout<<list2.is_same(list)<<endl;
    LinkedList l1;
    l1.insert_end(1);
    l1.insert_end(2);
    l1.insert_end(3);
    LinkedList l2;
    l2.insert_end(1);
    l2.insert_end(2);
    l2.insert_end(3);
    cout<<l1.is_same(l2)<<endl;
#ifdef DEBUG    
    cout<<list.debug_to_string()<<endl;
#endif
    return 0;
}