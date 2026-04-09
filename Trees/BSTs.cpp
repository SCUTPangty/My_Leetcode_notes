#include <iostream>
#include <vector>
#include<unordered_map>
#include <algorithm>
#include <queue>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x, TreeNode *l = nullptr, TreeNode *r = nullptr) 
        : val(x), left(l), right(r) {}
};

class Solution1 
{
public:
    int maxCount = 0;
    int count = 0;
    TreeNode *pre = nullptr;
    vector<int> result;

    void searchBST1(TreeNode *cur) {
        if (cur == nullptr) return;

        searchBST1(cur->left); // 左

        // 中：开始处理当前节点逻辑
        if (pre == nullptr) {
            count = 1; // 第一个节点
        } else if (pre->val == cur->val) {
            count++;   // 与前一个节点数值相同
        } else {
            count = 1; // 与前一个节点数值不同，重置计数
        }

        pre = cur; // 更新指针

        if (count == maxCount) {
            result.push_back(cur->val);
        }

        if (count > maxCount) {
            maxCount = count;
            result.clear(); // 发现频率更高的，清空之前的失效结果
            result.push_back(cur->val);
        }

        searchBST1(cur->right); // 右
    }

    vector<int> findMode(TreeNode *root)
    {
        count = 0;
        maxCount = 0;
        pre = nullptr;
        result.clear();

        searchBST1(root);
        return result;
    }
};

class Solution2 {
public:

    // vector<int> vec;
    // void traversal(TreeNode *root)
    // {
    //     if(root == nullptr) return;
    //     traversal(root->left);
    //     vec.push_back(root->val);
    //     traversal(root->right);
    // }

    int result = INT32_MAX;
    TreeNode *pre = nullptr;

    void traversal(TreeNode *cur)
    {
        if(cur == nullptr) return;
        traversal(cur->left);
        if(pre != nullptr)
        {
            result = min(result, cur->val - pre->val);
        }

        pre = cur;
        traversal(cur->right);
    }

    int getMinimumDifference(TreeNode* root)
     {
        // vec.clear();
        // traversal(root);
        // if(vec.size() < 2)return 0;
        // int result = INT_MAX;
        // for(int i=1; i< vec.size(); i++)
        // {
        //     result = min(result, vec[i] - vec[i-1]);
        // }
        // return result;
        traversal(root);
        return result;
    }
};

TreeNode *insertBST(TreeNode *root, int val)
{
    if(root == nullptr){
        return new TreeNode(val);
    }
    if(val < root->val)
    {
        root->left = insertBST(root->left, val);
    } else {
        root->right = insertBST(root->right, val);
    }
    return root;
}

void printTree(TreeNode *root)
{
    if(!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty())
    {
        TreeNode *node = q.front();
        q.pop();
        if(node)
        {
            cout << node->val << " ";
            q.push(node->left);
            q.push(node->right);
        }else {
            cout << "# ";//代表空节点
        }
    }
    cout << endl;
}

int main()
{
    Solution1 sol1;
    Solution2 sol2;

    TreeNode *root1 =nullptr;
    TreeNode *root2 = nullptr;

    vector<int> nums1 = {3,2,3,1,2,3};
    vector<int> nums2 = {4,2,6,1,3};

    for(int x : nums1)
    {
        root1 = insertBST(root1,x);
    }
    for(int x : nums2)
    {
        root2 = insertBST(root2,x);
    }

    printTree(root1);
    vector<int> modes = sol1.findMode(root1);
    cout << "Modes in this BST: ";
    for (int m : modes) {
        cout << m << " ";
    }
    cout << endl;

    printTree(root2);
    int result = sol2.getMinimumDifference(root2);
    cout << "The minimum difference in this BST is: ";
    cout << result << endl;

    return 0;

}