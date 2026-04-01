#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> res(n,0);
        stack<int> index;

        for(int i=0; i< n; i++)
        {//当栈不为空 且 今天的温度 > 栈顶那天的温度
            while(!index.empty() && temperatures[i] > temperatures[index.top()])
            {
                int prev_index = index.top();//获取还在等待的下标
                index.pop();//弹出该下标
                res[prev_index] = i - prev_index;//计算等了几天
            }
            index.push(i);//每次循环都把今天的下标放进去，寻找他未来的更高温
        }

        return res;
    }
};

int main()
{
    vector<int> temperatures;
    int temp;
    cout << "请输入温度序列（输入 -1 结束）：";
    while (cin >> temp && temp != -1) {
        temperatures.push_back(temp);
    }

    // 2. 调用 Solution 类的 dailyTemperatures 方法
    Solution sol;
    vector<int> result = sol.dailyTemperatures(temperatures);

    // 3. 输出结果（每个温度对应的等待天数）
    cout << "每日温度对应的等待天数：";
    for (int days : result) {
        cout << days << " ";
    }
    cout << endl;

    return 0;
}