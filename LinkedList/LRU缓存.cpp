#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct Node {
    int key;
    int value;
    Node *prev;
    Node *next;
    //必不可少的构造函数
    Node (int k=0, int v=0): key(k), value(v){};
};

class LRUCache {
private:
    int capacity;
    Node *dummy;//哨兵节点，其prev为要干掉的书，next为刚用过的书
    unordered_map<int, Node*> key_to_node;//STL最有用的一集

    void remove(Node *x)
    {//删除节点
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }

    void push_front(Node *x)
    {//dummy初始化放在public里面了
        x->prev = dummy;
        x->next = dummy->next;
        x->prev->next = x;
        x->next->prev = x;
    }

    Node* get_node(int key)
    {
        auto it = key_to_node.find(key);
        if(it == key_to_node.end()){
            return nullptr;
        }
        Node *node = it->second;//有这本书
        remove(node);//把书抽出来
        push_front (node);//放到最上面
        return node;
    }
public:
    LRUCache(int capacity) : capacity(capacity), dummy(new Node()){
        dummy->prev = dummy;
        dummy->next = dummy;
    }
    
    int get(int key) {
        Node *node = get_node(key);//get_node 会把对应节点转移到链表头部
        return node ? node->value : -1;
    }
    
    void put(int key, int value) {
        Node *node = get_node(key);
        if(node){//有这本书
            node->value = value;//更新value
            return;
        }
        key_to_node[key] = node = new Node(key, value);//新书
        push_front(node);//放到最上面
        if(key_to_node.size() > capacity)
        {//书太多了
            Node *back_node = dummy->prev;
            key_to_node.erase(back_node->key);
            remove(back_node);//干掉最后一本书
            delete back_node;//释放内存
        }
    }
};

int main()
{
    LRUCache lru(2);
    cout << "--- LRU 缓存测试开始 ---" << endl;
    cout << "--- LRU 缓存测试开始 ---" << endl;

    lru.put(1, 1); // 缓存是 {1=1}
    lru.put(2, 2); // 缓存是 {1=1, 2=2}
    cout << "获取 key 1: " << lru.get(1) << " (期望: 1, 此时 1 变成最新)" << endl; 

    lru.put(3, 3); // 此时容量满了，踢掉最久没用的 key 2，缓存是 {1=1, 3=3}
    cout << "获取 key 2: " << lru.get(2) << " (期望: -1, 因为被踢了)" << endl;

    lru.put(4, 4); // 此时踢掉最久没用的 key 1，缓存是 {3=3, 4=4}
    cout << "获取 key 1: " << lru.get(1) << " (期望: -1)" << endl;
    cout << "获取 key 3: " << lru.get(3) << " (期望: 3)" << endl;
    cout << "获取 key 4: " << lru.get(4) << " (期望: 4)" << endl;

    cout << "--- 测试结束 ---" << endl;

    return 0;
}

/*这个是纯STL版，带你领略STL的极致运用
#include <iostream>
#include <unordered_map>
#include <list>
#include <utility> // 包含 pair

using namespace std;

class LRUCache {
private:
    int capacity;
    // list 存储 pair<key, value>，它是一个双向链表
    list<pair<int, int>> cache_list;
    // unordered_map 存储 key 到 链表迭代器（iterator）的映射
    // 迭代器可以类比为指向链表节点的“精准书签”
    unordered_map<int, list<pair<int, int>>::iterator> key_to_iter;

public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        auto it = key_to_iter.find(key);
        // 1. 如果没找到，直接返回 -1
        if (it == key_to_iter.end()) {
            return -1;
        }

        // 2. 如果找到了，先把这个节点移到链表头部（表示最近使用过）
        // splice 的作用：将 it->second 指向的节点移动到 cache_list 的 begin() 位置
        // 这个操作是 O(1) 的，只是改变了指针指向，不涉及元素拷贝
        cache_list.splice(cache_list.begin(), cache_list, it->second);

        // 3. 返回 value
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = key_to_iter.find(key);

        // 情况 A: 如果 key 已经存在
        if (it != key_to_iter.end()) {
            // 更新 value
            it->second->second = value;
            // 移到最前面
            cache_list.splice(cache_list.begin(), cache_list, it->second);
            return;
        }

        // 情况 B: 如果是新 key
        // 1. 先在链表头部插入新节点
        cache_list.emplace_front(key, value);
        // 2. 在 map 中记录这个新节点的迭代器
        key_to_iter[key] = cache_list.begin();

        // 3. 如果超过容量，删除最久没用的（即链表尾部的节点）
        if (key_to_iter.size() > capacity) {
            // 拿到最后一个元素的 key
            int key_to_del = cache_list.back().first;
            // 从 map 中移除
            key_to_iter.erase(key_to_del);
            // 从链表中移除
            cache_list.pop_back();
        }
    }
};

int main() {
    LRUCache lru(2);

    cout << "--- STL 版 LRU 缓存测试 ---" << endl;

    lru.put(1, 10);
    lru.put(2, 20);
    cout << "Get 1: " << lru.get(1) << " (期望 10)" << endl;

    lru.put(3, 30); // 踢掉 2
    cout << "Get 2: " << lru.get(2) << " (期望 -1)" << endl;

    lru.put(4, 40); // 踢掉 1
    cout << "Get 1: " << lru.get(1) << " (期望 -1)" << endl;
    cout << "Get 3: " << lru.get(3) << " (期望 30)" << endl;

    cout << "--- 测试结束 ---" << endl;

    return 0;
}
*/