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

int FindHeight(Node *root)
{
    if(root==nullptr) return 0;
    int left = 0, right = 0;
    left = FindHeight(root->left);
    right = FindHeight(root->right);

    return max(left,right)+1;
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

Node* lowestCommonAncestor(Node* root, Node* p, Node* q) {

    if(root == nullptr || root==p || root == q) return  root;

    Node *left = lowestCommonAncestor(root->left,p,q);
    Node *right = lowestCommonAncestor(root->right,p,q);

    if(left == nullptr && right == nullptr) return nullptr;//没找到
    if(left == nullptr) return right;//左边没有，右边有
    if(right == nullptr) return left;//右边没有，左边有
    return root;//两边各有一个
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