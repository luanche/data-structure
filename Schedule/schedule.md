#### 算法与思路
- 这道题预先输出任务，每次输出优先级最小的任务。因为每次需要找数组中的最小值，那么这个思想和推排序思想很相似。堆排序的建堆就是，每次都让最小的值在堆顶（小于等于堆）。所以这个题可以用堆排序的方法，每次将最小的元素放在堆顶，输出它即可，输出之后将优先级翻倍，然后再从堆顶调整堆即可。然后考虑当优先级到$2^{32}$即可。
- 因为在调整堆时经常需要比较两个任务，而比较两个任务不单单时比较优先级，当优先级相同时还需要比较名字的ascii码，所以可以把大于小于运算符重载一下，这样就会比较容易比较。
---
#### 遇到的问题及解决办法
- 判断这个优先级是否大于等于$2^{32}$，如果用int或者用unsigned int都是会超范围，然后优先级就会溢出，所以永远不会大于$2^{32}$。所以改成long或者long long即可。
---
#### 时间复杂度和空间复杂度
- 这个算法用的是堆排序的思想，所以时间复杂度可以用堆排序来估计。但并不是所有的点都要排序，而只进行了堆调整m次，所以时间复杂度大约时$O(nlogn)$。空间复杂度就为存储任务的优先级和任务名所用到的空间。
---
#### 程序代码
```c++
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

class Node{//封装一个数据类型，用来存每个任务的任务名和优先级
public:
    long long prio;//优先级
    char *name;//任务名
    Node()
    {
        name=new char[10];
        prio;
    }
    //重载大于和小于运算符
    bool operator>(const Node &b)
    {
        if(prio>b.prio) return true;//比较优先级
        else if(prio<b.prio) return false;
        else//优先级相等比较名字的ascii码，可直接用strcmp()
        {
            if(strcmp(name,b.name)>0) return true;
            return false;
        }
    }
    bool operator<(const Node &b)
    {
        if(prio<b.prio) return true;
        else if(prio>b.prio) return false;
        else
        {
            if(strcmp(name,b.name)<0) return true;
            return false;
        }
    }
};

Node *sche=new Node[4000005];//定义为全局的数组，便于adjust()函数调整

void adjust(int i,int length)
{//堆排序的调整函数
    int k;
    Node temp;
    for(temp=sche[i];2*i+1<length;i=k)
    {
        k=2*i+1;
        if(k<length-1&&sche[k+1]<sche[k]) k++;
        if(temp>sche[k])
        {
            sche[i]=sche[k];
            sche[k]=temp;
        }
        else break;
    }
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++)
    {
        scanf("%lld %s",&sche[i].prio,sche[i].name);
    }
    Node t;
    if(n==0) return 0;//考虑n==0，及没有任务的情况
    for(int i=n/2-1;i>=0;i--)//将sche数组调整为堆
    {
        adjust(i,n);
    }
    int k=n;//表示当前还在的任务数
    for(int i=0;i<m;i++)
    {
        if(sche[0].prio<4294967296)//当优先级小于2^32，输出该任务
        {
            printf("%s\n",sche[0].name);
            sche[0].prio=sche[0].prio*2;//并把优先级翻倍
            adjust(0,k);//调整堆
        }else
        {//优先级>=2^32，删除该任务，及和最后一个任务交换，并k-1；
            Node t=sche[0];
            sche[0]=sche[k-1];
            sche[k-1]=t;
            k--;
            if(k==0) break;//没有任务则退出
        }
    }
    return 0;
}

```