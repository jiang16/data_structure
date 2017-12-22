/*
    写在前面：
    由于队列需要对一个线性表的两端操作，用数组太浪费空间，所以就用了链式表实现
*/
#include <iostream>
#include <cassert>

using namespace std;

template<class T> class Queue;  //声明队列类模板
//创建结点类模板
template<class T>
class Node{
private:
    Node(const T &d): data(d), next(0){}
    T data;
    Node<T> *next;
    friend class Queue<T>;     //允许队列类模板访问本类私有成员
};

//创建队列类模板
template<class T>
class Queue{
public:
    Queue(): head(0), tail(0){}
    Queue(const Queue<T> &Q);
    Queue<T> & operator= (const Queue<T> &Q);
    ~Queue();
    bool empty();
    int length();
    T & front();
    void pop();
    void push(const T &d);
    void clear();
private:
    Node<T> *head;      //队列头结点
    Node<T> *tail;      //队列尾结点
    void destroy();     //销毁操作，只供内部函数调用，不允许外部调用
    void copy(const Queue<T> &Q);  //复制操作，只供内部函数调用，不允许外部调用
};

//复制构造函数
template<class T>
Queue<T>::Queue(const Queue<T> &Q){
    head = tail = 0;
    copy(Q);
}

//赋值运算符
template<class T>
Queue<T> & Queue<T>::operator= (const Queue<T> &Q){
    destroy();
    head = tail = 0;
    copy(Q);
}

//析构函数
template<class T>
Queue<T>::~Queue(){
    destroy();
}

//判断队列是否为空
template<class T>
bool Queue<T>::empty(){
    return head == 0;
}

//返回队列的长度
template<class T>
int Queue<T>::length(){
    int len = 0;
    for(Node<T> *p = head; p; p = p->next)
        len++;
    return len;
}

//取队首元素
template<class T>
T & Queue<T>::front(){
    assert(head != 0);
    return head->data;
}

//删除队首元素
template<class T>
void Queue<T>::pop(){
    assert(tail != 0);
    Node<T> *p = head;
    head = p->next;
    delete p;
}

//向队列中压入元素
template<class T>
void Queue<T>::push(const T &d){
    Node<T> *p = new Node<T>(d);
    if(empty())
    {
        head = tail = p;
    }
    else
    {
        tail->next = p;
        tail = tail->next;
    }
}

//清空队列
template<class T>
void Queue<T>::clear(){
    destroy();
    head = tail = 0;
}

//销毁队列，释放空间
template<class T>
void Queue<T>::destroy(){
    if(empty()) return;
    Node<T> *p = head, *q;
    while(p)
    {
        q = p->next;
        delete p;
        p = q;
        if(q) q = q->next;
    }
}

//复制元素
template<class T>
void Queue<T>::copy(const Queue<T> &Q){
    for(Node<T> *p = Q.head; p; p = p->next)
        push(p->data);
}

//测试
int main(){
    Queue<int> q;
    int n, d;
    cin >> n;
    for(int i = 0; i < n; i++)   //输入n个元素入队
    {
        cin >> d;
        q.push(d);
    }
    Queue<int> qq = q;           //调用复制构造函数
    qq = q;                      //调用赋值运算符
    cout << "队列q的长度: " << q.length() << endl << "出队序列:";
    for(int i = 0; i < n; i++)
    {
        cout << ' ' << q.front();//取队首元素
        q.pop();                 //出队
    }
    cout << endl << "队列q的长度: " << q.length() << " 队列qq的长度: " << qq.length() << endl;
}
