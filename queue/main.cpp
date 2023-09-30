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
        array = new int [size];
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

int main()
{   
    queue<int> q; 
    
    return 0;
}

