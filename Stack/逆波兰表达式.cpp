#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        for(auto &token : tokens)
        {
            char c = token[0];
            if(token.size() > 1 || isdigit(c))
            {
                stk.push(stoi(token));
                continue;
            }

            int x = stk.top();
            stk.pop();
            if(c == '+')
            {
                stk.top() += x;
            } else if (c == '-')
            {
                stk.top() -= x;
            } else if (c == '*')
            {
                stk.top() *= x;
            } else 
            {
                stk.top() /= x;
            }
        }
        return stk.top();
    }
};

int main() {
    Solution solution;

    vector<string> tokens1 = {"2", "1", "+", "3", "*"};
    cout << "Result 1: " << solution.evalRPN(tokens1) << endl;

    
    return 0;
}