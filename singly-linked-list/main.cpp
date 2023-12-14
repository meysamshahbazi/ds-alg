#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <climits>
// #define DEBUG

using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int val):val(val){} 
};

void print1(Node *head)
{
    while (head != nullptr) {
        cout << head->val << " ";
        head = head->next;
    }
    cout<<endl; 
}

void print11(Node *head)
{
    for (Node* cur = head; cur != nullptr; cur = cur->next)
        cout << cur->val << " ";
    cout<<endl; 
}

void print2(Node *head)
{
    if (head == nullptr) {
        cout << endl;
        return;
    }

    cout << head->val << " ";
    print2(head->next);
}

void print_reversed(Node *head)
{
    if (head == nullptr) {
        cout << endl;
        return;
    }

    print_reversed(head->next);
    cout << head->val << " ";
}

Node* find(Node* head,int value) 
{
    if (head == nullptr)
        return nullptr;
    
    if (head->val == value)
        return head;
    
    return find(head->next, value);
}

// https://leetcode.com/problems/reverse-linked-list/
typedef Node ListNode;
ListNode* reverseList1(ListNode* head) // recursive!
{
    if (!head || !head->next)
        return head;
    
    ListNode* head_next = head->next;
    ListNode* rhead = reverseList1(head->next);
    head_next->next = head;
    head->next = nullptr;
    return rhead;
}

ListNode* reverseList(ListNode* head) // iterative!
{
    if (!head || !head->next)
        return head;
    
    ListNode* prv = head;
    ListNode* cur = head->next;

    while (cur) {
        ListNode* next = cur->next;
        cur->next = prv;
        prv = cur;
        cur = next;
    }
    head->next = nullptr;
    return prv;
}

// https://leetcode.com/problems/insertion-sort-list/
ListNode* insertionSortList(ListNode* head) {
    ListNode* sorted = nullptr;

    ListNode* cur = head;
    
    while (cur) {
        ListNode* next_step = cur->next;

        if (!sorted) {
            sorted = cur;
            cur->next = nullptr;
            cur = next_step;
            continue;
        }

        ListNode* scur = sorted, *prv = nullptr;
        for (scur = sorted, prv = nullptr; scur; prv = scur, scur = scur->next) 
            if (cur->val <= scur->val) 
                break; 

        if (!scur) {
            prv->next = cur;
            cur->next = nullptr;
        }
        if (!prv) {
            cur->next = sorted;
            sorted = cur;
        }
        else {
            prv->next = cur;
            cur->next = scur;
        }

        cur = next_step;
    }

    return sorted;
    
}

// https://leetcode.com/problems/delete-node-in-a-linked-list/
void deleteNode(ListNode* node) {
    for (ListNode* cur = node, *prv = nullptr; cur; prv = cur, cur = cur->next) {
        if (cur->next)
            cur->val = cur->next->val;
        else {
            delete cur;
            prv->next = nullptr;
            return;
        } 
    }
}

// https://leetcode.com/problems/remove-linked-list-elements/
ListNode* removeElements(ListNode* head, int val) {
    if (!head)
        return head;
    
    if (head->val == val) {
        ListNode* next = head->next;
        delete head;
        return removeElements(next, val); 
    }   
    ListNode* next = removeElements(head->next, val);
    head->next = next;
    return head;
}

// https://leetcode.com/problems/swap-nodes-in-pairs/
ListNode* swapPairs(ListNode* head) {
    for(ListNode* cur = head; cur && cur->next; cur = cur->next->next)
        std::swap(cur->val, cur->next->val);        

    return head;
}
// https://leetcode.com/problems/swapping-nodes-in-a-linked-list/
ListNode* swapNodes(ListNode* head, int k) {
    int i = 0;
    int n = 0;
    ListNode* tail, *prv_tail;
    for(ListNode* cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next) {
        tail = cur;
        prv_tail = prv;
        n++;
    }

    if (n == 1)
        return head;

    if (k == 1 || k == n) {
        if (n == 2 ){
            tail->next = head;
            head->next = nullptr;
            return tail;
        }
        ListNode* next = head->next;
        prv_tail->next = head;
        head->next = nullptr;
        tail->next = next;
        return tail;

    }

    ListNode* prv_k, *prv_n_k;
    k = min(k , n - k + 1);
    if (k == n - k) {
        for(ListNode* cur = head; cur; cur = cur->next) {
            i++;
            if(i == k - 1)
                prv_k = cur;
        }
        ListNode* node_k = prv_k->next;
        ListNode* next_k = node_k->next;
        ListNode* next_next_k = next_k->next;
        prv_k->next = next_k;
        next_k->next = node_k;
        node_k->next = next_next_k;
        return head;
    }

    for(ListNode* cur = head; cur; cur = cur->next) {
        i++;
        if (i == k - 1)
            prv_k = cur;
        if (i == n - k )
            prv_n_k = cur;
    }
    ListNode* node_k = prv_k->next;
    ListNode* node_n_k = prv_n_k->next;
    ListNode* next_k = prv_k->next->next;
    ListNode* next_n_k = prv_n_k->next->next;
    cout << node_k->val << " " << node_n_k->val << endl;

    prv_k->next = node_n_k;
    node_n_k->next = next_k;
    prv_n_k->next = node_k;
    node_k->next = next_n_k;
    
    return head;
    
}
// https://leetcode.com/problems/remove-duplicates-from-sorted-list/
ListNode* deleteDuplicates(ListNode* head) {
    if (!head || !head->next)
        return head;

    int value = head->val;
    ListNode* cur = head->next, *prv = head;
    while (cur) {
        if (prv->val == cur->val) {
            ListNode* next = cur->next;
            prv->next = next;
            delete cur;
            cur = next;
        }
        else {
            prv = cur;
            cur = cur->next;
        }
    }
    return head;
}

// https://leetcode.com/problems/rotate-list/
ListNode* rotateRight(ListNode* head, int k) {
    int len = 0;
    ListNode* tail;
    for (ListNode* cur = head; cur; cur = cur->next) {
        len++;
        tail = cur;
    }

    if (len <= 1)
        return head;

    int k_ = k % len;

    if (k_ == 0)
        return head;

    int i = 0;
    ListNode* rkhead = nullptr;
    for (ListNode* cur = head; cur; cur = cur->next) {
        if (++i == len - k_){
            rkhead = cur->next;
            cur->next = nullptr;
            tail->next = head;
            break;
        }
    }
    return rkhead;
}

// https://leetcode.com/problems/remove-nth-node-from-end-of-list/
ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (!head)
        return head;

    int sz = 0;
    for (ListNode* cur = head; cur; cur = cur->next)
        sz++;
    
    if (n == sz) {
        ListNode* next = head->next;
        delete head;
        return next;
    }
    if (n == 1) {
        ListNode* prv;
        for (ListNode* cur = head; cur->next; cur = cur->next)
            prv = cur;
        delete prv->next;
        prv->next = nullptr;
        return head;
    }
    int i = 0;
    ListNode* prv;
    for (ListNode* cur = head; cur; cur = cur->next)
        if (++i == sz - n){
            prv = cur;
            break;
        }
    
    ListNode* nth = prv->next;
    prv->next = nth->next;
    delete nth;
    return head;
}


// https://leetcode.com/problems/odd-even-linked-list/ hw4p1
ListNode* oddEvenList(ListNode* head) { 
    if (!head || !head->next || !head->next->next)
        return head;

    ListNode *odd_head = head;
    ListNode *even_tail = head->next;

    ListNode* cur = head;
    while (cur) {
        ListNode* next = cur->next;
        if(!next)
            break;
        cur->next = cur->next->next;
        cur = next; 
    }
    ListNode* odd_tail;
    for (odd_tail = head;odd_tail->next;odd_tail = odd_tail->next);
    odd_tail->next = even_tail;
    return odd_head;
}

// https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/ hw4p4
ListNode* deleteDuplicates(ListNode* head) {
    if (!head || !head->next)
        return head;
    
    for (ListNode* cur = head->next, *prv = head,*prv2 = nullptr; cur; ) {
        if (prv->val == cur->val) {
            int val = prv->val;
            ListNode* next;
            for(next = prv; next && next->val == val; next = next->next);
            if (!prv2) {
                head = next;
                prv = head;
            }
            else {
                prv2->next = next;
                prv = next;
            }

            if (!next)
                return head;
            cur = next->next;
        }
        else {
            prv2 = prv;
            prv = cur;
            cur = cur->next;
        }
    }
    return head;
}

// https://leetcode.com/problems/reverse-nodes-in-k-group/ hw4p5
ListNode* reverseKGroup(ListNode* head, int k) {
     
}

class LinkedList
{
private:
    Node* head {nullptr};
    Node* tail {nullptr};
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
    LinkedList() 
    {

    }

    ~LinkedList() // hw1 p1
    {
        Node* cur = head;
        while (head) {
            cur = head->next;
            delete head;
            head = cur;
        }
    }

    LinkedList (const LinkedList& ) = delete;
    LinkedList& operator=(const LinkedList& another) = delete;
#ifdef DEBUG
    void debug_print_address() 
    {
		for (Node* cur = head; cur; cur = cur->next)
			cout << cur << "," << cur->val << "\t";
		cout << "\n";
	}

	void debug_print_node(Node* node, bool is_seperate = false) {
		if (is_seperate)
			cout << "Sep: ";
		if (node == nullptr) {
			cout << "nullptr\n";
			return;
		}
		cout << node->val << " ";
		if (node->next == nullptr)
			cout << "X ";
		else
			cout << node->next->val << " ";

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
        Node* cur = head;
        while (cur != nullptr) {
            cout << cur->val << " ";
            cur = cur->next;
        }
        cout<<endl;   
    }

    void print_for()
    {
        for(Node* cur = head; cur; cur = cur->next) {
            cout << cur->val << " ";
        }
        cout<<endl;
    }

    void insert_end(int value)
    {
        Node* node = new Node(value);
        node->next = nullptr;

        if (head == nullptr) {
            head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }
    }

    void insert_front(int value) // hw1 p2
    {
        Node* new_head = new Node(value);
        new_head->next = head;
        head = new_head;

        if (head->next == nullptr)
            tail = new_head;
    }

    void delete_front() // hw1 p3
    {
        if (head == nullptr)
            return;

        Node* new_head = head->next;
        delete head;
        head = new_head;

        if (head == nullptr || head->next == nullptr) // len is 0 or len is 1
            tail = head;    
    }

    void delete_first()
    {
        if(head) {
            Node* cur = head;
            head = head->next;
            delete cur;
            if (!head) 
                tail = nullptr;
        }
    }

    void delete_last()
    {
        if (tail) {
            int len = get_lenght();
            if (len <= 1) {
                delete_first();
                return;
            }
            // in case we have at least 2 Nodes
            Node* befor_last = get_nth_back(1);
            // delete befor_last->next;
            delete tail;
            befor_last->next = nullptr;
            tail = befor_last;
        }
    }

    void delete_nth(int n)
    {
        int len = get_lenght();

        if (n == 1) {
            delete_first();
            return;
        }

        Node* perv = get_nth(n-1); // perv node befor we delete
        Node* nth = perv->next;
        perv->next = nth->next;
        delete nth;
    }

    Node* get_nth(int n) // 0-based indexing
    {
        int cnt = 0;
        for (Node* cur = head; cur; cur = cur->next)
            if (cnt++ == n)
                return cur;
        
        return nullptr;
    }

    Node* get_nth_back(int n) // hw1 p4
    {
        int cnt = 0;
        int len = get_lenght();
        return get_nth(len - n - 1);
    }

    int get_lenght() const
    {
        int len = 0;
        for(Node* cur = head; cur; cur = cur->next)
            len++;
        
        return len;
    }

    int search(int value)
    {
        int cnt {0};
        for (Node* cur = head; cur; cur = cur->next, cnt++)
            if (cur->val == value)
                return cnt;
        return -1;
    }

    bool is_same(const LinkedList & another) // hw1 p5
    {
        int alen = another.get_lenght();
        if (this->get_lenght() != alen)
            return false;

        for(Node *cur=head,*acur = another.head; cur; cur = cur->next, acur = acur->next)
            if (cur->val != acur->val)
                return false;
            
        return true;
    }
    int improved_search(int value)
    {
        // the idea of this function is swapping nodes by changing the next attr
        // it goes pretty long so best practice is doing by changing val
        // but for huge val it may be usefull 
        int cnt {0};
        Node* cur = head;
        Node* perv = head;
        Node* perv2 = nullptr;
        while (cur) {
            if (cur->val == value) {
                if (cnt > 1) {
                    perv2->next = cur;
                    perv->next = cur->next;
                    cur->next= perv;
                }
                else if (cnt == 1) {
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
        Node* perv = nullptr;
        for (Node* cur = head; cur; cur = cur->next, cnt++) {
            if (cur->val == value) {
                if (!perv) {
                    return cnt;
                }
                swap(perv->val, cur->val);
                return cnt - 1;
            }
            perv = cur;
        }
        return -1;
    }
    // hw2 p1
    void delete_next_node(Node* node) {
		Node* to_delete = node->next;
		bool is_tail = to_delete == tail;
		// node->next in middle to delete
		node->next = node->next->next;
		delete to_delete;
        // delete_node(to_delete);

		if(is_tail)
			tail = node;
	}
    // hw2 p1
    void delete_with_key(int value)
    {
        if (!head)
            return;
        if (head->val == value) {
            delete_first();
            return;
        }

        for (Node* cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next) {
            if (cur->val == value) {
                delete_next_node(prv);
                return;
            }
        }
        
    }

    // hw2 p2
    void swap_pairs()
    {
        for(Node* cur = head; cur && cur->next; cur = cur->next->next)
            std::swap(cur->val, cur->next->val);        
    }
    // hw2 p3
    void reverse()
    {
        int len = get_lenght();
        for (int i = len -1 ; i > 0; i--) {
            Node* cur = get_nth(i);
            Node* perv = get_nth(i - 1); 
            cur->next = perv;
        }

        head->next = nullptr;
        std::swap(head,tail);
    }
    
    void reverse2() {
        tail = head;
        head = reverseList1(head);
    }
    // hw2 p4
    void delete_even_positions()
    {
        Node *perv = head;
        Node *cur = head->next;

        while (cur) {
            perv->next = cur->next;
            if (cur == tail){
                tail = perv;
                tail->next = nullptr;
            }
            delete cur;
            if (perv->next) {
                cur = perv->next->next;
                perv = perv->next;
            }
            else 
                return;            
        }
    }
    // hw2 p5
    void insert_sorted1(int value) {
        int len = get_lenght();
        if (len == 0) { 
            insert_front(value);
            return;
        }
        

    }
    void insert_sorted(int value)
    {
        int len = get_lenght();
        if (len == 0) { 
            insert_front(value);
            return;
        }
        // otherwise we are here and we assume the list is already sorted
        Node* perv;
        for (Node* cur = head; cur && cur->next; cur = cur->next){
            if (value >= cur->val && value <cur->next->val) {
                Node* n_ptr = new Node(value);
                n_ptr->next = cur->next;
                cur->next = n_ptr;
                return;
            }
        }
        // if the above condition if FOR dosnt met 
        // it means that the given value is larger than all of the list 
        // elements so we should put it on the back of list:
        if (value <= head->val)
            insert_front(value);
        else
            insert_end(value);

        return;
    }
    // hw3 p1
    void swap_head_tail()
    {
        Node *perv_tail;
        // this one line FOR loop is intersting for me! I did some trick for that :P
        // also readble logic for doing so is the next commented FOR loop with an IF :))
        // for(perv_tail=head;perv_tail->next!=tail;perv_tail=perv_tail->next)

        // for(Node * cur=head;cur;cur=cur->next)
        //     if(cur->next==tail)
        //         perv_tail = cur;

        // and better way or in other words use modules .. 
        perv_tail = get_nth_back(1);
        
        tail->next = head->next;
        perv_tail->next = head;
        head->next = nullptr;
        std::swap(head,tail);
    }
    // hw3 p2
    void rotate_left_once()
    {
        tail->next = head;
        Node * after_head = head->next;
        head->next = nullptr;
        tail = head;
        head = after_head;
    }
    // hw3 p2
    void rotate_left(int k)
    {
        // this is my own solution
        int len = get_lenght();
        k = k % len;
        for(int i=0;i<k;i++)
            rotate_left_once();
    }
    // hw3 p2
    void rotate_left2(int k)
    {
        // this is idea from video!
        int len = get_lenght();
        k = k%len;
        tail->next = head;
        Node * nth = get_nth(k);
        tail = get_nth(k-1);
        tail->next = nullptr;
        head = nth;
    }
    // https://leetcode.com/problems/remove-duplicates-from-an-unsorted-linked-list/ premium
    void remove_duplicates() // not sorted! hw3 p3
    {
        if (!head || !head->next)
            return;

        for (Node* cur1 = head;cur1; cur1 = cur1->next) {
            for (Node* cur2 = cur1->next, *prv = cur1; cur2;) { // no steppeing statement 
                if (cur1->val == cur2->val) {
                    delete_next_node(prv);
                    cur2 = prv->next;
                }
                else {
                    prv = cur2;
                    cur2 = cur2->next;
                }
            }
        }
    }
    // hw3 p4
    void remove_last_occurance(int key)
    {
        // a little diffrence from orginal problem but its Ok...
        int n = -1;
        int i = 0;
        bool seen = false;
        for (Node* cur = head; cur; cur = cur->next) {
            // we will find and record last occurance index of given key
            if (key == cur->val || !seen) {
                seen = true;
                i++;
                continue;
            }
            if (seen && key == cur->val) 
                n = i;
            i++;
        }
        if(n != -1)
            delete_nth(n);
    }
    // hw3 p5
    void move_to_back(int key)
    {
        int nb_occ = 0;
        // at first we count all of key in list
        for(Node* cur = head; cur; cur=cur->next)
            if(cur->val == key)
                nb_occ++;

        // remove all of them and insert them in back 
        for(int i = 0; i < nb_occ; i++) {
            delete_with_key(key);
            insert_end(key);
        }
    }

    // hw3 p5
    void move_key_occurance_to_end(int key) 
    {
        int len = get_lenght();
        for(Node* cur = head, *prv = nullptr; len--;) {
            if (key == cur->val)
                cur = move_to_end(cur, prv);
            else 
                prv = cur, cur = cur->next;
        }        
    }

    Node* move_to_end(Node* cur, Node* prv) {
		Node* next = cur->next;
		tail->next = cur;

		if (prv)
			prv->next = next;
		else
			head = next;	// cur was head

		tail = cur;
		tail->next = nullptr;
		return next;
	}

    void push_node_to_back(Node * prv)
    {
        // this function aims to delete node after from chain and
        // put that node to the end of chain!
        if(!prv->next || !prv->next->next) // the node is tail so it is already at the end of chain
            return;

        Node *cur = prv->next;
        prv->next = prv->next->next;
        tail->next = cur;
        cur->next = nullptr;
        tail = cur;
        return;
    }
    // hw3 p6
    int max(Node* cur) 
    {
        if (!cur->next)
            return cur->val;
        return std::max(cur->val, max(cur->next));
    }
    int max() 
    {
        return max(head);
    }
    
    // leetcode oddEvenList hw4 p1
    void arrange_odd_even()
    {
        int len = this->get_lenght();

        int nb_pushed = 0;

        Node* prv = head;
        while (nb_pushed < len / 2) {
            push_node_to_back(prv);
            prv = prv->next;
            nb_pushed++;
        }
    }

    // hw4 p2
    void insert_alternate(LinkedList &another)
    {
        Node *cur=head;
        Node *acur= another.head;
        while (cur && acur)
        {
            Node *cur_next = cur->next;
            // Node *acur_next = acur->next;
            Node * acur_cpy = new Node(acur->val);
            cur->next = acur_cpy;
            acur_cpy->next = cur_next;

            tail = acur_cpy;
            cur = cur_next;
            acur = acur->next;
        }
        // we push back all remining nodes to the end of current list 
        while (cur)
        {
            Node *cur_next = cur->next;
            tail->next = cur;
            tail = cur;   
            cur = cur_next;
        }           

        while (acur)
        {
            Node * acur_cpy = new Node(acur->val);
            tail->next = acur_cpy;
            tail = acur_cpy;   
            acur = acur->next;
        }
        // at the end we need to close the chain by ending with nullptr
        tail->next = nullptr;
    }
    // hw4 p3
    void add_num(LinkedList &another)
    {
        Node *cur = head;
        Node *acur = another.head;
        int carry = 0;
        while (cur && acur)
        {
            int val = cur->val + acur->val + carry;
            cur->val = val%10;
            carry = val/10;
            cur = cur->next;
            acur = acur->next;
        }

        while (cur)
        {
            int val = cur->val+carry;
            cur->val = val%10;
            carry = val/10;
            cur = cur->next;
        }
        
        while (acur)
        {
            int val = acur->val+carry;
            this->insert_end(val%10);
            carry = val/10;
            acur = acur->next;
        }
    }
    // hw4 p4 leetcode
    void remove_all_repeated()
    {
        // assume given list is sorted!
        Node *cur=head;
        int nb_rm = 0;
        int len = get_lenght();
        while (cur)
        {
            if(! cur->next)
                return;
            if(cur->next->val > cur->val)
                cur = cur->next;
            else 
            {
                // find next non equal value to cur->val to use that as next itration value of cur
                Node *cur2;
                for(cur2=cur->next;cur2;cur2=cur2->next)
                    if(cur2->val != cur->val)
                        break;
                
                

                int val_to_del = cur->val;
                
                // remove all of node with value of cur->val;
                while (improved_search1(val_to_del) != -1)
                {
                    delete_with_key(val_to_del);
                    nb_rm++;
                }
                cur = cur2;                
            }
        }
    }   
    // hw4 p5 leetcode
    void reverse_chains(int k)
    {
        // TODO: 
        return;
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
            oss<<cur->val;
            if(cur->next)
                oss<<" ";
        }
        return oss.str();
    }
#endif
};

// hw1 p6
class LinkedList2 {
private:
	Node *head { };
public:
    void print() {
        for(Node* cur = head; cur; cur = cur->next)
            cout << cur->val << " ";
        cout << endl;
    }
    void push_back(int value) {
        Node* node = new Node(value);
        node->next = nullptr;
        Node* tail = get_tail();
        tail->next = node;
    }

    void push_front(int value) {
        Node* node = new Node(value);
        node->next = head;
        head = node;
    }

    Node* get_tail() {
        Node* cur;
        for ( ; cur; cur = cur->next);
        return cur;
    }
};

ListNode* fromVector(vector<int> vec) {
    ListNode* head, *cur;
    head = new ListNode(vec[0]);
    cur = head;
    for (int i = 1; i < (int)vec.size(); i++) {
        cur->next = new ListNode(vec[i]);
        cur = cur->next;
    }
    return head;
}

int main()
{   
    Node* node1 = new Node(1);
    Node* node2 = new Node(2);
    Node* node3 = new Node(3);
    Node* node4 = new Node(4);
    Node* node5 = new Node(5);

    

    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = nullptr;

    print1(node1);
    ListNode* head1721 = fromVector({1,2});
    // {7,9,6,6,7,8,3,0,9,5}
    print1(head1721);
    auto nswaped = swapNodes(head1721, 1);
    print1(nswaped);

    auto head328 = fromVector({1,2,3,4,5,6});
    print1(head328);
    head328 = oddEvenList(head328);
    print1(head328);
    // print1(node1);
    // print11(node1);
    // print2(node1);
    // print_reversed(node1);
    // cout << endl;
    // cout << find(node1, 4) << " " << find(node1, 44) << endl; 
    // print1(node1);
    // ListNode* rnode1 = reverseList(node1);
    // print1(rnode1);
    // ListNode* r2node = rotateRight(node1, 2);
    // print1(r2node);
    /*
    cout<<"\n";
    LinkedList list;
    list.insert_end(4);
    list.insert_end(3);
    list.insert_end(2);
    list.insert_end(1);
    list.print();
    list.print_for();
    cout<<list.get_nth(1)->val<<endl;
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
    cout<<list.improved_search1(4)<<endl;
    list.print();
    cout<<list.improved_search1(1)<<endl;
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
    
    cout<<list.get_nth_back(3)->val<<endl;
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
    l2.insert_end(33);
    cout<<l1.is_same(l2)<<endl;
    l2.insert_end(3);
    l2.insert_end(4);
    l2.insert_end(5);
    
    cout<<"----------------------\n";
    cout<<"test for delete nodes\n\n";
    l2.print();
    l2.delete_nth(4);
    cout<<"----------------------\n";
    l2.print();
    l2.delete_first();
    l2.print();
    l2.delete_last();
    l2.print();
    cout<<"----------------------\n";
    cout<<"test for delete with key\n\n";
    l2.insert_end(31);
    l2.insert_end(41);
    l2.insert_end(51);
    l2.insert_end(31);
    l2.print();
    l2.delete_with_key(2);
    l2.print();
    l2.delete_with_key(31);
    l2.print();
    l2.delete_with_key(31);
    l2.print();
    cout<<"----------------------\n";
    cout<<"test for swap pairs\n\n";
     
    l2.insert_end(31);
    l2.insert_end(41);
    l2.insert_end(51);
    l2.insert_end(31);
    l2.insert_end(311);
    l2.print();
    l2.swap_pairs();
    l2.print();
    cout<<"test for swap pairs\n\n";
    l2.print();
    l2.reverse();
    l2.print();
    cout<<"----------------------\n";
    l2.delete_even_positions();
    l2.print();
    LinkedList l3;
    l3.insert_end(1);
    l3.insert_end(2);
    l3.insert_end(3);
    l3.insert_end(4);
    l3.insert_end(5);
    l3.insert_end(6);
    l3.insert_end(7);
    l3.insert_end(8);
    cout<<"----------------------\n";
    l3.print();
    l3.delete_even_positions();
    l3.print();
    cout<<"----------------------\n";
    cout<<"test for insert sorted :\n";
    LinkedList ls;
    ls.insert_sorted(20);
    ls.insert_sorted(10);
    ls.insert_sorted(9);
    ls.insert_sorted(5);
    ls.insert_sorted(7);
    ls.insert_sorted(20);
    ls.insert_sorted(10);
    ls.insert_sorted(9);
    ls.insert_sorted(5);
    ls.insert_sorted(7);
    ls.insert_sorted(7);
    ls.insert_sorted(7);
    ls.insert_sorted(7);
    ls.insert_sorted(20);
    ls.insert_sorted(10);
    ls.insert_sorted(9);
    ls.insert_sorted(5);
    ls.print();
    /*
    cout<<"swap_head_tail ----------------------\n";
    ls.print();
    ls.swap_head_tail();
    ls.print();
    cout<<" rotate_left ----------------------\n";
    ls.print();
    ls.rotate_left(2);
    ls.print();
    cout<<" remove_duplicates ----------------------\n";
    ls.print();
    cout<<ls.get_lenght()<<endl;
    ls.remove_duplicates();
    // ls.delete_last();
    ls.print();
    // cout<<ls.get_lenght()<<endl;
    cout<<" remove_last_occurance ----------------------------------\n";
    LinkedList l4;
    l4.insert_end(1);
    l4.insert_end(2);
    l4.insert_end(1);
    l4.insert_end(1);
    l4.insert_end(2);
    l4.insert_end(3);
    l4.insert_end(3);
    l4.insert_end(1);
    l4.insert_end(2);
    
    l4.print();
    l4.remove_last_occurance(3);
    l4.print();
    cout<<" move_to_back ----------------------------------\n";
    LinkedList l5;
    l5.insert_end(1);
    l5.insert_end(2);
    l5.insert_end(1);
    l5.insert_end(1);
    l5.insert_end(2);
    l5.insert_end(3);
    l5.insert_end(3);
    l5.insert_end(1);
    l5.insert_end(2);
    l5.insert_end(4);
    l5.insert_end(5);
    l5.print();
    l5.move_to_back(1);
    l5.print();
    cout<<" rotate_left ----------------------\n";
    l5.remove_duplicates();
    l5.print();
    l5.rotate_left2(4);
    l5.print();
    

    LinkedList l6;
    l6.insert_end(1);
    l6.insert_end(2);
    l6.insert_end(3);
    l6.insert_end(4);
    l6.insert_end(5);
    l6.insert_end(6);
    l6.print();
    //    l6.push_node_to_back(l6.get_nth(3));
    l6.arrange_odd_even();
    l6.print();
    */

/*
   LinkedList l7;
   l7.insert_end(1);l7.insert_end(2);l7.insert_end(3);l7.insert_end(4);l7.insert_end(5);
   LinkedList l8;
   l8.insert_end(44);l8.insert_end(55);l8.insert_end(66);l8.insert_end(77);l8.insert_end(88);l8.insert_end(99);l8.insert_end(101);
   l7.insert_alternate(l8);
   l7.print();
*/
/*
    LinkedList l9;
    l9.insert_end(1);l9.insert_end(2);l9.insert_end(3);l9.insert_end(4);
    LinkedList l10;
    l10.insert_end(9);l10.insert_end(2);l10.insert_end(3);
    l9.add_num(l10);
    l9.print();*/
    
    LinkedList l11;l11.insert_sorted(1);
    l11.insert_sorted(8);l11.insert_sorted(1);l11.insert_sorted(1);
    l11.insert_sorted(2);l11.insert_sorted(2);l11.insert_sorted(2);l11.insert_sorted(4);l11.insert_sorted(4);l11.insert_sorted(4);l11.insert_sorted(5);
    l11.print();
    l11.remove_all_repeated();
    cout<<l11.get_lenght()<<endl;
    l11.print();

    // LinkedList l12;
    // l12.insert_front(0);
    // l12.print();
    // l12.delete_first();
    // l12.print();
    


#ifdef DEBUG    
    cout<<list.debug_to_string()<<endl;
#endif
    return 0;
}