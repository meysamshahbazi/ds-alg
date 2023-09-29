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

class StackLL
{
private: 
    struct Node
    {
        int data{};
        Node *next{nullptr};
        Node(int data):data(data) {}
    };
    Node * head{nullptr};
public:
    ~StackLL() {
        while (!empty()) {
            pop();
        }
    }
    int pop()
    {
        assert(!empty());
        int element = head->data;
        Node *temp = head;
        head = head->next;
        delete temp;
        return element;
    }
    void push(int data)
    {
        Node *newNode  = new Node(data);
        newNode->next = head;
        head = newNode;
        
    }
    int empty() 
    {
        return !head;
    }
    void display()
    {
        for(Node *cur=head;cur;cur = cur->next)
            cout<<cur->data<<", ";
        cout<<"\n";
    }
    int peek()
    {
       assert(!empty());
       return head->data;
    }
    int getLenght()
    {
        int len = 0;
        for(Node *cur=head;cur;cur = cur->next)
            len++;
        return len;
    }
    void delete_middle()
    {
        int len = getLenght();

        Node *cur;
        int index = 0;
        for(cur=head;cur;cur = cur->next){
            index++;
            if(index == len/2)
                break;
        }
        Node *temp = cur->next;// Node to be deleted!
        cur->next = temp->next;
        delete temp;
        
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
    stack<int> greaters_index;
    vector<int> answer(temperatures.size());
    for(int i=temperatures.size()-1;i>=0;i--){      
        while (!greaters_index.empty() && temperatures[i]>=temperatures[greaters_index.top()]) {
            greaters_index.pop();
        }

        if(greaters_index.empty())
            answer[i] = 0;
        else 
            answer[i] = greaters_index.top()-i;

        greaters_index.push(i);
    }
    return answer;
}

vector<int> next_greater_num(vector<int>& temperatures) 
{
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
// bool isHigher(char op1, char op2)
// {
//     // return true if op1 has higher precedence to op2
//     if(op1 == '*' || op1 == '/' )
//         if(op2 == '-' || op2 == '+' )
//             return true;
    
//     return false;
// }

int OpOrder(char op)
{
    if( op=='^' )
        return 3;
    else if ( op=='*'|| op=='/')
        return 2;
    else if ( op=='+'|| op=='-')
        return 1;
    else return 0;
}
// https://practice.geeksforgeeks.org/problems/infix-to-postfix-1587115620/1?category%5B%5D=Stack&category%5B%5D=Stack&page=2&query=category%5B%5DStackpage2category%5B%5DStack
string infixToPostfix(string &infix)
{
    stack<char> operators;
    string postfix;
    for(char c:infix){
        if(isdigit(c) || iswalnum(c)){
            postfix += c;
        }
        else {
            if(c == '(' ) {
                operators.push(c);
            }
            else if(c == ')' ) {
                 while (!operators.empty() ){
                        if(operators.top() != '('){
                            postfix += operators.top();
                            operators.pop();
                        }
                        else {
                            operators.pop();
                            break;
                        }
                }
            }
            else{
                while (!operators.empty() && (OpOrder(c)<=OpOrder(operators.top()))
                     && operators.top() !='(' && c != '^'){
                        postfix += operators.top();
                        operators.pop();
                        
                }
                operators.push(c);
            }
            
        }
    }
    while (!operators.empty()) {
        char c = operators.top();
        postfix += c;
        operators.pop();
    }
    

    return postfix;
}

string infixToPretfix(string &infix)
{
    infix.reserve();
    for(char c:infix) {

    }

}

#include <math.h>
double calc(double a,double b,char op)
{
    if(op == '+')
        return a+b;
    if(op == '-')
        return a-b;
    if(op == '*')
        return a*b;
    if(op == '/')
        return a/b;
    if(op == '^')
        return pow(a,b);

}

double evalaute_postfix(string postfix)
{
    stack<double> stk;
    for (char c:postfix){
        if(isdigit(c)){
            string s = "";
            s += c;
            stk.push(atof(s.c_str()));
        }
        else {
            double b = stk.top(); stk.pop();
            double a = stk.top(); stk.pop();
            double r = calc(a,b,c);
            stk.push(r);
        }
    }
    return stk.top();
}

string removeExpressionBrackets(string str)
{
    
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
    auto next_greaters = next_greater_num(temps);
    for(auto r:next_greaters)
        cout<<r<<", ";
    cout<<endl;

    // --
    StackLL stkll;
	stkll.push(10);
	stkll.push(20);
	stkll.push(30);

	stkll.display();	// 30 20 10
	cout << stkll.peek() << "\n";	// 30

	while (!stkll.empty())
		cout << stkll.pop() << " ";
        
    cout<<endl;
    vector<int> dt = {73,74,75,71,69,72,76,73};
    dt = {30,40,50,60};
    dt = {30,60,90};
    dt = {89,62,70,58,47,47,46,76,100,70};
    for(auto g:dt)
        cout<<g<<", ";
    cout<<endl;
    auto greaters_ = dailyTemperatures(dt);
    for(auto g:greaters_)
        cout<<g<<", ";
    cout<<endl;
    // --------------------------------
    string infix = "1+3*5-8/2";
    // infix = "A+b-((5+2)*3)";
    infix = "4^3^2";
    infix = "5+4^3^2-9";
    infix = "a+b*(c^d-e)^(f+g*h)-i";
    infix = "1+2^3^4*5-6";
    infix = "h^m^q^(7-4)";
    // hw3 p1
    cout<<infixToPostfix(infix)<<endl;
    // hw3 p2
    string postfix = "52/";
    postfix = "12+3+";
    postfix = "123*+";
    postfix = "135*+72/-";
    postfix = "432^^";
    cout<<evalaute_postfix(postfix)<<endl;
    //hw3 p3
    // hw3 p4
    StackLL stkp4;
    stkp4.push(1);stkp4.push(2);stkp4.push(3);stkp4.push(4);stkp4.push(5);
    stkp4.display();
    stkp4.delete_middle();
    stkp4.display();
    return 0;
}

