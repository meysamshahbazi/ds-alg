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
// HW1 P!
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
// HW1 P2
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
// hw1 p3
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
// HW1 p4
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

class PriorityQueue
{
private:
    queue<int> q3;
    queue<int> q2;
    queue<int> q1;
public:
    bool empty()
    {
        return q1.empty() && q2.empty() && q3.empty();
    }
    void enqueue(int value, int priorty)
    {
        if(priorty==3)
            q3.push(value);
        if(priorty==2)
            q2.push(value);
        if(priorty==1)
            q1.push(value);
    }
    int dequeue()
    {
        if(!q3.empty()){
            int val = q3.front();
            q3.pop();
            return val;
        }
        if(!q2.empty()){
            int val = q2.front();
            q2.pop();
            return val;
        }
        if(!q1.empty()){
            int val = q1.front();
            q1.pop();
            return val;
        }
    }
    void display()
    {
        cout<<"P3: ";
        while (!q3.empty()) {
            cout<<q3.front()<<", ";
            q3.pop();
        }
        cout<<endl;
        cout<<"P2: ";
        while (!q2.empty()) {
            cout<<q2.front()<<", ";
            q2.pop();
        }
        cout<<endl;
        cout<<"P1: ";
        while (!q3.empty()) {
            cout<<q1.front()<<", ";
            q1.pop();
        }
        cout<<endl;
    }


};


class QueueHw2p2 {
    int size{};
    int front{-1};
    int rear{0};
    int *array{};

    int next(int pos) {
        ++pos;
        if(pos==size)
            pos = 0;
        return pos;
    }
public:
    QueueHw2p2(int size):size{size}
    {
        array = new int[size];
    }
    ~QueueHw2p2()
    {
        delete[] array;
    }
    bool empty()
    {
        return rear==0 && front==-1;   
    }
    bool isFull()
    {
        return !empty() && rear==front;
    }
    void enqueue(int value)
    {
        assert(!isFull());
        array[rear+1] = value;
        rear = next(rear);
    }
    int dequeue()
    {
        assert(!empty());
        int value = array[front+1];
        front = next(front);
        if(rear-front==0) { // queue is about to be empty!
            rear =-1;
            front =-1;
        }
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
        for(int cur=front,step=0;cur!=rear;++step,cur=next(cur))
            cout<<array[cur]<< ", ";
        cout<<"\n";
    }
};

class Last_k_numbers_sum_stream
{
private:
    queue<int> q;
    int k;
    int sum{0};
public:
    Last_k_numbers_sum_stream(int k):k{k}
    {
    }
    int next(int new_num){
        if(q.size() == k) {
            sum -= q.front();
            q.pop();
        }
        sum +=new_num;
        q.push(new_num);
        return sum;
    }
};

// https://leetcode.com/problems/product-of-the-last-k-numbers/
class ProductOfNumbers {
public:
    stack<int> stk;
    ProductOfNumbers() {
        
    }
    
    void add(int num) {
        stk.push(num);
    }
    
    int getProduct(int k) {
        stack<int> temp;
        int i{0};
        int product = 1;
        while(i<k){
            int top = stk.top();
            product *= top;
            temp.push(top);
            stk.pop();
            i++;
        }
        while (!temp.empty()) {
            stk.push(temp.top());
            temp.pop();
        }
        return product;
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
    // hw2 p1
    PriorityQueue tasks;

	tasks.enqueue(1131, 1);
	tasks.enqueue(3111, 3);
	tasks.enqueue(2211, 2);
	tasks.enqueue(3161, 3);

	// tasks.display();


	cout << tasks.dequeue() << "\n";	// 3111
	cout << tasks.dequeue() << "\n";	// 3161

	tasks.enqueue(1535, 1);
	tasks.enqueue(2815, 2);
	tasks.enqueue(3845, 3);
	tasks.enqueue(3145, 3);


	while (!tasks.empty())
		cout << tasks.dequeue() << " ";
    cout<<"\n---------------------------------------------"<<endl;
    //---------------------------------------------    
    // hw2 p2 
    // QueueHw2p2 qu(6);
	// assert(qu.empty());
	// qu.display();

	// for (int i = 1; i <= 6; ++i) {
	// 	assert(!qu.isFull());
	// 	qu.enqueue(i);
	// 	qu.display();
	// }
	// assert(qu.isFull());

	// for (int i = 1; i <= 6; ++i) {
	// 	assert(!qu.empty());
	// 	qu.dequeue();
	// 	//qu.display();
	// }

	// for (int i = 1; i <= 6; ++i) {
	// 	assert(!qu.isFull());
	// 	qu.enqueue(i);
	// 	qu.display();
	// }

	// qu.dequeue();
	// assert(!qu.isFull());
	// qu.enqueue(7);
	// assert(qu.isFull());
	// qu.display();

	// qu.dequeue();
	// qu.dequeue();
	// assert(!qu.isFull());
	// qu.enqueue(8);
	// assert(!qu.isFull());
	// qu.display();
	// qu.enqueue(9);
	// assert(qu.isFull());
	// qu.display();

	// for (int i = 1; i <= 6; ++i) {
	// 	assert(!qu.empty());
	// 	qu.dequeue();
	// 	qu.display();
	// }

    // hw2 p3
    // Last_k_numbers_sum_stream lknss(4);
    // int num;
    // while (cin>>num)
    // {
    //     cout<<lknss.next(num)<<endl;
    // }
    cout<<"------------------------"<<endl;
    ProductOfNumbers productOfNumbers = ProductOfNumbers();
    productOfNumbers.add(3);        // [3]
    productOfNumbers.add(0);        // [3,0]
    productOfNumbers.add(2);        // [3,0,2]
    productOfNumbers.add(5);        // [3,0,2,5]
    productOfNumbers.add(4);        // [3,0,2,5,4]
    cout<<productOfNumbers.getProduct(2)<<endl; // return 20. The product of the last 2 numbers is 5 * 4 = 20
    cout<<productOfNumbers.getProduct(3)<<endl; // return 40. The product of the last 3 numbers is 2 * 5 * 4 = 40
    cout<<productOfNumbers.getProduct(4)<<endl; // return 0. The product of the last 4 numbers is 0 * 2 * 5 * 4 = 0
    productOfNumbers.add(8);        // [3,0,2,5,4,8]
    cout<<productOfNumbers.getProduct(2)<<endl; // return 32. The product of the last 2 numbers is 4 * 8 = 32 


    return 0;
}

