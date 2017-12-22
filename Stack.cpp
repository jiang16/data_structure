/*
    写在前面：
    由于栈只对一个线性表的一端操作，空间利用率很高，所以就用了顺序表实现
*/
#include <iostream>
#include <cassert>

using namespace std;

//创建栈类模板
template<class T>
class Stack{
public:
    Stack();
    Stack(const Stack<T> &S);
    Stack<T> & operator= (const Stack<T> &S);
    ~Stack();
    bool empty();
    int length();
    T & top();
    void pop();
    void push(const T &data);
    void clear();
private:
    T *list;          //T类型指针，用于存放动态分配的数组内存首地址
    int size;         //数组大小
    int cap;          //数组容量   
    void destroy();   //销毁操作，只供内部函数调用，不允许外部调用
    void copy(const Stack<T> &S);  //复制操作，只供内部函数调用，不允许外部调用
};

//构造函数
template<class T>
Stack<T>::Stack(){
    cap = 100;        //初始数组容量为100
    size = 0;
    list = new T [cap];
}

//复制构造函数
template<class T>
Stack<T>::Stack(const Stack<T> &S){
    copy(S);
}

//赋值运算符
template<class T>
Stack<T> & Stack<T>::operator= (const Stack<T> &S){
    destroy();        //释放原来的空间
    copy(S);
}

//析构函数
template<class T>
Stack<T>::~Stack(){
    destroy();
}

//判断栈是否为空
template<class T>
bool Stack<T>::empty(){
    return size == 0;
}

//返回栈的长度
template<class T>
int Stack<T>::length(){
    return size;
}

//取栈顶元素
template<class T>
T & Stack<T>::top(){
    assert(size > 0);
    return list[size - 1];
}

//删除栈顶元素
template<class T>
void Stack<T>::pop(){
    assert(size > 0);
    size--;
}

//向栈中压入元素
template<class T>
void Stack<T>::push(const T &data){
    if(size == cap)   //如果当前数组容量和数组长度相等
    {                 //则释放掉原来的空间，重新分配大一些的空间，把元素复制过去
        cap += 100;
        T *temp = new T [cap];
        for(int i = 0; i < size; i++)
            temp[i] = list[i];
        temp[size++] = data;
        destroy();
        list = temp;
    }
    else
    {
        list[size++] = data;
    }
}

//清空栈
template<class T>
void Stack<T>::clear(){
    size = 0;
}

//销毁栈，释放空间
template<class T>
void Stack<T>::destroy(){
    delete [] list;
}

//复制元素
template<class T>
void Stack<T>::copy(const Stack<T> &S){
    cap = S.cap;
    size = S.size;
    list = new T [cap];
    for(int i = 0; i < S.size; i++)
        list[i] = S.list[i];
}

//测试
int main(){
    Stack<int> s1;
    int n, x;
    cin >> n;
    for(int i = 0; i < n; i++) //输入n个元素入栈
    {
        cin >> x;
        s1.push(x);
    }
    Stack<int> s2 = s1;        //调用复制构造函数
    s2 = s1;                   //调用赋值操作
    s2.pop();                  //s2栈顶元素出栈
    cout << "s2的栈顶元素: " << s2.top() << endl;
    s2.clear();                //清空s2
    cout << "s1的长度: " << s1.length() << endl;
    cout << "s2的长度: " << s2.length() << endl;
}
