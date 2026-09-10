#include <iostream>
#include <vector>
using namespace std;

void BubbleSort(vector<int> &vec)
{
    int temp = 0;
    for(int i=0; i < vec.size(); i++)
    {//往前走
        for(int j=vec.size()-1; j > 0; j--)
        {//往回走
            if(vec[j] < vec[j-1])
            {
                temp = vec[j-1];
                vec[j-1] = vec[j];
                vec[j] = temp;
            }
        }
    }
}

void SelectionSort(vector<int> &vec)
{
    for(int i=0; i < vec.size()-1; i++)
    {
        int low = i;
        for(int j = vec.size()-1; j>i ;j--)
        {
            if(vec[low] > vec[j])
            {
                low = j;
            }
        }
        int temp = vec[low];
        vec[low] = vec[i];
        vec[i] = temp;
    }
}

void InsertionSort(vector<int> &vec)
{
    for(int i=1; i<vec.size() ;i++)
    {
        int cur = vec[i];
        int j=i;
        for(; j>0 && vec[j-1] > cur ;j--)
        {
            vec[j] = vec[j-1];
        }
        vec[j] = cur;
    }
}

void ShellSort(vector<int> &vec)
{
    for(int gap = vec.size()/2; gap>0 ;gap/=2)//间隔变化
    {
        for(int i=gap; i<vec.size() ;i++)
        {//交叉处理每个组
            int temp = vec[i];
            int j = i;

            while(j >= gap && temp < vec[j - gap])
            {//当前元素所属组别按gap向前找位置
                vec[j] = vec[j - gap];
                j -= gap;
            }

            vec[j] = temp;
        }
    }
}

int main()
{
    vector<int> n1 = {42,20,17,13,28,14,23,15};
    vector<int> n2 = n1;
    vector<int> n3 = n1;
    vector<int> n4 = n1;

    BubbleSort(n1);
    for(int i=0; i<n1.size();i++)
    {
        cout << n1[i]<<" ";
    }
    cout << endl;

    SelectionSort(n2);
    for(int i=0; i<n2.size();i++)
    {
        cout << n2[i]<<" ";
    }
    cout << endl;

    InsertionSort(n3);
    for(int i=0; i<n3.size();i++)
    {
        cout << n3[i]<<" ";
    }
    cout << endl;

    ShellSort(n4);
    for(int i=0; i<n4.size();i++)
    {
        cout << n4[i]<<" ";
    }
    cout << endl;

    return 0;
}