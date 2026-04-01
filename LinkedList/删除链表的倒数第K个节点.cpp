#include <iostream>
using namespace std;

struct Node {
int data;
Node *next;

Node (int dta = 0, Node *nxt = nullptr) : data(dta), next(nxt){}
};

Node *removeNthFromEnd(Node *head, int n)
{
    Node *dummy = new Node(0,head);//虚拟头节点
    Node *fast = dummy;
    Node *slow = dummy;

    for(int i=0; i<n ;i++)
    {//快指针先走N步
        fast = fast->next;
    }

    while(fast->next != nullptr)
    {
        fast = fast->next;
        slow = slow->next;
    }

    Node *temp = slow->next;
    slow->next = slow->next->next;
    delete temp;//好习惯之随手删除

    Node *result = dummy->next;
    delete dummy;
    return result;
}

Node *reverseBetween(Node *head, int left, int right)
{//伪头插法，一次遍历即可实现
    Node *dummy = new Node(0,head);
    Node *pre = dummy;

    for(int i=0; i<left-1 ;i++) pre = pre->next;
    Node *cur = pre->next;
    Node *temp;

    for(int i=0; i<right - left ;i++)
    {
        temp = cur->next;
        cur->next = temp->next;
        temp->next = pre->next;
        pre->next = temp;
    }

    Node *result = dummy->next;
    delete dummy;
    return result;
}

Node *Insert(Node *head, int data)
{
    Node *temp = new Node();
    temp->data = data;
    temp->next = nullptr;
    if(head==nullptr)
    {
        head = temp;
    } else {
        Node *temp1 = head;
        while(temp1->next != nullptr){
            temp1 = temp1->next;
        }
        temp1->next = temp;
    }
    return head;
}

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

int main()
{
    Node *head = nullptr;
    head = Insert(head,1);
    head = Insert(head,2);
    head = Insert(head,3);
    head = Insert(head,4);
    head = Insert(head,5);

    // head = removeNthFromEnd(head,2);
    head = reverseBetween(head,2,4);
    Print(head);
    return 0;
}