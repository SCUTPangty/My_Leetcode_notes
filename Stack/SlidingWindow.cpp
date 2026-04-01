#include <iostream>
#include <deque>
#include <vector>
using namespace std;

class Solution {
public://采用单调队列一遍过，时间复杂度仅O(n)
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque <int> dq;//获取下标
        vector<int> res;

        for(int i=0; i < (int)nums.size() ;i++)
        {//注意！我们从deque的队尾开始视为i，所以我们的i一直处在队尾！！！

            //掐头：判断deque的开头下标是否在窗口[i-k+1, i]里，不在则弹出
            if(!dq.empty() && dq.front() == i-k)
            {
                dq.pop_front();
            }

            //去尾：若i的值比队尾的值更大，则队尾的值必定无法比i大，可以直接踢走
            while(!dq.empty() && nums[i] > nums[dq.back()])
            {
                dq.pop_back();
            }

            //掐头去尾就可以正常入队了
            dq.push_back(i);

            //取值：获取deque中的最大值
            if(i >= k-1)
            {
                res.push_back(nums[dq.front()]);
            }
        }
        return res;
    }
};

int main()
{
    vector<int> nums;
    int k;
    int temp;
    cout << "请输入数据（输入 666666 结束）：";
    while (cin >> temp && temp != 666666) {
        nums.push_back(temp);
    }

    cout << "请输入滑动窗口k的大小：";
    cin >> k;

    Solution sol;
    vector<int> result = sol.maxSlidingWindow(nums, k);

    cout <<"滑动窗口的最大值序列：";
    for(int max_val : result)
    {
        cout << max_val <<" ";
    }
    cout << endl;
    return 0;
}