#include <iostream>
#include <stack>
#include <string>
#include <sstream>
using namespace std;

//infix转postfix
int Perform(char op,int a,int b)
{
    switch(op){
        case '+':
        return a+b;
        break;
        case '-':
        return a-b;
        break;
        case '*':
        return a*b;
        break;
        case '/':
        return a/b;
        break;
    }
    return 0;
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

bool HasHigherPrec(char top, char next)
{
    return (precedence(top) >= precedence(next));
}

// bool IsOpeningParentheses(char op)
// {
//     if(op == '['||op==']'||op=='{'||op=='}')
// }

string InfixToPostfix(string s)
{
    stack<char>S;
    string res;
    for(int i=0; i<s.size(); i++)
    {
        if(s[i] >='0' && s[i]<='9')
        {
            res = res + s[i];
        } else if(s[i] == '+'||s[i] == '-'||s[i]=='*'||s[i] == '/')
        {
            while(!s.empty()&& HasHigherPrec(S.top(),s[i]))
            {
                res += S.top();
                S.pop();
            }
            S.push(s[i]);
        }
    }
    while(!S.empty())
    {
        res += S.top();
        S.pop();
    }
    return res;
}

int EvaluatePostfix(string postfix) {
    stack<int> S;
    for (int i = 0; i < postfix.size(); i++) {
        if (postfix[i] >= '0' && postfix[i] <= '9') {
            S.push(postfix[i] - '0');
        } else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/') {
            int b = S.top();
            S.pop();
            int a = S.top();
            S.pop();
            int res = Perform(postfix[i], a, b);
            S.push(res);
        }
    }
    return S.top();
}

int main()
{
    string infix;
    cout << "请输入中缀表达式: ";
    getline(cin, infix);
    string postfix = InfixToPostfix(infix);
    cout << "后缀表达式为: " << postfix << endl;
    int result = EvaluatePostfix(postfix);
    cout << "计算结果为: " << result << endl;
    return 0;
}