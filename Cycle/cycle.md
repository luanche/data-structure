#### �㷨��˼·
- �������ѭ��λ�ƣ�ѭ��λ����ÿ�ν���һ���Ƶ����һ��������������ַ�����λ��������ô�����������Ͱ��������е�ѭ��λ�Ƶ�������������뵽������ѭ���������������ڲ�����������λ�õ�����£�ʵ��ѭ���Ĵ洢��Ȼ��ֻ��Ҫ�жϵڶ������Ƿ��ǵ�һ��ѭ�������Ӵ��������жϽ����
---
#### ���������⼰����취
- ʵ������㷨��ʱ�䲢������õģ�����һ�����Ӽ򵥵��㷨���Ǿ���ֱ�ӽ���һ�����ظ�һ�飬Ȼ����string.h������Ӵ��жϵڶ������Ƿ�Ϊ��һ�������Ӵ����ɡ������ж��Ӵ�ʱ��kmp�㷨����������ж��Ӵ���Ч�ʡ������Ҿ���ѭ�������˼��ȷʵͦ�õģ�������û��Ϊ��ʱ����������㷨��
---
#### ʱ�临�ӶȺͿռ临�Ӷ�
- ����㷨��ʱ�临�Ӷȹ���Ƚϸ��ӣ�����ÿ���ַ����ĳ���ƽ��ֵΪs��һ��n����������ôʱ�临�Ӷȴ�ԼΪ$O(n{\times}s^2)$���ռ临�Ӷ�ʱ�洢�����ַ������õ�ѭ������Ŀռ䡣
---
#### �������
```c++
#include <iostream>
#include <cstdio>

using namespace std;

class LinkNode
{//������
public:
    char data;
    LinkNode *next;
    LinkNode(char x)
    {
        data=x;
        next=NULL;
    }
};
class Link
{//ѭ������
public:
    LinkNode *first;//ͷָ��
    LinkNode *last;//βָ��
    int num;//����
    Link()
    {
        num=0;
        first=new LinkNode('@');//��ͷ�ڵ�
        last=first;//����ͷ��β�γ�ѭ������
        last->next=first;
    }
    void addOne(char x);
};
void Link::addOne(char x)
{//�������
    LinkNode *p=new LinkNode(x);
    p->next=first->next;
    last->next=p;
    last=p;
    num++;
}

int main()
{
    char sa[100001],sb[100001];
    while(scanf("%s %s",sa,sb)!=EOF)//���������ַ���
    {
        Link s1;
        Link s2;
        int n=0;
        //�������ַ�������˫������
        while(sa[n]!='\0')
        {
            s1.addOne(sa[n]);
            n++;
        }
        n=0;
        while(sb[n]!='\0')
        {
            s2.addOne(sb[n]);
            n++;
        }
        if(s1.num!=s2.num)
        {
            printf("NO\n");
            continue;
        }
        LinkNode *p=s1.first->next;
        bool yes=false;//�����ʼ��Ϊfalse
        for(int i=0;i<s1.num*2;i++)//�ӵ�һ��˫������ͷ�ڵ㿪ʼѭ�������������Σ�i<s1.num*2
        {
            LinkNode *q=s2.first->next;
            LinkNode *r=p;
            int j;
            for(j=0;j<s2.num;j++)//�ж�s2�Ƿ�Ϊs1���Ӵ�
            {
                if(r->data!=q->data) break;//��ͬ�˳�
                q=q->next;
                r=r->next;
            }
            if(j==s2.num)//��ʾ���Ӵ�
            {
                yes=true;
                break;
            }
            p=p->next;
        }
        if(yes) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}

```