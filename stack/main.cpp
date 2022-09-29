#include <iostream>
#include <cassert>
#include <string.h>
// #include <ostream>

using namespace std;

template <class T>
class Stack
{
private:
    int size{};
    int top{};
    T* array{};
public:
    Stack(int size): size(size), top(-1)
    {
        array = new T[size];
    }
    ~Stack() 
    {
        delete[] array;
    }
    void push(T val)
    {
        assert(!is_full());
        array[++top] = val;
    }
    T pop()
    {
        assert(!is_empty());
        return array[top--];
    }
    T peek()
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
            std::cout<<array[i]<<" ";
        std::cout<<endl;
    }
    int get_top(){return top;}
};
#define MAX_WORD_SIZE 10
string reverse_subwords(string line)
{
    string ret{""};
    Stack<char> word(MAX_WORD_SIZE);
    for(char &c:line)
    {
        if(c!=' ')
        {
            word.push(c);
        }
        else
        {
            while (!word.is_empty())
            {       
                ret+=string{word.pop()};
            }
            ret += " ";   
        }   
    }
    while (!word.is_empty())
    {       
        ret+=string{word.pop()};
    }
    return ret;
}

int revers_num(int num)
{
    Stack<int> stk{MAX_WORD_SIZE};
    while (num>0)
    {
        stk.push(num%10);
        num=num/10;
    }
    int ret=0;
    int d =1;
    while (!stk.is_empty())
    {
     ret = ret+d*stk.pop();
     d *= 10;  
    }
    return ret;
}
bool isValid(string str)
{
    // valid prantehesis
    Stack<char> stk_opend(MAX_WORD_SIZE);
    Stack<char> stk_closed(MAX_WORD_SIZE);
    for(char &c:str)
    {
        if(c =='(')
        {
            stk_opend.push(c);
        }
        if(c == ')')
        {
            stk_closed.push(c);
        }
    }

    

}

int main() 
{
    Stack<int> stk(3);
	stk.push(10);
	stk.push(20);
	stk.push(30);
    cout<<stk.get_top()<<endl;
	if (!stk.is_full())
		stk.push(50);
	else
		std::cout << "Full Stack\n";
	stk.display();	// 30 20 10
	std::cout << stk.peek() << "\n";	// 30

	while (!stk.is_empty()) 
    {
		std::cout << stk.peek() << " ";
		stk.pop();
	} // 30 20 10
    std::cout<<endl;

    string line{"abc df g higj"};
    std::cout<<reverse_subwords(line)<<endl;
    std::cout<<revers_num(4521)<<endl;
    return 0;
}

