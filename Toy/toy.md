#### 算法与思路
- 这道题正常的思路是通过广度遍历，遍历到初始状态，以求出最短路径。但是我看了题之后，发现这个题因为是一个带8个数字的魔方，对于这种魔方，它的所有状态是可以枚举出来的。所有的状态就是1-8的全排列。可以通过递归算法递归出所有的情况。而且这些全排列是固定的，所以不用每次都递归。可以提前递归好后将它们输出到文件存储好，一共40320种状态。
- 然后利用这些状态，根据它给的三种变换情况，求出所有的状态的邻接状态，每个状态能通过三种变换到别的状态，所以每个节点的出度是3，同样入度也是3。所以一共有40320*3=120960条无向边。将这些边输出到另一个文件储存起来。然后再写一个图的程序，建立一个邻接表，将所有边输入，通过dijkstra算法求出每个节点到初始状态的最短路径，并将状态和长度通过状态排序后输出到文件储存起来。
- 最后要求哪个状态到初始状态的最短路径，只需要利用二分查找找到这个状态的最短路径输出为结果即可。
---
#### 遇到的问题及解决办法
- 因为oj提交代码时，不能对文件进行操作，因此只能将所有的状态和对应的长度声明为全局变量。当然这样声明比读文件还要快，因为全局变量是在编译时就分配了空间。但如果有人使用的是和我相同的方法，那查重率肯定会特别高，因为这些值都是固定了。
---
#### 时间复杂度和空间复杂度
- 这个算法好久好在它的时间复杂度特别低，用例要求的m个查询，每个查询的时间复杂度为$O(log40320)$，m个查询的时间复杂度就是$O(mlog40320)$，40320是常熟，所以m特别特别大时，时间复杂度可约等于$O(m)$。空间复杂度就是存储所有状态以及对应的最短路径长度的数组的空间，及2*40320的int类型的空间。
---
#### 程序代码

##### 递归生成全排列的代码
```c++
#include <iostream>
#include <cstdio>

int N=8;
using namespace std;
int M=0;

FILE *f=fopen("dot_value_data.out","w+");
//结果输出到文件

void fun(bool *b,int *a,int n)//递归生成1-8的全排列并输出到文件
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
    fun(B,A,0);//调用递归函数生成全排列
    fclose(f);
    return 0;
}

```
##### 求每个状态的邻接状态的代码
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

bool changeUpDown(char *a,char *b)//上下换行变换
{
    for(int i=0;i<8;i++)
    {
        if(a[i]!=b[7-i]) return false;
    }
    return true;
}

bool moveToRight(char *a,char *b)//循环右移变换
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

bool centralRotation(char *a,char *b)//中心旋转变化
{
    if(a[0]!=b[0]||a[3]!=b[3]||a[4]!=b[4]||a[7]!=b[7]) return false;
    if(a[1]!=b[2]||a[2]!=b[5]||a[5]!=b[6]||a[6]!=b[1]) return false;
    return true;
}

bool isAdjacent(char *a,char *b)//判断是否邻接，及判断是否能通过三种变化变得
{
    if(changeUpDown(a,b)||moveToRight(a,b)||centralRotation(a,b)) return true;
    return false;
}


int main()
{
    int n;
    fscanf(fr,"%d",&n);
    for(int i=0;i<n;i++)
    {//读入全排列
        fscanf(fr,"%s",a[i]);
    }
    /*for(int i=0;i<50;i++)
    {
        printf("%s\n",a[i]);
    }
    */
    int k=0;
    fprintf(fw,"%d\n",60480*2);//输出总边数
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(isAdjacent(a[i],a[j]))
            {//遍历所有节点和它的临界点
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
##### 构建图并用dijkstra算法求最短路径长度代码
```c++
#include <iostream>
#include <cstdio>

#define N 40320
#define M 60480

using namespace std;

int maxLen=100000000;//定义为无穷大∞

FILE *frv=fopen("dot_value_data.in","r+");//结点输入
FILE *fr=fopen("data.in","r+");//邻接边
FILE *fw=fopen("value_hight_test.txt","w+");//结果输出

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
    int edgeNum;
    VertexNode();
};
VertexNode::VertexNode()
{
    link=new EdgeNode(-1);
    data=-1;
    edgeNum=0;
}

class Gragh//定义邻接表
{
public:
    VertexNode *verTab;
    int num;
    Gragh();
    void addEdge(int v1,int v2);
    void prinAll();
    int getWeight(int v1,int v2);
};
int Gragh::getWeight(int v1,int v2)//获得边的长度，1或∞
{
    EdgeNode *p=verTab[v1].link->next;
    while(p!=NULL)
    {
        if(p->vertex==v2) return 1;
        p=p->next;
    }
    return maxLen;
}
void Gragh::prinAll()//输出邻接表，调试用
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
void Gragh::addEdge(int v1,int v2)//添加边
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
        fscanf(frv,"%d %d",&index,&da);//输入所有节点
        g.verTab[index].data=da;
    }
    int m;
    fscanf(fr,"%d",&m);
    for(int i=0;i<m;i++)
    {
        int v1,v2;
        fscanf(fr,"%d %d",&v1,&v2);//输入所有边
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

    //利用dijkstra算法求最短路径
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
    {//输出为12345678 0这样的格式
        fprintf(fw,"%d %d\n",g.verTab[i].data,len[i]);
    }*/
    fprintf(fw,"{");
    for(int i=0;i<n-1;i++)
    {//输出为定义全局变量的格式
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
##### 最终代码
```c++
#include <iostream>
#include <cstdio>

#define N 40320

using namespace std;


//用来存储每种状态到初始状态对应的最短长度
typedef struct Point{
	int value,length;
}Point;


//这个Point数组里包含了所有得状态，以及提前用dijstra算法求出的每种状态到初始状态的最短路径长度，而且每种结点以状态得数字形式已经提前排好序
Point p[N]={{12345678,0},.....,{87654321,1}};
//这里的数据太多了，全部粘上来markdown就卡住了。这些数据可以用我上面给的三个程序进行生成，所以这里我就不贴了

int searchLen(int a)//直接通过状态得数字进行二分查找，直接返回该状态的最短路径长度
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
            scanf("%d",&a);//输入状态，并用秦九昭算法转化为对应的数字
            v=v*10+a;
        }
        int len=searchLen(v);//通过二分查找找出最短路径长度
        printf("%d\n",len);
    }

    return 0;
}

```