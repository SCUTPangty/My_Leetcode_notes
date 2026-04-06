#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        //查找元素a+b是否出现过，使用哈希表
        unordered_map<int,int> umap;//key:a+b的数值，value:a+b数值出现的次数
        // 遍历大A和大B数组，统计两个数组元素之和，和出现的次数，放到map中
        for(int a : A){
            for(int b : B)
            {
                umap[a + b]++;
            }
        }

        int count = 0;// 统计a+b+c+d = 0 出现的次数
        // 再遍历大C和大D数组，找到如果 0-(c+d) 在map中出现过的话，就把map中key对应的value也就是出现次数统计出来。
        for(int c : C)
        {
            for(int d : D)
            {
                if( umap.find(0 - (c + d)) != umap.end())
                {
                    count += umap[0 - (c + d)];
                }
            }
        }

        return count;//爱来自代码随想录
    }
};

int main()
{
    Solution sol;

    vector<int> nums1 = {1,2};
    vector<int> nums2 = {-2,-1};
    vector<int> nums3 = {-1,2};
    vector<int> nums4 = {0,2};

    int result1 = sol.fourSumCount(nums1,nums2,nums3,nums4);
    cout << result1 <<endl;

    return 0;
}