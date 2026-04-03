#include <iostream>
#include <stack>
#include <string>
#include <sstream>
using namespace std;

//postfix计算法
//想实现二位计算，可以，但很怪
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

int EvaluatePostfix(string s)
{
    stack<char>S;
    int a=0, b=0;
    int res = 0;
    for(int i=0; i<s.size() ;i++)
    {
        if(s[i] >='0' && s[i]<='9')
        {
            S.push(s[i]-'0');
        } else if(s[i] == '+'||s[i] == '-'||s[i]=='*'||s[i] == '/'){
            a = S.top();
            S.pop();
            b = S.top();
            S.pop();
            res = Perform(s[i],a,b);
            S.push(res);
        }
    }
    return S.top();
}

int main()
{
    string postfix = "23*54*+9-";
    cout <<EvaluatePostfix(postfix)<<endl;
    return 0;
}