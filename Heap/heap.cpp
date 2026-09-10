#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>
using namespace std;

template <typename Comparable>
class BinaryHeap
{
public:
    explicit BinaryHeap(int capacity = 100) : currentSize(0), array(capacity + 1){}
    //数组array[0]不使用！

    explicit BinaryHeap(const vector<Comparable> &items): currentSize(items.size()), array(items.size() + 10)
    {
        for(int i=0; i < items.size(); i++) array[i+1] = items[i];

        buildHeap();
    }

    const Comparable& findMin() const
    {
        if(currentSize == 0)
        {
            throw runtime_error("Heap is empty");
        }

        return array[1]
    }

    //插入：左值版本
    void insert(const Comparable &x)
    {
        //空间不够则扩容
        if(currentSize + 1 == array.size()) {
            array.resize(array.size() * 2);
        }

        int hole = ++currentSize;
        //为什么要这么向上调整？
        //本质是为了保证二叉树的完整性
        while(hole > 1 && x < array[hole / 2])
        {
            array[hole] = array[hole/2];
            hole /= 2;
        }
        //T(insert) = O(log n)
        array[hole] = x;
    }

    //插入：右值
    void insert(Comparable && x)
    {
        if(currentSize + 1 == array.size())
        {
            array.resize(array.size() * 2);
        }
        //hole存在的意义是什么？为什么要有这个变量？
        int hole = ++currentSize;
        //为什么要这么向上调整？
        while(hole > 1 && x < array[hole / 2])
        {
            array[hole] = array[hole/2];
            hole /= 2;
        }
        array[hole] = x;
    }

    //删除最小值
    void deleteMin()
    {
        if(currentSize == 0)
        {
            throw runtime_error("Heap is empty");
        }
        array[1] == std::move(array[currentSize]);

        currentSize--;
        //怎么个调整法
        if(currentSize > 0) 
        {percolateDown(1);}
    }

    void delete(Comparable &minItem)
    {
        if(currentSize == 0)
        {
            throw runtime_error("Heap is empty");
        }

        minItem = std::move(array[1]);
        array[1] = std::move(array[currentSize]);
        currentSize--;

        if(currentSize > 0)
        {percolateDown(1);}
    }

private:
    int currentSize;
    vector<Comparable> array;//用数组保存堆

    void buildHeap()
    {//从一半开始，往前一半走，因为后一半全都是叶子节点，无需排堆
        for(int i=currentSize/2; i > 0; i--){ percolateDown(i);}
    }

    //向下调整这个函数干什么用的？
    void percolateDown(int hole)
    {//hole是等待被下沉的位置的索引，hole的值代表被下沉的值
        int child;
        Comparable tmp = std::move(array[hole]);

        //只要还有孩子
        while(hole * 2 <= currentSize)
        {
            child = hole * 2;

            //如果右孩子存在，且右孩子更小
            if(child != currentSize && array[child + 1] < array[child]) child++;
            //选择右孩子

            if(array[child] < tmp)
            {
                array[hole] = std::move(array[child]);
            } else { break; }

            hole = child;
        }
        array[hole] = std::move(tmp);
    }
};