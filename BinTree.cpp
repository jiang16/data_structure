/*
    写在前面：
    由于二叉树的构建方式有点特殊，所以我这里就没再写成模板，数据类型为字符型
*/
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

//创建结点类
class Node{
private:
    Node(const char &d): data(d), lchild(0), rchild(0){}
    char data;
    Node *lchild;
    Node *rchild;
    friend class BinTree;
};

//创建二叉树类
class BinTree{
public:   
    BinTree(): root(0){}
    BinTree(const BinTree &B);
    BinTree & operator= (const BinTree &B);
    ~BinTree();
    Node *& GetRoot() {return root;}   //返回根结点，由于多次调用，定义为内联函数
    void Create(Node *&rt);
    int Leaf(Node *rt);
    int Depth(Node *rt);
    void PreOrder(Node *rt);
    void InOrder(Node *rt);
    void PostOrder(Node *rt);
    void LayerOrder(Node *rt);
private:    
    Node *root;
    void Destroy(Node *&rt);           //销毁操作，只供内部函数调用，不允许外部调用
    void Copy(Node *&rt, Node *br);    //复制操作，只供内部函数调用，不允许外部调用
};

//复制构造函数
BinTree::BinTree(const BinTree &B){
    root = 0;
    Copy(root, B.root);
}

//赋值运算符
BinTree & BinTree::operator= (const BinTree &B){
    Destroy(root);
    root = 0;
    Copy(root, B.root);
}

//析构函数
BinTree::~BinTree(){
    Destroy(root);
}

//输入先序序列构建二叉树，空格表示空结点
void BinTree::Create(Node *&rt){
    char c;
    cin >> c;
    if(c == '#')    //'#'表示空结点
    {
        rt = NULL;
        return;
    }
    rt = new Node(c);
    Create(rt->lchild);
    Create(rt->rchild);
}

//统计二叉树的叶子数目
int BinTree::Leaf(Node *rt){
    if(rt == 0) return 0;
    if(rt->lchild == 0 && rt->rchild == 0) return 1;
    return Leaf(rt->lchild) + Leaf(rt->rchild);
}

//返回二叉树的深度
int BinTree::Depth(Node *rt){
    if(rt == 0) return 0;
    return max(Depth(rt->lchild), Depth(rt->rchild)) + 1;
}

//前序遍历二叉树
void BinTree::PreOrder(Node *rt){
    if(rt == 0) return;
    cout << rt->data << ' ';
    PreOrder(rt->lchild);
    PreOrder(rt->rchild);
}

//中序遍历二叉树
void BinTree::InOrder(Node *rt){
    if(rt == 0) return;
    InOrder(rt->lchild);
    cout << rt->data << ' ';
    InOrder(rt->rchild);
}

//后序遍历二叉树
void BinTree::PostOrder(Node *rt){
    if(rt == 0) return;
    PostOrder(rt->lchild);
    PostOrder(rt->rchild);
    cout << rt->data << ' ';
}

//层序遍历二叉树
void BinTree::LayerOrder(Node *rt){
    queue<Node *> q;
    if(rt)
        q.push(rt);
    while(!q.empty())
    {
        Node *p = q.front();
        q.pop();
        cout << p->data << ' ';
        if(p->lchild) q.push(p->lchild);
        if(p->rchild) q.push(p->rchild);
    }
}

//销毁二叉树，释放空间
void BinTree::Destroy(Node *&rt){
    if(rt == 0) return;
    Node *p = rt->lchild, *q = rt->rchild;
    delete rt;
    Destroy(p);
    Destroy(q);
}

//复制元素
void BinTree::Copy(Node *&rt, Node *br){
    if(br == 0) return;
    rt = new Node(br->data);
    Copy(rt->lchild, br->lchild);
    Copy(rt->rchild, br->rchild);
}

//测试
int main(){
    BinTree tree1;
    tree1.Create(tree1.GetRoot());
    BinTree tree2 = tree1;    //调用复制构造函数
    tree2 = tree1;            //调用赋值运算符
    cout << "tree1的叶子结点数为: " << tree1.Leaf(tree1.GetRoot()) << endl;
    cout << "tree1的深度为: " << tree1.Depth(tree1.GetRoot()) << endl;
    cout << "tree2的前序遍历序列为:" << endl;
    tree2.PreOrder(tree2.GetRoot());
    cout << endl << "tree2的中序遍历序列为:" << endl;
    tree2.InOrder(tree2.GetRoot());
    cout << endl << "tree2的后序遍历序列为:" << endl;
    tree2.PostOrder(tree2.GetRoot());
    cout << endl << "tree2的层序遍历序列为:" << endl;
    tree2.LayerOrder(tree2.GetRoot());
    cout << endl;
    return 0;
}
