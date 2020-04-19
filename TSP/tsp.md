#### 算法与思路
- 这个题时为了找最长路径，而不是最短路径。最短路径用dijstra算法，但最长路径不行。而最长路径的求法和拓扑排序的算法有些相似。但求最大路径的方式和dijstra求最短路径的不断更新结点最短路径长度的方式有些像是。拓扑排序能求出一个包括所有结点的序列。最大路就包含在这个路径当中，所以最大路径长度就可以通过拓扑排序的过程实时更新。因此需要对图进行遍历，于是考虑用深度遍历遍历图，就得利用栈。而图的结构用的是邻接表。
---
#### 遇到的问题及解决办法
- 关于更新最大路径长度，拓扑排序算法可以求出每个结点的最大路径，全部更新完后，如果在通过遍历去求最大值，就得再浪费一定的时间。于是就在排序过程中直接跟新最大长度，可以节省一部分时间。
---
#### 时间复杂度和空间复杂度
- 这个算法时间复杂度为遍历图的时间复杂度，及为$O(n)$，但每个结点都需遍历它的所有邻接点，找出删除该节点后，入度变为0的邻接点，将其入栈。如果对于边较多的图，时间会相对慢一点。空间复杂度及为邻接表的存储空间，栈的空间。因为栈用的是顺序栈，而且因为不能确定栈的最大长度，所以必须定义和结点数相同的栈空间。
---
#### 程序代码
```c++
#include <iostream>
#include <cstdio>

using namespace std;

class EdgeNode//边节点
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
class VertexNode//点节点
{
public:
    int data;
    EdgeNode *link;
    int edgeNum;
    int hight;
    VertexNode();
};
VertexNode::VertexNode()
{
    link=new EdgeNode(-1);//带空头结点，便于插入
    data=-1;
    edgeNum=0;
    hight=1;
}

class Gragh
{//定义邻接表
public:
    VertexNode *verTab;
    int num;
    Gragh(int n);
    void addEdge(int v1,int v2);
};
void Gragh::addEdge(int v1,int v2)//添加边
{
    EdgeNode *p=new EdgeNode(v2);
    p->next=verTab[v1].link->next;
    verTab[v1].link->next=p;
    verTab[v2].edgeNum++;//节点v2入度+1
}
Gragh::Gragh(int n)
{//初始化邻接表
    num=n;
    verTab=new VertexNode[n+1];
    verTab[0].edgeNum=-1;
    for(int i=1;i<=n;i++)
    {
        verTab[i].data=i;
    }
}

class Stack{//定义顺序栈
public:
    int maxSize;
    int num;
    int *data;
    Stack(int ms);
    void push(int x);
    int pop();
    bool isEmpty();
};
Stack::Stack(int ms)
{//初始化栈
    maxSize=ms;
    data=new int[ms];
    num=0;
}
bool Stack::isEmpty()
{//判断栈空
    if(num==0) return true;
    return false;
}

int Stack::pop()
{//出栈
    return data[--num];
}
void Stack::push(int x)
{//入栈
    data[num++]=x;
}
int getMax(int a,int b)
{//比较最大值
    if(a>b) return a;
    return b;
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
        g.addEdge(v1,v2);//加入边，有向边
    }
    Stack s=Stack(n);
    for(int i=1;i<=n;i++)
    {
        if(g.verTab[i].edgeNum==0)
        {//将入度为0的结点入栈
            s.push(g.verTab[i].data);
        }
    }
    //利用拓扑排序算法求最大长度。
    int maxHight=1;//初始化最大长度为1
    if(n==0) maxHight=0;//考虑到节点数为0的情况，最大长度为0
    while(!s.isEmpty())//直到栈为空，表示遍历完了所有结点
    {
        int v=s.pop();//结点出栈
        EdgeNode *p=g.verTab[v].link->next;
        while(p!=NULL)
        {//遍历出栈结点
            g.verTab[p->vertex].hight=getMax(g.verTab[p->vertex].hight,g.verTab[v].hight+1);//用v结点最大高度更新每个邻接点的最大高度
            maxHight=getMax(g.verTab[p->vertex].hight,maxHight);//如果结点的hight比maxHight，则更新maxHight
            g.verTab[p->vertex].edgeNum--;//删除结点v，及将它的邻接点的入度减一
            if(g.verTab[p->vertex].edgeNum==0) s.push(p->vertex);//如果入度为0，则将该节点入栈
            p=p->next;
        }
    }
    printf("%d\n",maxHight);

    return 0;
}

```