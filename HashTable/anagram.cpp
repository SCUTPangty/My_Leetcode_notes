#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        int record[26] = {0};
        for(int i=0; i<s.size() ;i++)
        { // 并不需要记住字符a的ASCII，只要求出一个相对数值就可以了
            record[s[i] - 'a']++;
        }

        for(int i=0; i< t.size() ;i++)
        {//t做s的逆操作
            record[t[i] - 'a']--;
        }

        for(int i=0; i < 26 ;i++)
        {
            if(record[i] != 0)
            {//如果record有的元素不是0，则s和t字符串一定有人多了或少了字符
                return false;
            }
        }
        //  record  所有元素都为0，则s和t是字母异位词
        return true;
    }
};

int main()
{
    Solution sol;

    string s1 = "anagram", t1 = "margana";
    cout << "Test 1: " << (sol.isAnagram(s1, t1) ? "True" : "False") << endl;

    string s2 = "rat", t2 = "car";
    cout << "Test 2: " << (sol.isAnagram(s2, t2) ? "True" : "False")<< endl;

    // 测试用例 3 (长度不等)
    string s3 = "a", t3 = "ab";
    cout << "Test 3: " << (sol.isAnagram(s3, t3) ? "True" : "False")<< endl;

    return 0;
}