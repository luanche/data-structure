#include <iostream>
#include <cstdio>

using namespace std;

class EdgeNode//�߽ڵ�
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
class VertexNode//��ڵ�
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
    link=new EdgeNode(-1);//����ͷ��㣬���ڲ���
    data=-1;
    edgeNum=0;
    hight=1;
}

class Gragh
{//�����ڽӱ�
public:
    VertexNode *verTab;
    int num;
    Gragh(int n);
    void addEdge(int v1,int v2);
};
void Gragh::addEdge(int v1,int v2)//��ӱ�
{
    EdgeNode *p=new EdgeNode(v2);
    p->next=verTab[v1].link->next;
    verTab[v1].link->next=p;
    verTab[v2].edgeNum++;//�ڵ�v2���+1
}
Gragh::Gragh(int n)
{//��ʼ���ڽӱ�
    num=n;
    verTab=new VertexNode[n+1];
    verTab[0].edgeNum=-1;
    for(int i=1;i<=n;i++)
    {
        verTab[i].data=i;
    }
}

class Stack{//����˳��ջ
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
{//��ʼ��ջ
    maxSize=ms;
    data=new int[ms];
    num=0;
}
bool Stack::isEmpty()
{//�ж�ջ��
    if(num==0) return true;
    return false;
}

int Stack::pop()
{//��ջ
    return data[--num];
}
void Stack::push(int x)
{//��ջ
    data[num++]=x;
}
int getMax(int a,int b)
{//�Ƚ����ֵ
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
        g.addEdge(v1,v2);//����ߣ������
    }
    Stack s=Stack(n);
    for(int i=1;i<=n;i++)
    {
        if(g.verTab[i].edgeNum==0)
        {//�����Ϊ0�Ľ����ջ
            s.push(g.verTab[i].data);
        }
    }
    //�������������㷨����󳤶ȡ�
    int maxHight=1;//��ʼ����󳤶�Ϊ1
    if(n==0) maxHight=0;//���ǵ��ڵ���Ϊ0���������󳤶�Ϊ0
    while(!s.isEmpty())//ֱ��ջΪ�գ���ʾ�����������н��
    {
        int v=s.pop();//����ջ
        EdgeNode *p=g.verTab[v].link->next;
        while(p!=NULL)
        {//������ջ���
            g.verTab[p->vertex].hight=getMax(g.verTab[p->vertex].hight,g.verTab[v].hight+1);//��v������߶ȸ���ÿ���ڽӵ�����߶�
            maxHight=getMax(g.verTab[p->vertex].hight,maxHight);//�������hight��maxHight�������maxHight
            g.verTab[p->vertex].edgeNum--;//ɾ�����v�����������ڽӵ����ȼ�һ
            if(g.verTab[p->vertex].edgeNum==0) s.push(p->vertex);//������Ϊ0���򽫸ýڵ���ջ
            p=p->next;
        }
    }
    printf("%d\n",maxHight);

    return 0;
}
