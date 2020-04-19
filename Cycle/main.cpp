#include <iostream>
#include <cstdio>

using namespace std;

class LinkNode
{//链表结点
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
{//循环链表
public:
    LinkNode *first;//头指针
    LinkNode *last;//尾指针
    int num;//长度
    Link()
    {
        num=0;
        first=new LinkNode('@');//空头节点
        last=first;//连接头和尾形成循环链表
        last->next=first;
    }
    void addOne(char x);
};
void Link::addOne(char x)
{//条件结点
    LinkNode *p=new LinkNode(x);
    p->next=first->next;
    last->next=p;
    last=p;
    num++;
}

int main()
{
    char sa[100001],sb[100001];
    while(scanf("%s %s",sa,sb)!=EOF)//输入两个字符串
    {
        Link s1;
        Link s2;
        int n=0;
        //将两个字符串存入双向链表
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
        bool yes=false;//结果初始化为false
        for(int i=0;i<s1.num*2;i++)//从第一个双向链表头节点开始循环遍历链表两次，i<s1.num*2
        {
            LinkNode *q=s2.first->next;
            LinkNode *r=p;
            int j;
            for(j=0;j<s2.num;j++)//判断s2是否为s1的子串
            {
                if(r->data!=q->data) break;//不同退出
                q=q->next;
                r=r->next;
            }
            if(j==s2.num)//表示是子串
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
