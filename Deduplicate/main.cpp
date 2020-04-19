#include <iostream>
#include <cstdio>
#include <cstring>

#define MAXSIZE 600001

using namespace std;

//BKDRhash

char str[MAXSIZE][45];//字符串数组，用于储存输入的菜名


//hash表的存储结构和邻接表的存储结构几乎相同
class LinkNode//hash表用于解决冲突的链结点
{
public:
    char *data;
    LinkNode *link;
    bool isDup;//是否已重名的标志，因为考虑到重名只输出一次，所以用这个bool类型的isDup标记
    LinkNode(char *c)
    {
        isDup=false;
        data=c;
    }
};

class TabNode//hash表的结点
{
public:
    LinkNode *first;
    TabNode()
    {
        first=NULL;
    }
};

class HashTable//hash结构定义
{
public:
    TabNode *tab;
    HashTable()
    {
        tab=new TabNode[MAXSIZE];
    }
};

//BKDRHash，是构造字符串hash的很好的一种hash函数，相当于把字符串看作是一个一定进制的数，计算对应的hash值
//而这个进制，有人经过多次实现表明用取31或131或1331...这样的数，冲突的可能性会很小
//但是冲突是不能避免的，只能降低，所以解决hash冲突也是必须的
unsigned long BKDRHash(char *s)
{
    unsigned long adeci=131;//进制
    unsigned long hashValue=0;//hashValue为字符串的hash值，初始化为0
    //用无符号长整型unsigned long 存储hash值，计算hash值是不用考虑值过大的问题，如果值太大，使它自然上溢出即可
    for(int i=0;s[i]!='\0';i++)
    {
        //计算hash值
        hashValue=hashValue*adeci+(s[i]-'a');//利用秦九韶算法将表达式展开可以减少运算量
    }
    return hashValue%MAXSIZE;//对最大数组长度取余(除留余数法)
}
void hashColli(TabNode &tn,char *s)//解决hash冲突
{
    //用链表法，解决hash冲突比较方便，也比较好实现
    LinkNode *p=new LinkNode(s);
    p->link=tn.first;
    tn.first=p;
}

int main()
{
    int n;
    HashTable ht;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%s",str[i]);
        int index=BKDRHash(str[i]);//计算hash值
        LinkNode *p=ht.tab[index].first;
        while(p!=NULL)//遍历该下标位置对应的所有字符串
        {
            if(strcmp(p->data,str[i])==0)//如果字符串相同，表示重名了
            {
                if(!p->isDup)//如果没有输出过重名则输出，并将isDup标记为true，下一次再重名就不再输出
                {
                    p->isDup=true;
                    printf("%s\n",p->data);
                    break;
                }else break;
            }
            p=p->link;
        }
        if(p==NULL)//如果遍历完了依然没有重名，则之间将字符串插入该位置的链即可
        {
            hashColli(ht.tab[index],str[i]);
        }
    }
    
    return 0;
}
