#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2){
        unordered_set<int> res;
        int hash[1005] = {0};
        for(int i=0; i < nums1.size(); i++)
        {
            int num = nums1[i];
            hash[num] = 1;
        }

        for(int i=0; i < nums2.size(); i++)
        {
            int num = nums2[i];
            if(hash[num] == 1)
            {
                res.insert(num);
            }
        }
        return vector<int>(res.begin(), res.end());
    }
};

int main()
{
    vector<int> num1 = {4,9,5};
    vector<int> num2 = {9,4,9,8,4};

    Solution result;
    vector<int> num_res = result.intersection(num1,num2);

    for(int i=0; i < num_res.size();i++)
    {
        cout << num_res[i]<<endl;
    }
    return 0;
}