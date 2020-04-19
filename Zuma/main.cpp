#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

class ListNode{//链表结点的定义
public:
    char data;
    //双向链表，有pre和next两个指针，分别指向前一个元素和后一个元素
    ListNode *pre;
    ListNode *next;
    ListNode(char c){data=c;pre=NULL;next=NULL;}

};
class SeqList{
public:
    //带头指针first和尾指针last，尾指针是为了便于添加元素
    ListNode *first;
    ListNode *last;
    SeqList();
    void insertOne(int k,char &c);//插入一个元素
    void addOne(char &c);//添加一个元素使用后插发
    void printAll();//打印链表的函数
    void deleteOne(ListNode *d);//删除一个元素
    void update(ListNode *p);//插入节点后更新zuma链，及有三个连续的就删除，并且产生连锁反应
    bool isThree(ListNode *p);//判断结点p附近是否有三个或三个以上连续的元素
};
bool SeqList::isThree(ListNode *p)
{
    //判断结点p附近是否有三个或三个以上连续的元素
    //有返回true，没有返回false
    char t=p->data;
    if(p->pre->data==t)
    {
        if(p->pre->pre->data==t||p->next->data==t) return true;
    }else if(p->next->data==t)
    {
        if(p->next->next->data==t||p->pre->data==t) return true;
    }
    return false;
}
void SeqList::update(ListNode *q)
{
    //插入节点后更新zuma链，及有三个连续的就删除，并且产生连锁反应
    while(isThree(q))//判断是否三个连续
    {

        while(q->pre->data==q->data) deleteOne(q->pre);//从该节点往前判断是否和该节点data相同，相同则删除
        while(q->next->data==q->data) deleteOne(q->next);//从该节点往后判断是否和该节点data相同，相同则删除
        if(q->next!=last) {q=q->next;deleteOne(q->pre);}//如果p不是最后一个结点，则将p往后移，并且删除之前的p
        else if(q->pre!=first) {q=q->pre;deleteOne(q->next);}//否则p往前移
        else {deleteOne(q);break;}//再否则就是只剩下p结点，则只需删除p就行
    }
}
void SeqList::deleteOne(ListNode *d)
{
    //删除结点p
    d->pre->next=d->next;
    d->next->pre=d->pre;
    delete d;
}
void SeqList::printAll()
{
    //打印所有结点
    ListNode *p=first->next;
    if(first->next==last)//没有节点输出"-";
    {
        printf("-");
    }
    while(p!=NULL)
    {
        printf("%c",p->data);
        p=p->next;
    }
}
SeqList::SeqList()
{
    //初始化时定义空头节点和空尾结点
    first=new ListNode('#');
    last=new ListNode('\n');//为节点的值存放'\n'，这样在输出时最后直接输出尾结点，就能直接换行
    first->next=last;
    last->pre=first;
}
void SeqList::addOne(char &c)
{
    //尾插法添加节点
    ListNode *q=last->pre;
    ListNode *p=new ListNode(c);
    q->next=p;
    p->pre=q;
    p->next=last;
    last->pre=p;
}
void SeqList::insertOne(int n,char &c)
{
    //再位置n出插入一个节点
    ListNode *p=first->next;
    for(int i=0;i<n;i++)
    {
        p=p->next;
    }
    ListNode *q=p->pre;
    ListNode *newNode=new ListNode(c);
    q->next=newNode;
    newNode->pre=q;
    p->pre=newNode;
    newNode->next=p;
    update(newNode);//插入节点后直接调用更新函数，更新zuma链
}
int main()
{
    SeqList li;
    while(1)
    {
        char c;
        scanf("%c",&c);
        if(c=='\n') break;
        else li.addOne(c);
    }
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int k;
        char c;
        scanf("%d %c",&k,&c);
        li.insertOne(k,c);
        li.printAll();
    }
    return 0;
}
