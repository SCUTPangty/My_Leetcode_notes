#include <iostream>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    int getSum(int n)
    {
        int sum = 0;
        while(n!=0)
        {
            sum += (n%10) * (n%10);
            n /= 10;
        }
        return sum;
    }

    bool isHappy(int n)
    {
        unordered_set<int> set;
        while(1)
        {
            int sum = getSum(n);
            if(sum == 1) return true;

            if(set.find(sum) != set.end()) return false;
            //出现循环
            else set.insert(sum);

            n = sum;
        }
    }
};

int main()
{
    int n = 19;
    Solution res;
    if(res.isHappy(n)) cout << "true"<<endl;
    else cout << "false"<<endl;
    
    return 0;
}