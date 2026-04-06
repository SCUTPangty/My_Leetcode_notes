#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        int record[26] = {0};

        if(ransomNote.size() > magazine.size()) return false;

        for(int i=0; i< magazine.length(); i++)
        {
            record[magazine[i] - 'a'] ++ ;
        }

        for(int j=0; j< ransomNote.length(); j++)
        {
            record[ransomNote[j] - 'a']--;

            if(record[ransomNote[j] - 'a'] < 0) return false;
        }

        return true;
    }
};

int main()
{
    Solution sol;

    string ransomNote1 = "aa";
    string magazine1 = "aab";

    if(sol.canConstruct(ransomNote1, magazine1))
    {
        cout << "true"<<endl;
    } else {
        cout << "false" << endl;
    }

    return 0;
}