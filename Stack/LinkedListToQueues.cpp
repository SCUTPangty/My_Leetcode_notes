#include <iostream>
#include <queue>
using namespace std;

//链表实现queue
struct Node{
    int data;
    struct Node *next;
};

Node *front = nullptr;
Node *rear = nullptr;

void Enqueue(int x)
{
    struct Node *temp = new Node();
    temp->data = x;
    temp->next = nullptr;
    if(front==nullptr && rear==nullptr)
    {
        front = rear = temp;
        return ;
    }
    rear->next = temp;
    rear = temp;
    cout << x << " 已入队" << endl;
}

void Dequeue()
{
    Node *temp = front;
    if(front == nullptr) return;
    int value = front->data;
    if(front==rear)
    {
        front = rear = nullptr;
    } else {
        front = front->next;
    }
    delete temp; //temp指向front最初的位置，释放temp就相当于删了那个界定啊
    cout << value << " 已出队" << endl;
}

void Print()
{
    Node *temp = front;
    cout <<"当前队列："<<endl;
    while(temp != nullptr)
    {
        cout <<temp->data<<" ";
        temp = temp->next;
    }
    cout << endl;
}

int main()
{
    Enqueue(34);
    Enqueue(58);
    Enqueue(65);
    Enqueue(29);
    Print();
    Dequeue();
    Print();
    return 0;
}