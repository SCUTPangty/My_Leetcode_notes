#include <iostream>
#include <vector>
using namespace std;

void FastSort(vector<int> &vec, int start, int end)
{
    if(start >= end) return ;

    int left = start;
    int right = end;
    int temp = vec[left];

    while(left < right)
    {
        while(vec[right] > temp && left < right) right--;
        //跳出循环说明找到目标值，可以换数
        if(left < right)
        {
            vec[left] = vec[right];
            left++;
        }

        while(vec[left] < temp && left < right)
        {
            left++;
        }
        //跳出循环说明找到目标值，可以换数
        if(left < right)
        {
            vec[right] = vec[left];
            right--;
        }
    }
    //最左边作为基准值pivot
    vec[left] = temp;
    //递归
    FastSort(vec,start,left-1);
    FastSort(vec, right+1,end);
}

void BucketSort(vector<int> &vec)
{
    if(vec.empty()) return ;

    int Maxkey = vec[0];
    for(int i=1; i < vec.size();i++)
    {
        if(vec[i] > Maxkey)
        {
            Maxkey = vec[i];
        }
    }

    vector<vector<int>> bucket(Maxkey+1);

    //分桶
    for(int i=0;i < vec.size() ;i++)
    {
        bucket[vec[i]].push_back(vec[i]);
    }
    //按桶号从小到大拿出来
    int k=0;

    for(int i=0; i<=Maxkey ;i++)
    {
        for(int j=0; j < bucket[i].size(); j++)
        {
            vec[k] = bucket[i][j];
            k++;
        }
    }
}

void RadixSort(vector<int> &vec)
{
    if(vec.empty()) return ;
    int Maxkey = vec[0];
    for(int i=1; i < vec.size(); i++)
    {//寻找最大值，确定有多少位
        if(vec[i] > Maxkey)
        {
            Maxkey = vec[i];
        }
    }

    vector<int> temp(vec.size());

    for(int btoi = 1; Maxkey/btoi>0; btoi*=10)
    {
        int cnt[10] = {0};

        //统计这一位有多少0~9
        for(int i=0; i<vec.size(); i++)
        {
            int digit = (vec[i]/btoi)%10;
            cnt[digit]++;
        }

        for(int i=1; i<10 ;i++)
        {//累加，得到每个桶的结果
            //通过累加得知每个桶在总数组里的收尾下标（确认桶的范围）
            cnt[i] += cnt[i-1];
        }
        //重塑数组
        for(int i=vec.size()-1; i>=0 ;i--)
        {
            int digit = (vec[i]/btoi)%10;
            cnt[digit]--;//确认最终下标位置，从0开始，需要-1
            temp[cnt[digit]] = vec[i];
        }

        //temp复制回vec
        for(int i=0; i<vec.size(); i++)
        {
            vec[i] = temp[i];
        }
    }
}

int main()
{
    vector<int> a = {8,1,4,9,6,3,5,2,7,0};
    vector<int> b = {27,91,1,97,17,23,84,28,72,5,67,25};
    vector<int> c = {27,91,1,97,17,23,84,28,72,5,67,25};

    FastSort(a,0,a.size()-1);
    for(int i=0; i < a.size(); i++)
    {
        cout << a[i] <<" ";
    }
    cout << endl;

    BucketSort(b);
    for(int i=0; i < b.size() ;i++)
    {
        cout << b[i]<<" ";
    }
    cout << endl;

    RadixSort(c);
    for(int i=0; i<c.size();i++)
    {
        cout << c[i]<<" ";
    }
    cout << endl;

    return 0;
}