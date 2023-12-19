#include <iostream>
#include <cassert>
#include <string.h>
#include <stack>
#include <queue>
// #include <ostream>

using namespace std;
// https://leetcode.com/problems/reverse-words-in-a-string/
class Solution151 {
public:
    string reverseWords(string s) {
        stack<string> stk;

        queue<char> word;

        for (auto c : s) {
            if (c != ' ')
                word.push(c);
            else {
                if (!word.empty()) {
                    string w = "";
                    while (!word.empty()) {
                        w += word.front();
                        word.pop();
                    }
                    stk.push(w);
                }
            }
        }

        if (!word.empty()) {
            string w = "";
            while (!word.empty()) {
                w += word.front();
                word.pop();
            }
            stk.push(w);
        }

        string res;
        res = stk.top();
        stk.pop();
        
        while (!stk.empty()) {
            res += " ";
            res += stk.top();
            stk.pop();
        }

        return res;
    }
};

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
    int get_top() const {
        return top;
    }
    // hw2 p2
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
    // hw2 p3
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

#define MAX_WORD_SIZE 10 // hw1 p2
string reverse_subwords(string line)
{
    string ret{""};
    Stack<char> word(MAX_WORD_SIZE);
    for (char &c : line) {
        if (c != ' ') {
            word.push(c);
        }
        else {
            while (!word.is_empty()) {       
                ret += string{word.pop()};
            }
            ret += " ";   
        }   
    }

    while (!word.is_empty()) {       
        ret+=string{word.pop()};
    }
    return ret;
}
// hw1 p3
int revers_num(int num)
{
    Stack<int> stk{MAX_WORD_SIZE};
    while (num > 0) {
        stk.push(num % 10);
        num = num / 10;
    }
    int ret = 0;
    int d = 1;
    while (!stk.is_empty()) {
     ret = ret + d * stk.pop();
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
// https://leetcode.com/problems/valid-parentheses/ hw1 p4
bool isValid(string s) 
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
    for (const char &c:s) {
        if (stk.is_empty() || c != stk.peek() )
            stk.push(c);
        else 
            stk.pop();
    }
    string ret (stk.get_top() + 1, ' ' );
    for(int i = ret.size() - 1; i >= 0; i--)
        ret[i] = stk.pop();
    return ret;
}
// hw1 p5
// https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/ 
string removeDuplicates(string s) 
{
    std::stack<char> stk;
    for (const char &c : s) {
        if (stk.empty() || c != stk.top())
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
    while (!stk.empty()) {
        ret = stk.top() + ret;
        stk.pop();
    }
    
    return ret;
}

// hw2 p1
// https://leetcode.com/problems/asteroid-collision/
vector<int> asteroidCollision(vector<int>& asteroids) { 
    std::stack<int> stk;
    std::vector<int> res;
    for (auto a : asteroids) {
        bool do_push = true;
        while (!stk.empty()) {
            if (a < 0 && stk.top() > 0) {
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
    while (!stk.empty()) {
        stk2.push(stk.top());
        stk.pop();
    }
    while (!stk2.empty()) {
        res.push_back(stk2.top());
        stk2.pop();
    }
    
    return res;
}
// hw2 p5
// https://leetcode.com/problems/score-of-parentheses/
int scoreOfParentheses(stack<char> s)
{
    int closeness = 0;
    stack<char> stk;
    if (s.empty()) 
        return 0;
    if (s.size() == 2)
        return  1;

    while (!s.empty()) {
        char c = s.top();
        if ( c==')' )
            closeness++;
        else 
            closeness--;

        stk.push(c);
        s.pop();

        if (closeness == 0) {
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

int scoreOfParentheses(string s) 
{
    stack<char> stk;
    for(char c:s)
        stk.push(c);
    
    return scoreOfParentheses(stk);
}

// hw2 p6
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
        
        while (!greaters.empty() && t > greaters.top()) {
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
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op== '+' || op == '-')
        return 1;
    return 0;
}

// https://practice.geeksforgeeks.org/problems/infix-to-postfix-1587115620/1?category%5B%5D=Stack&category%5B%5D=Stack&page=2&query=category%5B%5DStackpage2category%5B%5DStack
string infixToPostfix(string &infix)
{
    stack<char> operators;
    string postfix;
    for (char c : infix) {
        if (isdigit(c) || iswalnum(c)) {
            postfix += c;
        }
        else {
            if (c == '(' ) {
                operators.push(c);
            }
            else if (c == ')' ) {
                 while (!operators.empty() ){
                    if (operators.top() != '(') {
                        postfix += operators.top();
                        operators.pop();
                    }
                    else {
                        operators.pop(); // pop '('
                        break;
                    }
                }
            }
            else {
                while (!operators.empty() && (OpOrder(c)<=OpOrder(operators.top()))
                    && c != '^'){
                        // there is minor change in code that has been submited !
                        // the condition c != '^' is not needed in geeksforgeeks
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

// https://leetcode.com/problems/basic-calculator/
class Solution224 {
public:
    int OpOrder(char op) {
        if (op == '^')
            return 3;
        if (op == '*' || op == '/')
            return 2;
        if (op== '+' || op == '-')
            return 1;
        return 0;
    }
    vector<string> infixToPostfix(string &infix) {
        stack<char> operators;
        vector<string> postfix;
        string digit = "";
        for (int i = 0; i < (int) infix.size(); i++) {
            char c = infix[i];
            if (c == ' ')
                continue;
            if (isdigit(c)) {
                digit += c;
                if (i == (int) infix.size() - 1 || !isdigit(infix[i + 1])) {
                    postfix.push_back(digit);
                    digit = "";
                }
            }
            else {
                if (c == '(' ) {
                    operators.push(c);
                }
                else if (c == ')' ) {
                    while (!operators.empty() ){
                        if (operators.top() != '(') {
                            string s_ = "";
                            s_ += operators.top();
                            postfix.push_back(s_);
                            operators.pop();
                        }
                        else {
                            operators.pop(); // pop '('
                            break;
                        }
                    }
                }
                else {
                    while (!operators.empty() && (OpOrder(c)<=OpOrder(operators.top())) ) {
                        char c = operators.top();
                        string s_ ;
                        s_ += c;
                        postfix.push_back(s_);
                        operators.pop();
                    }
                    operators.push(c);
                }
            }
        }

        while (!operators.empty()) {
            char c = operators.top();
            string s_ ;
            s_ += c;
            postfix.push_back(s_);
            operators.pop();
        }

        return postfix;
    }

    int calc(int a, int b, string op) {
        if(op == "+")
            return a+b;
        if(op == "-")
            return a-b;
        return 0;
    }
    int calculate(string s) {
        vector<string> postfix = infixToPostfix(s);
        stack<int> stk;
        if (postfix[0] == "-")
            stk.push(0);
        for (string c : postfix){
            if (c == "+" || c == "-") {
                int b = stk.top(); stk.pop();
                int a = stk.top(); stk.pop();
                int r = calc(a, b, c);
                stk.push(r);
            }
            else {
                stk.push(atoi(c.c_str()));
            }
        }
        return stk.top();
    }
};

// https://leetcode.com/problems/parsing-a-boolean-expression/
class Solution1106 {
public:
    bool parseBoolExpr(string expression) {
        
    }
};

char getSign(char a,char b)
{
    return a == b ? '+' : '-';
}
// hw3 p5
string removeExpressionBrackets(string str)
{
    string res = "";
    stack<char> prantesis;
    stack<char> sign_of_prantesis;
    stack<char> ops;
    sign_of_prantesis.push('+');
    ops.push('+');
    for(char c:str){
        if(isdigit(c))
            res += c;
        else if(c == '('){
            if(ops.top() == '-'){
                prantesis.push(c);                
                sign_of_prantesis.push(getSign(ops.top(),sign_of_prantesis.top()));// check for empty stack
            }
        }
        else if(c == ')'){
            prantesis.pop();                
            sign_of_prantesis.pop();
        }
        else {// c is +-
            ops.push(c);
            res += getSign(sign_of_prantesis.top(),c);
        }
    }
    return res;
}

int main() 
{
    Solution224 s224;
    cout << s224.calculate("2-1 + 2") << endl;

/* 
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
    // hw3 p3
    // hw3 p4
    StackLL stkp4;
    stkp4.push(1);stkp4.push(2);stkp4.push(3);stkp4.push(4);stkp4.push(5);
    stkp4.display();
    stkp4.delete_middle();
    stkp4.display();
    // hw 3 p5
    string expr;
    expr = "1+2-3-4+5-6-7+8";
    expr = "9-(2+3)";
    expr = "9-(2-3)";
    expr = "9+(2-3)";
    expr = "1-(2-3-(4+5))-6-(7-8)";
    expr = "1-(2-3-(4+5)+6-7)";
    expr = "1-(2-3-(4+5-(6-7)))";
    cout<<removeExpressionBrackets(expr)<<endl; */
    return 0;
}

