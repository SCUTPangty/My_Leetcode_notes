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

Node *swapPairs(Node *head)
{
    Node *dummy = new Node(0,head);
    Node *temp = dummy;
    while(temp->next != nullptr && temp->next->next != nullptr)
    {
        Node *n1 = temp->next;
        Node *n2 = temp->next->next;
        temp->next = n2;
        n1->next = n2->next;
        //n1先存储n2->next原来的地址
        n2->next = n1;
        temp = n1;
    }

    Node *res = dummy->next;
    delete dummy;
    return res;
}

Node *rotateRight(Node *head, int k)
{
    if(k == 0 || head == nullptr || head->next == nullptr) return head;
    int length = 1;
    Node *temp = head;
    while(temp->next != nullptr)
    {
        temp = temp->next;
        length++;
    }
    
    int step = length - k % length;
    if(step == length) return head;
    temp->next = head;
    for(int i=step; i>0; i--)
    {
        temp = temp->next;
    }
    Node *res = temp->next;
    temp->next = nullptr;
    return res;
}

Node *deleteDuplicates(Node* head)
{
    if(head == nullptr) return head;
    Node *dummy = new Node(0, head);
    Node *temp = dummy;

    while(temp->next != nullptr && temp->next->next != nullptr)
    {
        if(temp->next->data == temp->next->next->data)
        {
            int val = temp->next->data;
            while(temp->next != nullptr && temp->next->data == val)
            {
                temp->next = temp->next->next;
            }
        } else {
            temp = temp->next;
        }
    }
    Node* res = dummy->next;
    delete dummy;
    return res;
}

Node* partition(Node* head, int x)
{
    Node* small = new Node(0);
    Node* smallDummy = small;
    Node* big = new Node(0);
    Node* bigDummy = big;

    while(head != nullptr)
    {
        if(head->data < x)
        {
            small->next = head;
            small = small->next;
        } else {
            big->next = head;
            big = big->next;
        }
        head = head->next;
    }
    big->next = nullptr;
    small->next = bigDummy->next;
    Node* res = smallDummy->next;
    delete smallDummy;
    delete bigDummy;
    return res;
}

Node* detectCycle(Node *head)
{
    Node* slow = head;
    Node* fast = head;
    while(fast != nullptr)
    {
        slow = slow->next;
        if(fast->next == nullptr) return nullptr;
        fast = fast->next->next;
        if(slow == fast)
        {
            Node* temp = head;
            while(temp != slow)
            {
                temp = temp->next;
                slow = slow->next;
            }
            return temp;
        }
    }
    return nullptr;
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
    // head = reverseBetween(head,2,4);
    // head = swapPairs(head);
    head = rotateRight(head,4);
    Print(head);
    return 0;
}
