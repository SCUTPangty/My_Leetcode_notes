#include <iostream>
#include <queue>
using namespace std;

//队列queue基于数组的实现
const int MAX_SIZE = 10;
int A[ MAX_SIZE];
int front = -1,rear = -1;

bool IsEmpty()
{
    return front==-1 && rear==-1;
}

bool IsFull() {
    return (rear + 1) % MAX_SIZE == front;
}

void Enqueue(int x)
{
    //环形数组
    if(IsFull()) return;
    else if(IsEmpty())
    {
        front = 0;
        rear = 0;
    } else {
        rear = (rear+1) %MAX_SIZE;
    }
    A[rear] = x;
    cout << "入队："<<x<<endl;
}

void Dequeue()
{
    if (IsEmpty()) {
        cout << "错误：队列已空，无法出队" << endl;
        return;
    }
    
    int temp = A[front]; // 记录一下弹出的元素
    if (front == rear) {
        // 最后一个元素弹完后，重置
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % MAX_SIZE;
    }
    cout << "出队成功，弹出元素: " << temp << endl;
}

int Front()
{
    if (IsEmpty( )) {
        cout << "队列已空，无队首元素" << endl;
        return -1;  // 这里返回-1表示错误情况，可根据实际需求调整
    }
    return A[front];
}

int main()
{
    
    Enqueue(94);
    Enqueue(46);
    Enqueue(3);

    cout << "当前队首: " << Front() << endl;

    // 2. 实现一个一个弹出的效果
    cout << "\n开始依次弹出元素：" << endl;
    while (!IsEmpty()) {
        Dequeue(); // 每次调用都会弹出当前的 front
        if (!IsEmpty()) {
            cout << "新的队首变为: " << Front() << endl;
        } else {
            cout << "队列现在彻底空了。" << endl;
        }
        cout << "-------------------" << endl;
    }

    return 0;
}