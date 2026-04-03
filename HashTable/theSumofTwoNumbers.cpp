#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> hashtable;
        //哈希表的空间换时间
        for(int i=0; i<nums.size() ;i++)
        {
            auto it = hashtable.find(target - nums[i]);
            if(it != hashtable.end())
            {
                return {it->second, i};
            }
            //哈希表特有的key和value长得一样
            hashtable[nums[i]] = i;
        }
        return {};
    }
};

int main()
{
    Solution sol;
    vector<int> nums1 = {2,7,11,15};
    int target1 = 9;
    vector<int> res1 = sol.twoSum(nums1, target1);
    cout << "Test 1: " << res1[0] << ", " << res1[1] << endl;

    vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    vector<int> res2 = sol.twoSum(nums2, target2);
    cout << "Test 2: " << res2[0] << ", " << res2[1] << endl;
    return 0;

}