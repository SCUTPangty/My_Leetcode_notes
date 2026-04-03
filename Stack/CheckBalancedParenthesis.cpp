#include <iostream>
#include <stack>
#include <string>
#include<cstring>
using namespace std;

//栈实现括号配对
bool CheckBalancedParenthesis(int len,string s)
{
    stack<char> S;
    for(int i=0; i<len ;i++)
    {
        if(s[i] == '(' || s[i]=='{' || s[i]=='[')
        {
            S.push(s[i]);
        } else if (s[i] == ')' || s[i]=='}' || s[i]==']'){
            if(S.size()==0)
            {
                return false;
            } else {
                S.pop();
            }
        }
    }
    return S.empty();
}

int main()
{

    string n;
    getline(cin,n);
    int len = n.size();

    cout << CheckBalancedParenthesis(len,n);
    return 0;
}