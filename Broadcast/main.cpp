#include <iostream>
#include <cstdio>

using namespace std;

//用队列来实现广度遍历
class QueueNode//链式队列结点
{
public:
    int data;
    QueueNode *next;
    QueueNode(int x):data(x),next(NULL){}
};
class Queue//链式队列
{
public:
    QueueNode *head;
    QueueNode *rear;
    Queue();
    void enQueue(int x);
    int outQueue();
    bool isEmpty();

};
bool Queue::isEmpty()
{
    if(head==rear) return true;
    return false;
}
void Queue::enQueue(int x)
{
    rear->next=new QueueNode(x);//结点入队
    rear=rear->next;
}
int Queue::outQueue()
{
    QueueNode *p=head->next;
    head->next=p->next;//结点出队
    int x=p->data;
    if(rear==p) rear=head;
    delete p;
    return x;
}
Queue::Queue()
{
    head=new QueueNode(-1);//带空头结点
    rear=head;
}
class EdgeNode//边结点
{
public:
    int vertex;
    EdgeNode *next;
    EdgeNode(int v);
};
EdgeNode::EdgeNode(int v)
{
    vertex=v;
    next=NULL;
}
class VertexNode//点结点
{
public:
    int data;
    EdgeNode *link;
    bool isMark;//判断该节点是否被标记过
    bool color;//存储该结点的着色(及该村庄的无线电类型)，因为只有两种类型，所以只用bool型就可以
    VertexNode();
};
VertexNode::VertexNode()//结点初始化
{
    link=new EdgeNode(-1);
    data=-1;
    isMark=false;
    color=false;
}

class Gragh
{//定义邻接表
public:
    VertexNode *verTab;
    Gragh(int n);
    void addEdge(int v1,int v2);
};
void Gragh::addEdge(int v1,int v2)
{//添加边操作
    EdgeNode *p=new EdgeNode(v2);
    p->next=verTab[v1].link->next;
    verTab[v1].link->next=p;
}
Gragh::Gragh(int n)
{//图初始化
    verTab=new VertexNode[n+1];
    for(int i=1;i<=n;i++)
    {
        verTab[i].data=i;
    }
}
int main()
{
    setvbuf(stdin,new char[1<<20],_IOFBF,1<<20);
    setvbuf(stdout,new char[1<<20],_IOFBF,1<<20);
    int n,m;
    scanf("%d %d",&n,&m);
    Gragh g=Gragh(n);
    for(int i=0;i<m;i++)
    {
        int v1,v2;
        scanf("%d %d",&v1,&v2);
        //根据题目可以确定为双向图，所有v1,v2结点，需要添加边v1->v2,以及v2->v1
        g.addEdge(v1,v2);
        g.addEdge(v2,v1);
    }
    Queue q;
    g.verTab[1].isMark=true;//将第一个结点标记，并入队
    q.enQueue(g.verTab[1].data);
    int yes=1;//用来储存结果
    while(!q.isEmpty())//当队空时，表示所有节点遍历完了，则退出循环
    {
        int x=q.outQueue();//结点出队
        EdgeNode *p=g.verTab[x].link->next;
        while(p!=NULL)//遍历出对节点x的所有邻接点
        {
            if(g.verTab[p->vertex].isMark)//判断该结点是否被标记过
            {
                //如果标记过则判断标记的颜色是否和结点x反色
                if(g.verTab[p->vertex].color==g.verTab[x].color)
                {
                    yes=-1;//如果不是反色，则说明不满足要求，结果为-1，并退出循环
                    break;
                }
            }else
            {
                //如果没标记过，则将结点着反色，并记录结点已被标记，然后将该结点入队
                g.verTab[p->vertex].color=!g.verTab[x].color;
                g.verTab[p->vertex].isMark=true;
                q.enQueue(p->vertex);
            }
            p=p->next;
        }
    }
    printf("%d\n",yes);//输出结果
    return 0;
}
