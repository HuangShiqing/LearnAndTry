// 剑指 Offer 59 - II. 队列的最大值
// 请定义一个队列并实现函数 max_value 得到队列里的最大值，要求函数max_value、push_back 和 pop_front 的均摊时间复杂度都是O(1)。
// 若队列为空，pop_front 和 max_value 需要返回 -1

// 示例 1：
// 输入: 
// ["MaxQueue","push_back","push_back","max_value","pop_front","max_value"]
// [[],[1],[2],[],[],[]]
// 输出: [null,null,null,2,1,2]

// 示例 2：
// 输入: 
// ["MaxQueue","pop_front","max_value"]
// [[],[],[]]
// 输出: [null,-1,-1]

// -------------------第三次刷-----------------------
// 2021年6月3日14:30:29
// 准备第一次社招
// 思路: 就跟那题包含min的栈思路一样, 用两个队列是很容易想到的. 一个队列d1正常使用, 另外一个d2包含对应高度的最大值, 但是问题是队列是可以前面出队的, 这样d2前面一变动, 
// 后面所有的最大值就失效了. 因此不能是同样高度一一对应的. 有一个特点应该注意, 比如正常队列里d1是1,1,1,3, 只要3还没出队, 对于d2来说前面的1都不重要. 因此改进
// 的d2在push value的时候会pop_back()直到value<d2.back(). 这样max = d2.front(). 而pop的时候只要pop的数不是d2.front(), 那d2就不用动

class MaxQueue {
public:
    queue<int> d1;
    deque<int> d2;
    MaxQueue() {

    }
    
    int max_value() {
        if(d2.empty())
            return -1;

        return d2.front();
    }
    
    void push_back(int value) {
        d1.push(value);

        while(!d2.empty() && value>d2.back()){
            d2.pop_back();
        }
        d2.push_back(value);        
    }
    
    int pop_front() {
        if(d1.empty())
            return -1;

        int tmp = d1.front();
        d1.pop();

        if(tmp == d2.front()){
            d2.pop_front();
        }
        return tmp;
    }
};

/**
 * Your MaxQueue object will be instantiated and called as such:
 * MaxQueue* obj = new MaxQueue();
 * int param_1 = obj->max_value();
 * obj->push_back(value);
 * int param_3 = obj->pop_front();
 */