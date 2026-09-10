#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode():val(0),next(nullptr){}
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution
{
public: 
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode dummy;//假的头节点，方便统一链表的插入操作
        ListNode *cur = &dummy;

        int carry = 0;
        while(l1 || l2 || carry)
        {
            int sum = carry;
            if(l1)
            {
                sum += l1->val;
                l1 = l1->next;
            }

            if(l2)
            {
                sum += l2->val;
                l2 = l2->next;
            }

            cur->next = new ListNode(sum % 10);
            //函数返回的是链表，要用链表存储数据，于是要new一个
            cur = cur->next;
            carry = sum/10;
        }
        return dummy.next;
    }
};

int main()
{
    ListNode *l1 = new ListNode(2);
    l1->next = new ListNode (4);
    l1->next->next = new ListNode (3);

    ListNode *l2 = new ListNode (0);
    l2->next = new ListNode (6);

    Solution s;
    ListNode *res = s.addTwoNumbers(l1,l2);
    while(res)
    {
        cout << res->val <<" ";
        res = res->next;
    }

    return 0;
}