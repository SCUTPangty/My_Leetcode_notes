#include <iostream>
#include <stack>
#include <climits>
using namespace std;

class MinStack{
private:
    stack<int> min_stack;
    stack <int> stk;

public:
    MinStack() 
    {
        min_stack.push(INT_MAX);
    }

    void push(int x)
    {
        stk.push(x);
        if(x <= min_stack.top())
        {
            min_stack.push(x);
        }
    }

    void pop()
    {
        if(!stk.empty())
        {
            stk.pop();
            min_stack.pop();
        }
    }

    int top()
    {
        if(!stk.empty())
        {
            return stk.top();
        }
    }
};