#include <iostream>
#include <cassert>

using namespace std;

class Stack
{
private:
    int size{};
    int top{};
    int* array{};
public:
    Stack(int size): size(size), top(-1)
    {
        array = new int [size];
    }
    ~Stack() 
    {
        delete [] array;
    }
    void push(int val)
    {
        assert(!is_full());
        array[++top] = val;
    }
    int pop()
    {
        assert(!is_empty());
        return array[top--];
    }
    int peek()
    {
        assert(!is_empty());
        return array[top];
    }
    int is_full()
    {
        return top==size-1;
    }
    int is_empty()
    {
        return top ==-1;
    }
    void display()
    {
        for(int i=top;i>-1;i--)
            cout<<array[i]<<" ";
        cout<<endl;
    }



};

int main() 
{
    Stack stk(3);
	stk.push(10);
	stk.push(20);
	stk.push(30);

	if (!stk.is_full())
		stk.push(50);
	else
		cout << "Full Stack\n";
	stk.display();	// 30 20 10
	cout << stk.peek() << "\n";	// 30

	while (!stk.is_empty()) {
		cout << stk.peek() << " ";
		stk.pop();
	} // 30 20 10
    cout<<endl;
    return 0;
}

