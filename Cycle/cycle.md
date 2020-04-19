#### 算法与思路
- 这道题是循环位移，循环位移是每次将第一个移到最后一个，但是如果将字符串首位相连，那么就能这个环里就包括了所有的循环位移的情况。所以我想到的是用循环链表，这样就能在不动两个串的位置的情况下，实现循环的存储。然后只需要判断第二个串是否是第一个循环串的子串，即可判断结果。
---
#### 遇到的问题及解决办法
- 实际这个算法的时间并不是最好的，还有一个更加简单的算法，那就是直接将第一个串重复一遍，然后用string.h库里的子串判断第二个串是否为第一个串的子串即可。或者判断子串时用kmp算法，可以提高判断子串的效率。但是我觉得循环链表的思想确实挺好的，所以我没有为了时间弃用这个算法。
---
#### 时间复杂度和空间复杂度
- 这个算法的时间复杂度估算比较复杂，假设每个字符串的长度平均值为s，一共n组用例，那么时间复杂度大约为$O(n{\times}s^2)$。空间复杂度时存储两个字符串所用的循环链表的空间。
---
#### 程序代码
```c++
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

```