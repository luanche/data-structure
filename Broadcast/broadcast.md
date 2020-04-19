#### 算法与思路
- 本题是要在存在建立两中无线基站，距离小于20km的村庄不能建立同一种基站，判断是否可以建立。将本题建模，村庄可表示为结点，距离小于20km表示两个结点有一条无向边，而建立基站则表示对图进行着色，两种基站就是两种颜色。于是这道题就建模为图着色问题，问题是两种颜色是否可以对图的结点进行着色。那么，就需要使用图结构来储存图，我用的是邻接表，因为边比较少的话节省空间，还节省算法的时间。而对图进行遍历着色，需要用到广度遍历，就得建立队列来辅助进行广度遍历。我用到的时链式队列，对于插入结点和删除结点比较方便。其实也可以用循环队列，但不太好判断队列的最大长度。
- 那么，这道题的算法就是从一个结点开始对图进行广度遍历，相邻结点着不同颜色，如果发现相邻结点以及着色过，那么判断它是否满足反色，如果不满足就可直接退出遍历输出结果，如果遍历完了所有结点都满足相邻结点反色，那么输出结果为1。
- 因为只有两种颜色，所以如果直接用int类型存储是否着色过，着的什么颜色，那int类型只用了三个数，比较浪费空间。所以可以用两个bool类型来存储结点是否标记过和标记的什么颜色。这样就节省了大量空间。
---
#### 遇到的问题及解决办法
- 最开始我用的有向图，因为之前一道题用的有向图，我直接用的之前那道题对图的定义的代码来改的，导致程序结果一直不对。后来明白应该使用无向图，于是将它改为有向图，就正确了。其实这个题还算比较简单，仔细一点就没问题。
---
#### 时间复杂度和空间复杂度
- 这个算法的时间复杂度就是遍历图的时间复杂度，和TSP问题的时间复杂度相同，为$O(n)$,但如果结点之间边太多，时间复杂度会高一些。
- 空间复杂度就是图存储结构所有的空间，以及辅助广度遍历所用的队列的空间复杂度。因为都是用的链表，结点和边少的情况下，所用的空间还是比较少。而且颜色所用的空间我将它简化为两个bool类型，比用int类型或者short类型所用的空间少很多。
---
#### 程序代码
```c++
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

```