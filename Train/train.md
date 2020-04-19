#### 算法与思路
- 该题的说明很明显，调度站就是一个栈，因此用栈模拟这个调度站就十分合理。而进出调度站的操作就是就是以初始状态为根的一个二叉树结构，找这个进出站的顺序，就是对这个二叉树的遍历。用递归来模拟这种操作则是对二叉树的深度遍历。所以我的算法就是用一个栈和递归操作。
---
#### 遇到的问题及解决办法
- 对于递归操作里面，判断出栈还是入栈的条件比较复杂，对于条件的嵌套如果合理，可以提高递归的效率。所以我仔细研究了这几个条件的嵌套关系。对于条件的分析，我写在了Search()函数的注释里了。
---
#### 时间复杂度和空间复杂度
- 该算法的时间复杂度就是递归操作的时间复杂的，但并不是深度遍历的时间复杂度$O(n)$，因为并不需要遍历所有的情况。但不满足条件时就可以退出。因此时间复杂度小于$O(n)$。空间复杂度则是用例输入顺序的数组a的空间，还有出栈入栈操作数组seq的空间复杂度。这个数组时车厢个数的两倍，但用的bool类型来存储，所以其实用的空间不太大。
---
#### 程序代码
```c++
#include <iostream>
#include <cstdio>

using namespace std;


//seq数组是布尔类型的数组，用来储存出栈入栈顺序，true表示push，false标时pop
//因为需要判断用例给的顺序是否成立，因此我将seq的第一个元素作为成立与否的标识
//对于每一个车厢，都有入栈和出栈两个操作，因此seq的长度为车厢个数最大值的两倍
bool *seq=new bool[3200005];
//seqNum为记录顺序的个数
int seqNum=1;

class Stack{//顺序栈，用来充当列车调度站
public:
    int maxSize;
    int num;
    int *data;
    Stack(int ms);
    ~Stack();
    void push(int x);//入栈
    int pop();//出栈
    int topData();//获得栈顶元素，该不出栈，只用于比较
    bool isEmpty();//栈空
    bool isFull();//栈满

};
Stack::~Stack()
{
    delete []data;
}
bool Stack::isFull()
{
    if(num==maxSize) return true;
    return false;
}
bool Stack::isEmpty()
{
    if(num==0) return true;
    return false;
}
int Stack::topData()
{
    return data[num-1];
}
int Stack::pop()
{
    return data[num--];
}
void Stack::push(int x)
{
    data[num++]=x;
}
Stack::Stack(int ms)
{
    maxSize=ms;
    num=0;
    data=new int[ms];
}

void Search(Stack &s,int *a,int out,int in,const int &n)
{
    //递归模拟出栈入栈操作
    //栈就相当于调度站，元素相当于车厢，因此用栈模拟车厢进出调度站的操作，就能求出出栈入栈的顺序，或者是否存在这个顺序
    if(out==n)//out表示出栈个数，out==n时退出递归
    {
        seq[0]=true;//存在这样的顺序
        return;
    }
    if(in>n)//in表示入栈个数，in>n表示元素已经全部入栈，着只能进行出栈操作
    {
        if(s.topData()!=a[out]) return;//栈顶元素不满足当前顺序，退出
        s.pop();//满足则出栈
        seq[seqNum++]=false;//记录出栈操作，false表示出栈
        Search(s,a,out+1,in,n);//继续递归
    }else
    {
        if(s.isFull())//栈满，只能出栈
        {
            if(s.topData()!=a[out]) return;
            else
            {
                s.pop();
                seq[seqNum++]=false;
                Search(s,a,out+1,in,n);
            }
        }
        else if(s.isEmpty())//栈空，只能入栈
        {
            s.push(in);
            seq[seqNum++]=true;
            Search(s,a,out,in+1,n);

        }
        else//栈既不空，也不满，则既能出栈，又能入栈
        {
            if(s.topData()==a[out])//栈顶元素满足该顺序，出栈
            {
                s.pop();
                seq[seqNum++]=false;
                Search(s,a,out+1,in,n);
            }else//栈顶元素不满足则，入栈
            {
                s.push(in);
                seq[seqNum++]=true;
                Search(s,a,out,in+1,n);
            }
        }
    }
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int *a=new int[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    Stack s=Stack(m);
    seq[0]=false;//出栈入栈记录数组的第一个元素为记录是否成立，初始化为false
    Search(s,a,0,1,n);//进行递归出栈入栈模拟
    if(seq[0])//该顺序成立，则输出出栈入栈顺序
    {
        for(int i=1;i<=2*n;i++)
        {
            if(seq[i])printf("push\n");
            else printf("pop\n");
        }
    }else{printf("No\n");}//不成立，输出No；

    return 0;
}

```