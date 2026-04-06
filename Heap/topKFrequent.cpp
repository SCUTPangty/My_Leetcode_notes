#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:

    //构建小顶堆
    class Comparison
    {
    public:
        bool operator()(const pair<int,int>& left, const pair<int,int>& right)
        {//重载运算符，使函数能调用类对象
            return left.second > right.second;
        }
    };

    vector<int> topKFrequent(vector<int>& nums, int k) {
        //统计元素出现的频率
        unordered_map<int,int> map;
        for(int i=0; i< nums.size(); i++)
        {
            map[nums[i]]++;
        }

        //对频率排序，使用小顶堆，且其大小为k
        //priority_queue<数据类型, 容器类型, 比较方式>
        priority_queue<pair<int,int>, vector<pair<int,int>>,Comparison> pri_que;

        //用固定大小为K的小顶堆，扫描所有频率的数值
        for(unordered_map<int,int>::iterator it = map.begin(); it != map.end(); it++)
        {
            pri_que.push(*it);
            //如果堆的大小大于k，则队列弹出，保证大小一直为k
            if(pri_que.size() > k) pri_que.pop();
        }

        //找出前K个高频元素，因为小顶堆先弹出的是最小的，所以倒叙输出到数组
        vector<int> result(k);
        for(int i = k - 1 ; i >= 0; i--)
        {
            result[i] = pri_que.top().first;
            pri_que.pop();
        }

        return result;
    }
};

int main()
{
    Solution sol;

    vector<int> nums1 = {1,1,1,2,2,3};
    int k1 = 2;
    vector<int> res1 = sol.topKFrequent(nums1, k1);

    cout <<"Test Case 1: ";
    for (int num : res1) cout << num << " ";
    cout << endl;

    return 0;
}