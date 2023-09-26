#include <iostream>
#include <cassert>
#include <string.h>
#include <stack>
#include <queue>
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
    bool is_empty()
    {
        return top ==-1;
    }
    void display()
    {
        for(int i=top;i>-1;i--)
            std::cout<<array[i]<<" ";
        std::cout<<endl;
    }
    int get_top() const {return top;}
    void insert_at_bottom(T x)
    {
        if(top ==-1){
            push(x);
            return;
        }
        else {
            T t = pop();
            insert_at_bottom(x);
            push(t);
        }
    }
    void reverse()
    {
        if(top == 0){
            return;
        }
        else {
            T t = pop();
            reverse();
            insert_at_bottom(t);
        }
    }
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

char close_with(const char c)
{
    // input char c colse with return value
    if(c == ')') return '(';
    if(c == ']') return '[';
    return '{';
}
bool isValid1(string str)
{
    // valid prantehesis
    Stack<char> opened(MAX_WORD_SIZE);
    
    for(char &c:str)
    {
        if(c =='(' || c =='[' || c =='{' )
            opened.push(c);
        else if(opened.is_empty() || opened.pop() != close_with(c))
            return false;
    }
    return opened.is_empty();
}

bool isValid(string s) //https://leetcode.com/problems/valid-parentheses/
{
    std::stack<char> opened;
    for(const char &c:s)
    {
        if(c =='(' || c =='[' || c =='{' )
            opened.push(c);
        
        else if( opened.empty() ) 
            return false;
        else
        {
            char poped = opened.top();
            opened.pop();
            if(poped !=close_with(c))
                return false;
        }
    }
    return opened.empty();
}
string removeDuplicates1(string s)
{
    Stack<char> stk(MAX_WORD_SIZE);
    for(const char &c:s)
    {
        if(stk.is_empty() || c!=stk.peek() )
            stk.push(c);
        else 
            stk.pop();
    }
    string ret (stk.get_top()+1, ' ' );
    for(int i=ret.size()-1;i>=0;i--)
        ret[i]=stk.pop();
    return ret;
}

string removeDuplicates(string s) //https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/
{
    std::stack<char> stk;
    for(const char &c:s)
    {
        if(stk.empty() || c!=stk.top() )
            stk.push(c);
        else 
            stk.pop();      
    }
    // string ret (stk.size(), ' ' );
    // for(int i=ret.size()-1;i>=0;i--)
    // {
    //     ret[i]=stk.top();
    //     stk.pop();
    // }
    string ret;
    while (!stk.empty())
    {
        ret = stk.top()+ret;
        stk.pop();
    }
    
    return ret;
}

vector<int> asteroidCollision(vector<int>& asteroids) { // https://leetcode.com/problems/asteroid-collision/
    std::stack<int> stk;
    std::vector<int> res;
    for(auto a:asteroids){
        bool do_push = true;
        while (!stk.empty()){
            if (a <0 && stk.top() >0) {
                if(-a > stk.top()){
                    stk.pop();
                    do_push = true;
                }
                else if (-a == stk.top()){
                    stk.pop();
                    do_push = false;
                    break;
                }
                else {
                    do_push = false;
                    break;
                }
            }
            else {
                do_push = true;
                break;
            }
        }
        if(do_push)
            stk.push(a);
    }
    stack<int> stk2;
    while (!stk.empty())
    {
        stk2.push(stk.top());
        stk.pop();
    }
    while (!stk2.empty())
    {
        res.push_back(stk2.top());
        stk2.pop();
    }
    
    return res;

}

int scoreOfParentheses(stack<char> s)
{
    int closeness = 0;
    stack<char> stk;
    if(s.empty()) return 0;
    if(s.size() == 2 ){
        return  1;
    }

    while (!s.empty()) {
        char c = s.top();
        if ( c==')' )
            closeness++;
        else 
            closeness--;

        stk.push(c);
        s.pop();

        if( closeness == 0 ){
            return scoreOfParentheses(s)+scoreOfParentheses(stk);       
        }

        if(s.size() == 1){
            stack<char> stk_inside;
            while(stk.size() > 1) {
                char cc = stk.top();
                stk.pop();
                stk_inside.push(cc);
            }
            return 2*scoreOfParentheses(stk_inside);
        }
    }
    return 0;
}

int scoreOfParentheses(string s) // https://leetcode.com/problems/score-of-parentheses/
{
    stack<char> stk;
    for(char c:s)
        stk.push(c);
    
    return scoreOfParentheses(stk);
}

// https://leetcode.com/problems/daily-temperatures/
vector<int> dailyTemperatures(vector<int>& temperatures) 
{
    // TODO: sumbit proper code!
    stack<int> stk;
    for(auto t:temperatures)
        stk.push(t);
    
    stack<int> greaters;
    stack<int> answer;
    while (!stk.empty()) {
        int t = stk.top();
        
        while (!greaters.empty() && t>greaters.top()) {
            greaters.pop();
        }

        if(greaters.empty())
            answer.push(-1);
        else 
            answer.push(greaters.top());

        greaters.push(t);
        stk.pop();
    }
    
    vector<int> res;
    while (!answer.empty()) {
        res.push_back(answer.top());
        answer.pop();
    }
    return res;
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
    std::cout<<revers_num(45021)<<endl;

    cout << isValid("(())") << "\n";		// 1
	cout << isValid("(()[()])") << "\n";	// 1
	cout << isValid("(][)") << "\n";		// 0
	cout << isValid("(()") << "\n";	

    cout<<removeDuplicates("abbaca")<<endl;
    // hw2 p1 
    vector<int> astroids = {8,-8};//{1,-1,-2,-2};
    auto res = asteroidCollision(astroids);
    for(auto r:res)
        cout<<r<<", ";
    cout<<endl;
    // hw2 p2,p3
    Stack<int> stk2(20);
    stk2.push(1);stk2.push(2);stk2.push(3);
    stk2.display();
    stk2.insert_at_bottom(0);
    stk2.display();
    stk2.reverse();
    stk2.display();
    // hw2 p5
    string s = "(()(()))";
    cout<<scoreOfParentheses(s)<<"\n";
    // hw2 p6
    vector<int> temps = {8, 73, 74, 75, 71, 69, 72, 76, 73} ;
    for(auto r:temps)
        cout<<r<<", ";
    cout<<endl;
    auto next_greaters = dailyTemperatures(temps);
    for(auto r:next_greaters)
        cout<<r<<", ";
    cout<<endl;
    return 0;
}

