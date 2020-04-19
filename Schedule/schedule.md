#### �㷨��˼·
- �����Ԥ���������ÿ��������ȼ���С��������Ϊÿ����Ҫ�������е���Сֵ����ô���˼���������˼������ơ�������Ľ��Ѿ��ǣ�ÿ�ζ�����С��ֵ�ڶѶ���С�ڵ��ڶѣ����������������ö�����ķ�����ÿ�ν���С��Ԫ�ط��ڶѶ�����������ɣ����֮�����ȼ�������Ȼ���ٴӶѶ������Ѽ��ɡ�Ȼ���ǵ����ȼ���$2^{32}$���ɡ�
- ��Ϊ�ڵ�����ʱ������Ҫ�Ƚ��������񣬶��Ƚ��������񲻵���ʱ�Ƚ����ȼ��������ȼ���ͬʱ����Ҫ�Ƚ����ֵ�ascii�룬���Կ��԰Ѵ���С�����������һ�£������ͻ�Ƚ����ױȽϡ�
---
#### ���������⼰����취
- �ж�������ȼ��Ƿ���ڵ���$2^{32}$�������int������unsigned int���ǻᳬ��Χ��Ȼ�����ȼ��ͻ������������Զ�������$2^{32}$�����Ըĳ�long����long long���ɡ�
---
#### ʱ�临�ӶȺͿռ临�Ӷ�
- ����㷨�õ��Ƕ������˼�룬����ʱ�临�Ӷȿ����ö����������ơ������������еĵ㶼Ҫ���򣬶�ֻ�����˶ѵ���m�Σ�����ʱ�临�Ӷȴ�Լʱ$O(nlogn)$���ռ临�ӶȾ�Ϊ�洢��������ȼ������������õ��Ŀռ䡣
---
#### �������
```c++
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

class Node{//��װһ���������ͣ�������ÿ������������������ȼ�
public:
    long long prio;//���ȼ�
    char *name;//������
    Node()
    {
        name=new char[10];
        prio;
    }
    //���ش��ں�С�������
    bool operator>(const Node &b)
    {
        if(prio>b.prio) return true;//�Ƚ����ȼ�
        else if(prio<b.prio) return false;
        else//���ȼ���ȱȽ����ֵ�ascii�룬��ֱ����strcmp()
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

Node *sche=new Node[4000005];//����Ϊȫ�ֵ����飬����adjust()��������

void adjust(int i,int length)
{//������ĵ�������
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
    if(n==0) return 0;//����n==0����û����������
    for(int i=n/2-1;i>=0;i--)//��sche�������Ϊ��
    {
        adjust(i,n);
    }
    int k=n;//��ʾ��ǰ���ڵ�������
    for(int i=0;i<m;i++)
    {
        if(sche[0].prio<4294967296)//�����ȼ�С��2^32�����������
        {
            printf("%s\n",sche[0].name);
            sche[0].prio=sche[0].prio*2;//�������ȼ�����
            adjust(0,k);//������
        }else
        {//���ȼ�>=2^32��ɾ�������񣬼������һ�����񽻻�����k-1��
            Node t=sche[0];
            sche[0]=sche[k-1];
            sche[k-1]=t;
            k--;
            if(k==0) break;//û���������˳�
        }
    }
    return 0;
}

```