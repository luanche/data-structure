#### �㷨��˼·
- �����������˼·��ͨ����ȱ�������������ʼ״̬����������·���������ҿ�����֮�󣬷����������Ϊ��һ����8�����ֵ�ħ������������ħ������������״̬�ǿ���ö�ٳ����ġ����е�״̬����1-8��ȫ���С�����ͨ���ݹ��㷨�ݹ�����е������������Щȫ�����ǹ̶��ģ����Բ���ÿ�ζ��ݹ顣������ǰ�ݹ�ú�����������ļ��洢�ã�һ��40320��״̬��
- Ȼ��������Щ״̬���������������ֱ任�����������е�״̬���ڽ�״̬��ÿ��״̬��ͨ�����ֱ任�����״̬������ÿ���ڵ�ĳ�����3��ͬ�����Ҳ��3������һ����40320*3=120960������ߡ�����Щ���������һ���ļ�����������Ȼ����дһ��ͼ�ĳ��򣬽���һ���ڽӱ������б����룬ͨ��dijkstra�㷨���ÿ���ڵ㵽��ʼ״̬�����·��������״̬�ͳ���ͨ��״̬�����������ļ�����������
- ���Ҫ���ĸ�״̬����ʼ״̬�����·����ֻ��Ҫ���ö��ֲ����ҵ����״̬�����·�����Ϊ������ɡ�
---
#### ���������⼰����취
- ��Ϊoj�ύ����ʱ�����ܶ��ļ����в��������ֻ�ܽ����е�״̬�Ͷ�Ӧ�ĳ�������Ϊȫ�ֱ�������Ȼ���������ȶ��ļ���Ҫ�죬��Ϊȫ�ֱ������ڱ���ʱ�ͷ����˿ռ䡣���������ʹ�õ��Ǻ�����ͬ�ķ������ǲ����ʿ϶����ر�ߣ���Ϊ��Щֵ���ǹ̶��ˡ�
---
#### ʱ�临�ӶȺͿռ临�Ӷ�
- ����㷨�þú�������ʱ�临�Ӷ��ر�ͣ�����Ҫ���m����ѯ��ÿ����ѯ��ʱ�临�Ӷ�Ϊ$O(log40320)$��m����ѯ��ʱ�临�ӶȾ���$O(mlog40320)$��40320�ǳ��죬����m�ر��ر��ʱ��ʱ�临�Ӷȿ�Լ����$O(m)$���ռ临�ӶȾ��Ǵ洢����״̬�Լ���Ӧ�����·�����ȵ�����Ŀռ䣬��2*40320��int���͵Ŀռ䡣
---
#### �������

##### �ݹ�����ȫ���еĴ���
```c++
#include <iostream>
#include <cstdio>

int N=8;
using namespace std;
int M=0;

FILE *f=fopen("dot_value_data.out","w+");
//���������ļ�

void fun(bool *b,int *a,int n)//�ݹ�����1-8��ȫ���в�������ļ�
{
    if(n==N)
    {
        fprintf(f,"%d ",M++);
        for(int i=0;i<N;i++)
        {
            //printf("%d",a[i]);
            fprintf(f,"%d",a[i]);
        }
        fprintf(f,"\n");
        //printf("\n");
        return;
    }
    bool *nb=new bool[N];
    int *na=new int[N];
    for(int i=0;i<N;i++)
    {
        nb[i]=b[i];
    }
    for(int i=0;i<n;i++)
    {
        na[i]=a[i];
    }
    for(int i=0;i<N;i++)
    {
        if(!nb[i])
        {
            na[n]=i+1;
            nb[i]=true;
            fun(nb,na,n+1);
            nb[i]=false;
        }

    }
}

int main()
{
    int n=1;
    for(int i=N;i>1;i--) n=n*i;
    fprintf(f,"%d\n",n);
    printf("%d\n",n);
    int A[N]={0};
    bool B[N]={false};
    //printf("*****\n");
    //fprintf(f,"*****\n");
    fun(B,A,0);//���õݹ麯������ȫ����
    fclose(f);
    return 0;
}

```
##### ��ÿ��״̬���ڽ�״̬�Ĵ���
```c++
#include <iostream>
#include <cstdio>
/*
30239:35876412-B->73584126
30240:35876421-B->73584216
30241:36124578-C->37624158
*/
using namespace std;

FILE *fr=fopen("data.in","r+");
FILE *fw=fopen("data.out","w+");


char a[40325][9];

bool changeUpDown(char *a,char *b)//���»��б任
{
    for(int i=0;i<8;i++)
    {
        if(a[i]!=b[7-i]) return false;
    }
    return true;
}

bool moveToRight(char *a,char *b)//ѭ�����Ʊ任
{
    for(int i=0;i<3;i++)
    {
        if(a[i]!=b[i+1]) return false;
    }
    if(a[3]!=b[0]) return false;
    for(int i=5;i<8;i++)
    {
        if(a[i]!=b[i-1]) return false;
    }
    if(a[4]!=b[7]) return false;
    return true;
}

bool centralRotation(char *a,char *b)//������ת�仯
{
    if(a[0]!=b[0]||a[3]!=b[3]||a[4]!=b[4]||a[7]!=b[7]) return false;
    if(a[1]!=b[2]||a[2]!=b[5]||a[5]!=b[6]||a[6]!=b[1]) return false;
    return true;
}

bool isAdjacent(char *a,char *b)//�ж��Ƿ��ڽӣ����ж��Ƿ���ͨ�����ֱ仯���
{
    if(changeUpDown(a,b)||moveToRight(a,b)||centralRotation(a,b)) return true;
    return false;
}


int main()
{
    int n;
    fscanf(fr,"%d",&n);
    for(int i=0;i<n;i++)
    {//����ȫ����
        fscanf(fr,"%s",a[i]);
    }
    /*for(int i=0;i<50;i++)
    {
        printf("%s\n",a[i]);
    }
    */
    int k=0;
    fprintf(fw,"%d\n",60480*2);//����ܱ���
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(isAdjacent(a[i],a[j]))
            {//�������нڵ�������ٽ��
                fprintf(fw,"%s %s\n",a[i],a[j]);
                //fprintf(fw,"%d %d\n",i,j);
                k++;
            }
        }
    }
    cout<<k;
    /*
    char a[9],b[9];
    scanf("%s %s",a,b);
    printf("%s %s\n",a,b);
    cout<<centralRotation(a,b);
    */
    fclose(fr);
    fclose(fw);
    return 0;
}

```
##### ����ͼ����dijkstra�㷨�����·�����ȴ���
```c++
#include <iostream>
#include <cstdio>

#define N 40320
#define M 60480

using namespace std;

int maxLen=100000000;//����Ϊ������

FILE *frv=fopen("dot_value_data.in","r+");//�������
FILE *fr=fopen("data.in","r+");//�ڽӱ�
FILE *fw=fopen("value_hight_test.txt","w+");//������

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
    int edgeNum;
    VertexNode();
};
VertexNode::VertexNode()
{
    link=new EdgeNode(-1);
    data=-1;
    edgeNum=0;
}

class Gragh//�����ڽӱ�
{
public:
    VertexNode *verTab;
    int num;
    Gragh();
    void addEdge(int v1,int v2);
    void prinAll();
    int getWeight(int v1,int v2);
};
int Gragh::getWeight(int v1,int v2)//��ñߵĳ��ȣ�1���
{
    EdgeNode *p=verTab[v1].link->next;
    while(p!=NULL)
    {
        if(p->vertex==v2) return 1;
        p=p->next;
    }
    return maxLen;
}
void Gragh::prinAll()//����ڽӱ�������
{
    for(int i=0;i<num;i++)
    {
        EdgeNode *p=verTab[i].link->next;
        fprintf(fw,"%d(%d):",verTab[i].data,i);
        while(p!=NULL)
        {
            fprintf(fw,"->%d(%d)",verTab[p->vertex],p->vertex);
            p=p->next;
        }
        fprintf(fw,"\n");
    }
}
void Gragh::addEdge(int v1,int v2)//��ӱ�
{
    EdgeNode *p=new EdgeNode(v2);
    p->next=verTab[v1].link->next;
    verTab[v1].link->next=p;
    verTab[v1].edgeNum++;
}
Gragh::Gragh()
{
    num=N;
    verTab=new VertexNode[N+5];
}
Gragh g;

int main()
{
    int n;
    fscanf(frv,"%d",&n);
    for(int i=0;i<n;i++)
    {
        int index,da;
        fscanf(frv,"%d %d",&index,&da);//�������нڵ�
        g.verTab[index].data=da;
    }
    int m;
    fscanf(fr,"%d",&m);
    for(int i=0;i<m;i++)
    {
        int v1,v2;
        fscanf(fr,"%d %d",&v1,&v2);//�������б�
        int iv1=0,iv2=0;
        for(int k=0;k<n;k++)
        {
            if(g.verTab[k].data==v1) iv1=k;
            if(g.verTab[k].data==v2) iv2=k;
        }
        g.addEdge(iv2,iv1);
    }
    /*while(1)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        printf("%d\n",g.isAdjac(x,y));
    }*/
    //g.prinAll();
    int *len=new int[n];
    bool *s=new bool[n];
    int v=0;

    //����dijkstra�㷨�����·��
    for(int i=0;i<n;i++)
    {
        len[i]=g.getWeight(0,i);
        s[i]=false;
    }
    s[v]=true;
    len[v]=0;
    for(int i=0;i<n-1;i++)
    {
        int minLen=maxLen;
        int u=v;
        for(int j=0;j<n;j++)
        {
            if(s[j]==false&&len[j]<minLen)
            {
                u=j;
                minLen=len[j];
            }
        }
        s[u]=true;
        //printf("%d\n",g.verTab[u].data);
        for(int k=0;k<n;k++)
        {
            int w=g.getWeight(u,k);
            if(s[k]==false&&w<maxLen&&len[u]+w<len[k])
            {
                len[k]=len[u]+w;
            }
        }
    }
    /*for(int i=0;i<n;i++)
    {//���Ϊ12345678 0�����ĸ�ʽ
        fprintf(fw,"%d %d\n",g.verTab[i].data,len[i]);
    }*/
    fprintf(fw,"{");
    for(int i=0;i<n-1;i++)
    {//���Ϊ����ȫ�ֱ����ĸ�ʽ
        fprintf(fw,"{%d,%d},",g.verTab[i].data,len[i]);
    }
    fprintf(fw,"{%d,%d}}",g.verTab[n-1].data,len[n-1]);
    fclose(frv);
    fclose(fr);
    fclose(fw);
    cout << "complete!" << endl;
    return 0;
}

```
##### ���մ���
```c++
#include <iostream>
#include <cstdio>

#define N 40320

using namespace std;


//�����洢ÿ��״̬����ʼ״̬��Ӧ����̳���
typedef struct Point{
	int value,length;
}Point;


//���Point��������������е�״̬���Լ���ǰ��dijstra�㷨�����ÿ��״̬����ʼ״̬�����·�����ȣ�����ÿ�ֽ����״̬��������ʽ�Ѿ���ǰ�ź���
Point p[N]={{12345678,0},.....,{87654321,1}};
//���������̫���ˣ�ȫ��ճ����markdown�Ϳ�ס�ˡ���Щ���ݿ����������������������������ɣ����������ҾͲ�����

int searchLen(int a)//ֱ��ͨ��״̬�����ֽ��ж��ֲ��ң�ֱ�ӷ��ظ�״̬�����·������
{
    int k=0,l=N-1,m;
    while(k<=l)
    {
        m=k+(l-k)/2;
        if(p[m].value==a) return p[m].length;
        else if(p[m].value>a) l=m-1;
        else k=m+1;
    }
    return -1;
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int a;
        int v=0;
        for(int i=0;i<8;i++)
        {
            scanf("%d",&a);//����״̬�������ؾ����㷨ת��Ϊ��Ӧ������
            v=v*10+a;
        }
        int len=searchLen(v);//ͨ�����ֲ����ҳ����·������
        printf("%d\n",len);
    }

    return 0;
}

```