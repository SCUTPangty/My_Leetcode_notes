#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        //一切的根本，排序
        for(int i=0; i < nums.size(); i++)
        {
            //排序后，如果第一个元素大于0，则此时再怎么凑，都无法凑出三和为0
            if(nums[i] > 0) return result;
            //遇见重复就跳过本轮不操作
            //不写i>0会漏掉-1,-1,2这种
            if(i > 0 && nums[i] == nums[i-1]) continue;

            int left = i + 1;
            int right = nums.size()-1;
            while(right > left)
            {
                if(nums[i] + nums[left] + nums[right] > 0) right--;
                else if (nums[i] + nums[left] + nums[right] < 0) left++;
                else {
                    result.push_back(vector<int>{nums[i],nums[left],nums[right]});
                    //去重逻辑
                    while(right > left && nums[right] == nums[right - 1]) right--;
                    while (right > left && nums[left] == nums[left + 1]) left++;
                    //找到答案时，双指针同时收缩
                    right--;
                    left++;
                }
            }
        }
        return result;
    }
};

int main()
{
    vector<int> num = {-1,0,1,2,-1,-4};
    Solution abc;
    vector<vector<int>> res = abc.threeSum(num);
    for(int i=0; i < res.size(); i++)
    {
        for(int j=0; j < res[i].size();j++) cout << res[i][j]<<" ";
        cout << endl;
    }
    return 0;
}