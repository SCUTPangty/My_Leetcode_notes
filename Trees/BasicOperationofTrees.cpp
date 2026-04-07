#include <iostream>
#include <queue>
using namespace std;
//遍历tree

struct Node
{
int data;
Node *left;
Node *right;
};

//binary tree 广度优先算法
void LevelOrder(Node *root)
{
    if(root==nullptr) return;
    queue<Node*> Q;
    Q.push(root);
    while(!Q.empty())
    {
        Node *current = Q.front();
        cout<<current->data<<" ";//从左到右实现，自己画图理解一下
        if(current->left != nullptr) Q.push(current->left);
        if(current->right != nullptr) Q.push(current->right);
        Q.pop();
    }
}

//深度优先 前序遍历DLR
void PreOrder(Node *root)
{
    if(root==nullptr) return ;
    cout<<root->data<<" ";
    //自己画图理解一下
    PreOrder(root->left);
    PreOrder(root->right);
}

//深度优先 中序遍历LDR
void InOrder(Node *root)
{
    if(root==nullptr) return ;
    InOrder(root->left);
    cout<<root->data<<" ";
    //自己画图理解一下
    InOrder(root->right);
}

//深度优先 中序遍历LRD
void PostOrder(Node *root)
{
    if(root==nullptr) return ;
    PostOrder(root->left);
    //自己画图理解一下
    PostOrder(root->right);
    cout<<root->data<<" ";
}

Node* GetNewNode(int data)
{//创建子树
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

Node* Insert(Node* root, int data)
{
    if(root == nullptr)
    {
        root = GetNewNode(data);
    }
    else if(data <= root->data)
    {
        root->left = Insert(root->left,data);
    } else {
            root->right = Insert(root->right,data);
    }
    return root;
}

bool Search(Node* root, int data)
{
    if(root == nullptr) return false;
    else if (root->data == data) return true;
    else if (data<=root->data) return Search(root->left, data);
    else return Search(root->right,data);
}

int FindMin(Node* root)
{
    //根据二叉树的规则，最小的元素出现在最左边
    if(root == nullptr)
    {
        cout<<"Tree is empty"<<endl;
        return -1;
    }
    while(root->left != nullptr)
    {
        root = root->left;
    }
    return root->data;
}

int FindMax(Node* root)
{
    //根据二叉树的规则，最大的元素出现在最右边
    if(root == nullptr)
    {
        cout<<"Tree is empty"<<endl;
        return -1;
    }
    else if (root->right == nullptr)
    {
       return root->data;
    }
    return FindMax(root->right);
}

int FindHighestHeight(Node *root)
{
    if(root==nullptr) return 0;
    int left = 0, right = 0;
    left = FindHighestHeight(root->left);
    right = FindHighestHeight(root->right);

    return max(left,right)+1;
}

int FindLowestHeight(Node *node)
{
    if (node == NULL) return 0;
    int leftDepth = FindLowestHeight(node->left);           // 左
    int rightDepth = FindLowestHeight(node->right);         // 右
                                                    // 中
    // 当一个左子树为空，右不为空，这时并不是最低点
    if (node->left == NULL && node->right != NULL) { 
        return 1 + rightDepth;
    }   
    // 当一个右子树为空，左不为空，这时并不是最低点
    if (node->left != NULL && node->right == NULL) { 
        return 1 + leftDepth;
    }
    int result = 1 + min(leftDepth, rightDepth);
    return result;
}

Node *InvertTree(Node *root)
{
    if(root == nullptr) return 0;
    Node *left = InvertTree(root->left);
    Node *right = InvertTree(root->right);
    root->left = right;
    root->right = left;
    return root;
}

bool hasPathSum(Node* root, int targetSum) {
        if(root == nullptr) return false;

        if(root->left==nullptr && root->right==nullptr)
        {//利用逆向思维解题
            return targetSum == root->data;
        }

        return hasPathSum(root->left, targetSum - root->data) || hasPathSum(root->right, targetSum - root->data);
        
}

bool Comparison(Node* node, long long minVal, long long maxVal) {
    // 1. 空节点也是合法的 BST
    if (node == nullptr) return true;
    // 2. 检查当前节点是否在允许的区间内 (minVal, maxVal)
    if (node->data <= minVal || node->data >= maxVal) {
        return false;
    }
    // 3. 递归检查左右子树
    // 左子树的所有节点必须 < 当前节点值 (更新 maxVal)
    // 右子树的所有节点必须 > 当前节点值 (更新 minVal)
    return Comparison(node->left, minVal, node->data) && 
           Comparison(node->right, node->data, maxVal);
}

bool isValidBST(Node* root) {
    // 初始区间设为负无穷到正无穷
    return Comparison(root, __LONG_LONG_MAX__, __LONG_LONG_MAX__);
}

Node* lowestCommonAncestor(Node* root, Node* p, Node* q)
{

    if(root == nullptr || root==p || root == q) return  root;

    Node *left = lowestCommonAncestor(root->left,p,q);
    Node *right = lowestCommonAncestor(root->right,p,q);

    if(left == nullptr && right == nullptr) return nullptr;//没找到
    if(left == nullptr) return right;//左边没有，右边有
    if(right == nullptr) return left;//右边没有，左边有
    return root;//两边各有一个
}

int findBottomLeftValue(Node* root) 
{
    queue<Node*>que;
    if(root != nullptr) que.push(root);
    int result = 0;

    while(!que.empty())
    {
        int size = que.size();
        for(int i=0; i< size ;i++)
        {//记录每行的节点，画图理解一下
            Node *node = que.front();
            que.pop();//que只保存每行第一个值
            //记录最后一行第一个元素
            if(i == 0) result = node->data;
            if(node->left) que.push(node->left);
            if(node->right) que.push(node->right);
        }
    }
    return result;//爱来自代码随想录
}

int sumOfLeftLeaves(Node* root) 
{
    if(root == nullptr) return 0;
    if(root->left == nullptr && root->right == nullptr) return 0;

    int leftValue = sumOfLeftLeaves(root->left);//左
    if(root->left && !root->left->left && !root->left->right)
    {
        leftValue = root->left->data;
    }
    int rightValue = sumOfLeftLeaves(root->right);//右
    //求的是左叶子节点的和，与右叶子节点无关，有左孩子自然会加上的

    int sum = leftValue + rightValue;//中
    return sum;//爱来自代码随想录
}

void traversal(Node *cur, vector<int>& path, vector<string>& result)
{//爱来自代码随想录
    path.push_back(cur->data);//中为什么写在这里，因为最后一个节点也要加入path中
    // 这才到了叶子节点
    if(cur->left == nullptr && cur->right == nullptr)//遇见叶子节点
    {
        string sPath;//各种操作，只为博AC一绿
        for(int i=0; i<path.size()-1; i++)
        {//path里的路径转为string
            sPath += to_string(path[i]);
            sPath += "->";
        }//要写箭头，故loop里不能写最后一个节点
        //记录最后一个节点(叶子)
        sPath += to_string(path[path.size() -1]);
        result.push_back(sPath);//收集整个路径
        return;
    } 
    if(cur->left)
    {//左
        traversal(cur->left, path, result);
        path.pop_back();//回溯
    }
    if(cur->right)
    {//右
        traversal(cur->right, path, result);
        path.pop_back();//回溯
    }
}

vector<string> binaryTreePaths(Node* root)
{//爱来自代码随想录
    vector<string> result;
    vector<int> path;
    if(root == nullptr) return result;
    traversal(root, path, result);
    return result;
}

int getBalancedHeight (Node *node)
{
    if(node == nullptr) return 0;

    int leftHeight = getBalancedHeight(node->left);//左
    if(leftHeight == -1) return -1;
    int rightHeight = getBalancedHeight(node->right);//右
    if(rightHeight == -1) return -1;
    //中
    int result;
    if (abs(leftHeight - rightHeight) > 1) {  // 中
        result = -1;
    } else {
        // 以当前节点为根节点的树的最大高度
        result = 1 + max(leftHeight, rightHeight);
    }
    return result;
}

bool isBalanced(Node* root) {
    return getBalancedHeight(root) == -1 ? false : true;
}

int main()
{
    Node *root= NULL;// to store address of root node
    root = Insert(root,15);
    root = Insert(root,10);
    root = Insert(root,20);
    root = Insert(root,25);
    root = Insert(root,8);
    root = Insert(root,12);
    // int number;
    // cin>>number;
    // if(Search(root,number)==true) cout <<"Found"<<endl;
    // else cout << "NO"<<endl;
    // cout<<FindMax(root)<<" "<<FindMin(root)<<endl;
    PreOrder(root);
    cout << endl;
    InOrder(root);
    cout << endl;
    PostOrder(root);
    cout << endl;
    return 0;
} 