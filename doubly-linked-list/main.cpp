#include <iostream>
#include <cassert>
#include <climits>

#include <sstream>
#include <algorithm>

using namespace std;

struct Node
{
    int data{};
    Node* next{};
    Node* prev{};

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

};

int main()
{       
    

    return 0;
}



