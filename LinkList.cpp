/*
   写在前面：
   不得不说链表真的挺复杂，而且我还写成了模板，debug了很久...
   严重强迫症的我，代码改了好多遍... 如果有错，尽管来拍我
*/
#include <iostream>

using namespace std;

template<class T> class LinkList;   //声明链表类模板
template<class T> ostream & operator<< (ostream &os, const LinkList<T> &L);

//创建结点类模板
template<class T>
class Node{
private:
    Node(const T &d): data(d), next(0){}
    T data;
    Node *next;
    friend class LinkList<T>;       //允许链表类模板访问本类私有成员
    friend ostream & operator<< <T>(ostream &os, const LinkList<T> &L);
};

//创建单链表类模板
template<class T>
class LinkList{
public:
    LinkList();
    LinkList(const LinkList<T> &L);
    LinkList<T> & operator= (const LinkList<T> &L);
    ~LinkList();
    void Create(int n);
    bool GetElem(int i, T &elem);
    bool Insert(int i, const T &d);
    bool Delete(int i);
    LinkList<T> & operator+ (const LinkList &L);
    friend ostream & operator<< <T>(ostream &os, const LinkList<T> &L);
private:
    Node<T> *head;                  //链表头结点
    void Destroy();                 //销毁操作，只供内部函数调用，不允许外部调用
    void Copy(const LinkList<T> &L);//复制操作，只供内部函数调用，不允许外部调用
};

//构造函数
template<class T>
LinkList<T>::LinkList(){
    head = new Node<T>(0);          //为头结点分配空间
}

//复制构造函数
template<class T>
LinkList<T>::LinkList(const LinkList<T> &L){
    head = new Node<T>(0);
    Copy(L);
}

//赋值运算符
template<class T>
LinkList<T> & LinkList<T>::operator= (const LinkList<T> &L){
    Destroy();
    head = new Node<T>(0);
    Copy(L);
}

//析构函数
template<class T>
LinkList<T>::~LinkList(){
    Destroy();
}

//输入n个元素的值，建立带头结点的单链表
template<class T>
void LinkList<T>::Create(int n){
    T d;
    Node<T> *p = head;
    while(n--)
    {
        cin >> d;
        p->next = new Node<T>(d);
        p = p->next;
    }
}

//当第i个元素存在时，其值赋给elem，否则返回false
template<class T>
bool LinkList<T>::GetElem(int i, T &elem){
    Node<T> *p = head;
    while(p && i)
    {
        p = p->next;
        i--;
    }
    if(!p) return false;
    elem = p->data;
    return true;
}

//在单链表中第i个位置之前插入元素d，插入失败返回false
template<class T>
bool LinkList<T>::Insert(int i, const T &d){
    Node<T> *p = head;
    while(p && i > 1)
    {
        p = p->next;
        i--;
    }
    if(!p) return false;
    Node<T> *temp = new Node<T>(d);        
    temp->next = p->next;
    p->next = temp;
    return true;
}

//删除单链表中第i个元素，删除失败返回false
template<class T>
bool LinkList<T>::Delete(int i){
    Node<T> *p = head;
    while(p && i > 1)
    {
        p = p->next;
        i--;
    }
    if(!p) return false;
    Node<T> *temp = p->next;
    p->next = temp->next;
    delete temp;
    return true;
}

//重载加号操作符，归并有序的当前链表和L，使之成为一个非递减有序表
template<class T>
LinkList<T> & LinkList<T>::operator+ (const LinkList &L){
    Node<T> *p = head->next;
    Node<T> *q = L.head->next;
    Node<T> *t = head;
    while(p && q)
    {
        if(p->data <= q->data)
        {
            t->next = p;
            t = t->next;
            p = p->next;
        }
        else
        {
            t->next = q;
            t = t->next;
            q = q->next;
        }
    }
    t->next = p ? p : q;
    t = head->next;
    return *this;
}

//重载输出操作符，输出单链表的元素
template<class T>
ostream & operator<< (ostream &os, const LinkList<T> &L){
    Node<T> *p = L.head->next;
    while(p)
    {
        os << p->data << ' ';
        p = p->next;
    }
    return os;
}

//销毁单链表，释放空间
template<class T>
void LinkList<T>::Destroy(){
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
void LinkList<T>::Copy(const LinkList<T> &L){
    Node<T> *p = head, *q = L.head->next;
    while(q)
    {
        p->next = new Node<T>(q->data);
        p = p->next;
        q = q->next;
    }
}

//测试
int main(){    
    int n;
    cin >> n;
    LinkList<int> L1;            
    L1.Create(n);           //建立有n个元素的单链表L1
    cout << "输出L1: " << L1 << endl;
    LinkList<int> L2(L1);   //调用复制构造函数
    L2 = L1;                //调用赋值运算符
    cout << "输出L2: " << L2 << endl;
    int i, elem, d;
    cin >> i;               
    L1.GetElem(i, elem);    //在L1中把第i个元素的值赋给elem
    cout << "第i个元素: " << elem << endl;
    cin >> d;               //输入要插入的元素值
    L1.Insert(i, d);        //在L1的第i个位置插入元素d
    cout << "输出插入元素后的L1: " << L1 << endl;
    L1.Delete(i);           //删除L1的第i个位置的元素
    cout << "输出L1 + L2: " << L1 + L2 << endl;
    return 0;
}
