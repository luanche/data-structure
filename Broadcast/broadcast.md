#### �㷨��˼·
- ������Ҫ�ڴ��ڽ����������߻�վ������С��20km�Ĵ�ׯ���ܽ���ͬһ�ֻ�վ���ж��Ƿ���Խ����������⽨ģ����ׯ�ɱ�ʾΪ��㣬����С��20km��ʾ���������һ������ߣ���������վ���ʾ��ͼ������ɫ�����ֻ�վ����������ɫ�����������ͽ�ģΪͼ��ɫ���⣬������������ɫ�Ƿ���Զ�ͼ�Ľ�������ɫ����ô������Ҫʹ��ͼ�ṹ������ͼ�����õ����ڽӱ���Ϊ�߱Ƚ��ٵĻ���ʡ�ռ䣬����ʡ�㷨��ʱ�䡣����ͼ���б�����ɫ����Ҫ�õ���ȱ������͵ý����������������й�ȱ��������õ���ʱ��ʽ���У����ڲ������ɾ�����ȽϷ��㡣��ʵҲ������ѭ�����У�����̫���ж϶��е���󳤶ȡ�
- ��ô���������㷨���Ǵ�һ����㿪ʼ��ͼ���й�ȱ��������ڽ���Ų�ͬ��ɫ������������ڽ���Լ���ɫ������ô�ж����Ƿ����㷴ɫ�����������Ϳ�ֱ���˳���������������������������н�㶼�������ڽ�㷴ɫ����ô������Ϊ1��
- ��Ϊֻ��������ɫ���������ֱ����int���ʹ洢�Ƿ���ɫ�����ŵ�ʲô��ɫ����int����ֻ�������������Ƚ��˷ѿռ䡣���Կ���������bool�������洢����Ƿ��ǹ��ͱ�ǵ�ʲô��ɫ�������ͽ�ʡ�˴����ռ䡣
---
#### ���������⼰����취
- �ʼ���õ�����ͼ����Ϊ֮ǰһ�����õ�����ͼ����ֱ���õ�֮ǰ�ǵ����ͼ�Ķ���Ĵ������ĵģ����³�����һֱ���ԡ���������Ӧ��ʹ������ͼ�����ǽ�����Ϊ����ͼ������ȷ�ˡ���ʵ����⻹��Ƚϼ򵥣���ϸһ���û���⡣
---
#### ʱ�临�ӶȺͿռ临�Ӷ�
- ����㷨��ʱ�临�ӶȾ��Ǳ���ͼ��ʱ�临�Ӷȣ���TSP�����ʱ�临�Ӷ���ͬ��Ϊ$O(n)$,��������֮���̫�࣬ʱ�临�ӶȻ��һЩ��
- �ռ临�ӶȾ���ͼ�洢�ṹ���еĿռ䣬�Լ�������ȱ������õĶ��еĿռ临�Ӷȡ���Ϊ�����õ��������ͱ��ٵ�����£����õĿռ仹�ǱȽ��١�������ɫ���õĿռ��ҽ�����Ϊ����bool���ͣ�����int���ͻ���short�������õĿռ��ٺܶࡣ
---
#### �������
```c++
#include <iostream>
#include <cstdio>

using namespace std;

//�ö�����ʵ�ֹ�ȱ���
class QueueNode//��ʽ���н��
{
public:
    int data;
    QueueNode *next;
    QueueNode(int x):data(x),next(NULL){}
};
class Queue//��ʽ����
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
    rear->next=new QueueNode(x);//������
    rear=rear->next;
}
int Queue::outQueue()
{
    QueueNode *p=head->next;
    head->next=p->next;//������
    int x=p->data;
    if(rear==p) rear=head;
    delete p;
    return x;
}
Queue::Queue()
{
    head=new QueueNode(-1);//����ͷ���
    rear=head;
}
class EdgeNode//�߽��
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
class VertexNode//����
{
public:
    int data;
    EdgeNode *link;
    bool isMark;//�жϸýڵ��Ƿ񱻱�ǹ�
    bool color;//�洢�ý�����ɫ(���ô�ׯ�����ߵ�����)����Ϊֻ���������ͣ�����ֻ��bool�;Ϳ���
    VertexNode();
};
VertexNode::VertexNode()//����ʼ��
{
    link=new EdgeNode(-1);
    data=-1;
    isMark=false;
    color=false;
}

class Gragh
{//�����ڽӱ�
public:
    VertexNode *verTab;
    Gragh(int n);
    void addEdge(int v1,int v2);
};
void Gragh::addEdge(int v1,int v2)
{//��ӱ߲���
    EdgeNode *p=new EdgeNode(v2);
    p->next=verTab[v1].link->next;
    verTab[v1].link->next=p;
}
Gragh::Gragh(int n)
{//ͼ��ʼ��
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
        //������Ŀ����ȷ��Ϊ˫��ͼ������v1,v2��㣬��Ҫ��ӱ�v1->v2,�Լ�v2->v1
        g.addEdge(v1,v2);
        g.addEdge(v2,v1);
    }
    Queue q;
    g.verTab[1].isMark=true;//����һ������ǣ������
    q.enQueue(g.verTab[1].data);
    int yes=1;//����������
    while(!q.isEmpty())//���ӿ�ʱ����ʾ���нڵ�������ˣ����˳�ѭ��
    {
        int x=q.outQueue();//������
        EdgeNode *p=g.verTab[x].link->next;
        while(p!=NULL)//�������Խڵ�x�������ڽӵ�
        {
            if(g.verTab[p->vertex].isMark)//�жϸý���Ƿ񱻱�ǹ�
            {
                //�����ǹ����жϱ�ǵ���ɫ�Ƿ�ͽ��x��ɫ
                if(g.verTab[p->vertex].color==g.verTab[x].color)
                {
                    yes=-1;//������Ƿ�ɫ����˵��������Ҫ�󣬽��Ϊ-1�����˳�ѭ��
                    break;
                }
            }else
            {
                //���û��ǹ����򽫽���ŷ�ɫ������¼����ѱ���ǣ�Ȼ�󽫸ý�����
                g.verTab[p->vertex].color=!g.verTab[x].color;
                g.verTab[p->vertex].isMark=true;
                q.enQueue(p->vertex);
            }
            p=p->next;
        }
    }
    printf("%d\n",yes);//������
    return 0;
}

```