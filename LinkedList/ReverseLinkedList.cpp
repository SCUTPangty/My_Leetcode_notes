
#include <iostream>
using namespace std;

// 定义链表节点结构
struct Node {
    int data;
    struct Node* next;
};

// 尾插法插入节点函数
Node* Insert(Node* head, int data) {
    Node* temp = new Node();
    temp->data = data;
    temp->next = NULL;
    if (head == NULL) {
        head = temp;
    }
    else {
        Node* temp1 = head;
        while (temp1->next != NULL) {
            temp1 = temp1->next;
        }
        temp1->next = temp;
    }
    return head;
}

// 递归反转链表函数
Node* Reverse(Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    Node* newHead = Reverse(head->next);
    head->next->next = head;
    head->next = NULL;
    return newHead;
}

// 打印链表函数
void Print(Node *head)
{
    cout <<"List is:"<<endl;
    while(head != NULL)
    {
        cout << head->data<<" ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Node* head = NULL;
    head = Insert(head, 34);
    head = Insert(head, 76);
    head = Insert(head, 22);
    head = Insert(head, 89);

    head = Reverse(head);
    Print(head);

    return 0;
}

// #include <iostream>
// using namespace std;

// //递归反转链表，这回是正牌了
// struct Node{
//     int data;
//     struct Node *next;
// };

// struct Node *head;

// void Reverse(Node* p)
// {
//     if(p->next == nullptr)
//     {//防止无限进行递归
//         head = p;
//         return;
//     }//到最后一个节点，立刻回到倒数第二个节点
//     Reverse(p->next);
//     //注意！这里p在倒数第二个节点
//     struct Node *temp = p->next;
//     temp->next = p;
//     p->next = nullptr;
//     //上面三行可以写成p->next->next = p，但是太复杂了
// }

// Node* Insert(Node *head,int data)
// {//尾插法
//     Node *temp = new Node();
//     temp->data = data;
//     temp->next = NULL;
//     if(head == NULL)head = temp;
//     else {
//         Node *temp1 = head;
//         while(temp1->next != NULL) temp1 = temp1->next;
//         temp1->next = temp;
//     }
//     return head;//改完记得改函数的属性啊
// }

// void Print(Node *p)
// {
//     if(p==NULL)return ;
//     cout << p->data<<" ";
//     Print(p->next);
// }

// int main()
// {
//     head = Insert(head,34);
//     head = Insert(head,76);
//     head = Insert(head,22);
//     head = Insert(head,89);

//     Reverse(head);
//     Print(head);

//     return 0;
// }
