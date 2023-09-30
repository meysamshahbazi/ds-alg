#include <iostream>
#include <cassert>
#include <string.h>
#include <stack>
#include <queue>

using namespace std;

class Queue {
    int size{};
    int front{0};
    int rear{0};
    int added_elements{0};
    int *array{};

    int next(int pos) {
        // return (pos + 1)%size; // mod is slow!!
        ++pos;
        if(pos==size)
            pos = 0;
        return pos;
    }
public:
    Queue(int size):size{size}
    {
        array = new int[size];
    }
    ~Queue()
    {
        delete[] array;
    }
    bool empty()
    {
        return added_elements==0;   
    }
    bool isFull()
    {
        return added_elements == size;
    }
    void enqueue(int value)
    {
        assert(!isFull());
        array[rear] = value;
        rear = next(rear);
        added_elements++;
    }
    int dequeue()
    {
        assert(!empty());
        int value = array[front];
        front = next(front);
        --added_elements;
        return value;
    }
    void display()
    {
        cout<<"Front: "<<" - Rear: "<<rear<<"\t";
        if(isFull())
            cout<<"full";
        else if( empty() ) {
            cout<<"Empty\n";
            return;
        }
        cout<<"\n";
        for(int cur=front,step=0;step <added_elements;++step,cur=next(cur))
            cout<<array[cur]<< ", ";
        cout<<"\n";
    }
};

class Deque
{
    int size{};
    int front{0};
    int rear{0};
    int added_elements{0};
    int *array{};

    int next(int pos) {
        // return (pos + 1)%size; // mod is slow!!
        ++pos;
        if(pos==size)
            pos = 0;
        return pos;
    }
    int perv(int pos) {
        --pos;
        if(pos==-1)
            pos = size-1;
        return pos;
    }
public:
    Deque(int size):size{size}
    {
        array = new int[size];
    }
    ~Deque()
    {
        delete[] array;
    }
    bool empty()
    {
        return added_elements==0;   
    }
    bool isFull()
    {
        return added_elements == size;
    }
    void enqueue_rear(int value)
    {
        assert(!isFull());
        array[rear] = value;
        rear = next(rear);
        added_elements++;
    }
    void enqueue_front(int value)
    {
        assert(!isFull());
        front = perv(front);
        array[front] = value;
        added_elements++;
    }
    int dequeue_front()
    {
        assert(!empty());
        int value = array[front];
        front = next(front);
        --added_elements;
        return value;
    }
    int dequeue_rear()
    {
        assert(!empty());
        rear = perv(rear);
        int value = array[rear];
        --added_elements;
        return value;
    }
    void display()
    {
        cout<<"Front: "<<front<<" - Rear: "<<rear<<"\t";
        if(isFull())
            cout<<"full";
        else if( empty() ) {
            cout<<"Empty\n";
            return;
        }
        cout<<"\n";
        for(int cur=front,step=0;step <added_elements;++step,cur=next(cur))
            cout<<array[cur]<< ", ";
        cout<<"\n";
    }
};

class Stack
{
private:
    queue<int> q;
    int added_elements{0};

public:
    void pop()
    {
        added_elements--;
        q.pop();
    }

    void push(int value)
    {
        // queue<int> qq;
        // while(!q.empty()){
        //     qq.push(q.front());
        //     q.pop();
        // }
        // q.push(value);
        // while(!qq.empty()){
        //     q.push(qq.front());
        //     qq.pop();
        // }
        int sz = added_elements;
        q.push(value);
        while(sz--){
            q.push(q.front());
            q.pop();
        }
        added_elements++;
    }

    int peek()
    {
        return q.front();
    }
    bool empty() { return q.empty();}
};

class QueueHw1p3
{
private:
    int size;
    int added_element{0};
    stack<int> s1;
    stack<int> s2;
public:
    QueueHw1p3()
    {

    }
    bool empty()
    {
        return added_element==0;   
    }
    void enqueue(int value)
    {
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
        s1.push(value);
        while (!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
        added_element++;
    }
    int dequeue()
    {
        int val = s1.top();
        s1.pop();
        added_element--;
        return val;
    }
};

class QueueHw1p4
{
private:
    int size;
    int added_element{0};
    stack<int> s1;
    stack<int> s2;
public:
    QueueHw1p4()
    {

    }
    bool empty()
    {
        return added_element==0;   
    }
    void enqueue(int value)
    {
        s1.push(value);
        added_element++;

    }
    int dequeue()
    {
        while (!s1.empty())
        {
            s2.push(s1.top());
            s1.pop();
        }
        int val = s2.top();
        s2.pop();
        while (!s2.empty())
        {
            s1.push(s2.top());
            s2.pop();
        }
        added_element--;
        return val;
    }
};

int main()
{   
    // hw1 p1
    Deque dq(6);
    dq.enqueue_front(3);
    dq.enqueue_front(2);
    dq.enqueue_rear(4);
    dq.enqueue_front(1);
    dq.display();
    cout<<dq.dequeue_rear()<<endl;
    dq.display();
    cout<<dq.dequeue_front()<<endl;
    dq.display();
    cout<<dq.dequeue_rear()<<endl;
    cout<<dq.dequeue_front()<<endl;
    dq.enqueue_rear(7);
    dq.display();
    // hw1 p2
    Stack stk;
    stk.push(10); stk.push(20); stk.push(30); 
    while (!stk.empty() ){
        cout<<stk.peek()<<", ";
        stk.pop();
    }
    cout<<endl;
    // hw1 p3
    QueueHw1p3 qup3;
    for(int i=1;i <=3;i++)
        qup3.enqueue(i);
    cout<<qup3.dequeue()<<", ";
    for(int i=4;i<=5;i++)
        qup3.enqueue(i);

    while (!qup3.empty()) {
        cout<<qup3.dequeue()<<", ";
    }
    cout<<endl;
    
    // hw1 p4
    QueueHw1p4 qup4;
    for(int i=1;i <=3;i++)
        qup4.enqueue(i);
    cout<<qup4.dequeue()<<", ";
    for(int i=4;i<=5;i++)
        qup4.enqueue(i);

    while (!qup4.empty()) {
        cout<<qup4.dequeue()<<", ";
    }
    cout<<endl;
    return 0;
}

