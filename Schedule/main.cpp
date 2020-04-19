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
