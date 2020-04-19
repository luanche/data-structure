#### 算法与思路
- 该题判断重名，如果之间判断，时间复杂度是$O(n^2)$，效率特别低，肯定不满足这道题对时间的要求，于是考虑用别的算法，去网上查了查字符串的存储可以使用字符串hash，只要找到合适的hash函数，就可以很好的存储字符串，而且用hash存储的方式，对于查找某个字符串的效率特别好，可以之间通过hash函数定义到该字符串的存储位置。而我使用的hash函数的方式为最常用的除留余数法，也最方便写。解决hash冲突的方法也用最方便的链表发，及hash表。
- 至于这个hash函数如果就要好好考虑。我去网上查了查常用的字符串hash的hash函数，对于有意义的字符单词，BKDRhash函数是冲突最低的。于是我就是用BKDRhash函数用来确定hash值。BKDRhash法，是将字符串看作是某个进制的数，然后之间算出hash值。而研究表明，最合适的进制为31、131、1331、13131……等这样的特殊的质数。但如果进制太大，或者字符串太长，算出的hash值就特别大，所以没办法确定一个具体的hash值，于是可以用无符号长整型(unsigned long int),是计算结果自然上溢出，就不用再考虑取余来保证hash值太大的问题。
- 而hash值的计算因为相当于是k进制转10进制的过程。例如字符串"abc"，本来的计算过程是$hash=a{\times}k^2+b{\times}k+c$，而在计算机中，计算这个公式会是$hash=a{\times}k{\times}k+b{\times}k+c$，当字符串很长时，需要计算很多次乘法。于是想到了计算方法讲到的秦九韶算法，就乘法展开为$hash=(a{\times}k+b){\times}k+c$，可以减少计算次数。
---
#### 遇到的问题及解决办法
- 一开始不知道字符串hash的方法，就没有头绪。直接进行查找，嵌套两层循环。但时间特别长，根本过不了。所以必须得换一个，于是去网上看了关于字符串的存储问题，看见了字符串hash。
---
#### 时间复杂度和空间复杂度
- 因为用hash存储，对于字符串的存取和重复查询是比较快的，可以直接通过下标来确定。所以时间复杂度大约为$O(n)$。至于空间复杂的，在冲突少的情况下，大约就是字符串数组的存储空间。冲突多了，会稍微多一点。
---
#### 程序代码
```c++
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

```