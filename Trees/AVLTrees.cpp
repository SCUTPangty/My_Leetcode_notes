#include <iostream>
#include <cassert>
using namespace std;

#define LH 1
#define EH 0
#define RH -1

typedef struct Node
{
    int data;
    Node *left;
    Node *right;
    int bf;//平衡因子
}BiNode, *BiTree;

BiTree LeftRotate(BiTree T)
{//左旋
    BiTree R = T->right;//记录T节点右子树
    T->right = R->left;//将右子树的左子树插入到T的右子树上
    R->left = T;//把节点T连到R的左子树上
    T = R;//完成旋转后，R成为新的根节点
    return T;
}

BiTree RightRotate(BiTree T)
{//右旋
    BiTree L = T->left;//记录T节点左子树
    T->left = L->right;//将左子树的右子树插入到T的左子树上
    L->right = T;//把节点T连到L的右子树上
    T = L;//完成旋转后，L成为新的根节点

    return T;
}

//处理左子树的节点插入情况，使其平衡
BiTree LeftBalance(BiTree T)
{
    BiTree L,R;
    L = T->left;
    switch(L->bf)
    {//通过平衡状态决定怎么旋转
        case LH://若为LL
        {
            T->bf = L->bf = EH;
            T = RightRotate(T);//右旋
            break;
        }
        case RH://若为LR
        {
            R = L->right;//记录左子树的右子树
            switch(R->bf)
            {//更新平衡状态
                case LH:
                {
                    T->bf = RH;
                    L->bf = EH;
                    break;
                } 
                case EH:
                {
                    T->bf = L->bf = EH;
                    break;
                }
                case RH:
                {
                    T->bf = EH;
                    L->bf = LH;
                    break;
                }
            }
            R->bf = EH;
            T->left = LeftRotate(T->left);
            T = RightRotate(T);
            break;
        }
    }
    return T;
}

//处理右子树的节点插入情况，使其平衡
BiTree RightBalance(BiTree T)
{
    BiTree L,R;
    R = T->right;
    switch(R->bf)
    {
        case RH:
        {//右子树的右子树插入节点
            T->bf = R->bf = EH;
            T = LeftRotate(T);//进行左旋
            break;
        }
        case LH://若右子树的左子树插入节点
        {
            L = R->left;
            switch(L->bf)
            {
                case LH:
                {
                    T->bf = EH;
                    R->bf = RH;
                    break;
                }
                case EH:
                {
                    T->bf = R->bf = EH;
                    break;
                }
                case RH:
                {
                    T->bf = LH;
                    R->bf = EH;
                    break;
                }
            }
            L->bf = EH;
            T->right = RightRotate(T->right);//对右子树右旋
            T = LeftRotate(T);//对树左旋
            break;
        }
    }
    return T;
}

//平衡二叉树的节点插入与调整
BiTree InsertAVL(BiTree T, int value)
{
    if(T == nullptr)
    {
        T = new BiNode;
        T->bf = EH;//创建新节点的初始平衡因子为0
        T->data = value;
        T->left = nullptr;
        T->right = nullptr;
    }
     else 
    {
        assert(value != T->data);//如果存在两个相同值的节点则报错
        if(value < T->data)
        {
            T->left = InsertAVL(T->left, value);
            switch(T->bf)
            {
                case LH: T = LeftBalance(T); break;
                case EH: T->bf = LH; break;
                case RH: T = RightBalance(T); break;
            }
        } 
        else if (value > T->data)
        {
            T->right = InsertAVL(T->right,value);
            switch(T->bf)
            {
                case LH: T->bf=EH;break;
                case EH: T->bf=RH;break;
                case RH: T = RightBalance(T);break;
            }
        }
    }
    return T;
}

//前序遍历AVLTree
void AVL_PreOrder(BiTree T)
{
    if(T == nullptr) return;

    cout << T->data<<" ";
    AVL_PreOrder(T->left);
    AVL_PreOrder(T->right);
}

//后序遍历AVLTree
void AVL_InOrder(BiTree T)
{
    if(T == nullptr) return;
    AVL_InOrder(T->left);
    cout << T->data<<" ";
    
    AVL_InOrder(T->right);
}

int main()
{
    int N = 100;
    int n,i,val[N];
    BiTree T = nullptr;
    cin >> n;
    for(i=1; i<=n ;i++)
    {
        cin >> val[i];
        T = InsertAVL(T,val[i]);
    }

    cout << endl << "PreOrder traversal:" <<endl;
    AVL_PreOrder(T);
    cout << endl << "InOrder traversal:" <<endl;
    AVL_InOrder(T);
    return 0;
}