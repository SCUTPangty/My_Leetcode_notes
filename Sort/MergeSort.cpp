#include <iostream>
#include <vector>
using namespace std;

void Merge(vector<int> &vec, int left, int mid, int right)
{
    vector<int> temp;

    int i = left;
    int j = mid + 1;

    while(i <= mid && j <= right)
    {//左右两个有序区间进行比较
        if(vec[i] <= vec[j])
        {
            temp.push_back(vec[i]);
            i++;
        } else 
        {
            temp.push_back(vec[j]);
            j++;
        }
    }

    while(i <= mid)
    {//左边还有剩余
        temp.push_back(vec[i]);
        i++;
    }

    while(j <= right)
    {//右边还有剩余
        temp.push_back(vec[j]);
        j++;
    }

    for(int k=0; k < temp.size(); k++)
    {//把排好序的结果放回原数组
        vec[left + k] = temp[k];
    }
}

void MergeSort(vector<int> &vec,int left, int right)
{
    if(left >= right) return;//只有一个元素，不用排序

    int mid = left + (right - left)/2;

    MergeSort(vec,left,mid);//排左半部分
    MergeSort(vec,mid+1, right);//排右半部分
    Merge(vec,left,mid,right);//合并两个有序部分
}

void MergeSort(vector<int> &vec)
{
    if(vec.empty()) return;
    MergeSort(vec, 0, vec.size() -1 );
}

//向下调整，大顶堆
void PercolateDown(vector<int> &vec, int parent, int size)
{
    int temp = vec[parent];
    int child = parent*2 + 1;//左孩子
    while(child < size)
    {
        //如果右孩子存在，且右孩子更大，就选择右孩子
        if(child+1 < size && vec[child+1] > vec[child])
        {
            child++;
        }
        //如果父节点比最大的孩子大，就不同调整
        if(temp >= vec[child]) break;

        //把较大的孩子往上移动
        vec[parent] = vec[child];
        //parent向下移动，向下遍历
        parent = child;
        child = parent*2 + 1;
    }

    //把原来的父节点放到最终位置
    vec[parent] = temp;
}

void HeapSort(vector<int> &vec)
{
    if(vec.empty()) return ;
    int n = vec.size();

    //建立大顶堆
    for(int i = n/2-1; i>=0 ;i--)
    {
        PercolateDown(vec,i,n);
    }

    //不断把堆顶最大值放到数组末尾
    for(int end = n-1; end>0 ;end--)
    {//交换堆顶和当前最后一个元素
        int temp = vec[0];
        vec[0] = vec[end];
        vec[end] = temp;

        //剩下部分重新调整成大顶堆
        PercolateDown(vec,0,end);
    }
}

int main()
{
    vector<int> vec = {8,2,9,4,5,3,1,6,3};
    vector<int> vect = vec;

    MergeSort(vec);
    for(int i=0; i < vec.size(); i++)
    {
        cout << vec[i]<<" ";
    }
    cout << endl;

    HeapSort(vect);
    for(int i=0; i < vect.size(); i++)
    {
        cout << vect[i]<<" ";
    }
    cout << endl;
    return 0;
}