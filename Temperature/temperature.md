#### 算法与思路
- 这个题给的用例对时间要求特别严格，所以普通的算法肯定是不行了。看了题目给的提示，用kd-tree或者range-tree。于是去网上了解了一下kd-tree的说明。kd-tree是不断地通过对x排序和对y排序构建一个平衡二叉树。第一层的结点对x排序，找出中间结点作为根节点。接着递归构建第二层的结点，对y进行排序，以中间结点作为下一层的根节点。不断递归直到将所有结点都添加到树里。查找某个结点就从根节点开始，先判断根节点是否满足，如果查找的点比根节点小，则递归左子树，反之递归右子树，直到把要找的结点找出来。和二叉排序树的思想一样，只是因为是多维的数据，所以是x，y交替进行比较。但这个题是范围查找，所以要不断判断结点是否在范围内。而且如果结点在x1和x2直接，左右子树都要继续递归。所以如果给的范围是包含了整个区间，那么得判断所有的节点，时间很特别慢。
- 这个题最高拿到了85分，哪怕我优化了很多的地方，包括判断时将条件进行嵌套以减少判断次数，也只能将第19个用例得时间提到6100ms，其他得三个用依旧超时。我估计其他三个用例有很多得全覆盖得区间，所以查询就很慢。据说这个题更好的算法是用r-tree，但是r-tree得思想我看不太明白，网上关系r-tree得说明也很少。
---
#### 遇到的问题及解决办法
- 一开始第19个用例得时间接近10000ms，几乎是特别极限得完成了。于是我试着优化这个算法，从存储结点时用节点得地址来存，这样比存下标会更快一点。以及判断节点时将判断条件通过嵌套，避免有的条件重复判断来提升效率。最后将第19个用例得时间提升到了6100ms，其他的三个用例依然是超时，最后只得了85分。我估计这个算法得极限就只能得85分，如果要想得的分更高，只能换别的算法。毕竟如果需要查询的范围覆盖了所有结点，这个算法就得把每个结点都进行判断，效率必定不能提上来。
---
#### 时间复杂度和空间复杂度
- 这个算法得时间复杂度，对于n个结点，m个查询，最好的情况下时间复杂度时$O(mlogn)$，最坏的情况下，时间复杂度则是$O(mn)$。空间复杂度就是n个结点存储的平衡二叉树得空间。
---
#### 程序代码
```c++
#include <iostream>
#include <cstdio>
#include "temperature.h"

using namespace std;
const int SIZE=1<<23;
struct FastIO {
    char inbuf[SIZE];
    char outbuf[SIZE];
    FastIO() {
        setvbuf(stdin,inbuf,_IOFBF,SIZE);
        setvbuf(stdout,outbuf,_IOFBF,SIZE);
    }
}IO;

typedef struct //站点结点，储存位置坐标和温度
{
public:
    int x,y;
    int temper;
}Point;

Point p[500005];

int k;
int x1,y1,x2,y2;//定于全局变量，用于调用接口和后面算法使用
long tatolTemper;

void adjust(Point *arr,int i,int length,bool X)//bool X表示是以x排序还是以y排序，以x排序bool变量X为true
{//堆排序调整函数
    int k;
    Point temp;
    if(X)//以x排序
    {
        for(temp=arr[i];2*i+1<length;i=k)
        {
            k=2*i+1;
            if(k<length-1&&arr[k+1].x>arr[k].x) k++;
            if(temp.x<arr[k].x)
            {
                arr[i]=arr[k];
                arr[k]=temp;
            }
            else break;
        }
    }else//以y排序
    {
        for(temp=arr[i];2*i+1<length;i=k)
        {
            k=2*i+1;
            if(k<length-1&&arr[k+1].y>arr[k].y) k++;
            if(temp.y<arr[k].y)
            {
                arr[i]=arr[k];
                arr[k]=temp;
            }
            else break;
        }
    }

}

void sortArr(Point *arr,int len,bool X)//堆排序
{
    Point t;
    for(int i=len/2-1;i>=0;i--)
    {
        adjust(arr,i,len,X);
    }
    for(int i=len-1;i>0;i--)
    {
          t=arr[0];
          arr[0]=arr[i];
          arr[i]=t;
        adjust(arr,0,i,X);
    }
}

class TreeNode //kd-tree结点
{
public:
    Point *index;//指向站点的在p里的位置所对应的指针
    bool isX;//表示以x为参考还是以y为参考
    TreeNode *lc;
    TreeNode *rc;
    TreeNode(Point *i,bool x)
    {
        isX=x;
        index=i;
        lc=NULL;
        rc=NULL;
    }
};

class Tree
{
public:
    TreeNode *root;
    Tree(){root=NULL;}
};
void makeTree(TreeNode *&rot,int left,int right,bool X)//构建kd-tree
{
    sortArr(p+left,right-left+1,X);
    int m=(left+right)>>1;
    rot=new TreeNode(&p[m],X);
    if(left<=m-1) makeTree(rot->lc,left,m-1,!X);
    if(m+1<=right) makeTree(rot->rc,m+1,right,!X);


}
void rangeSearch(TreeNode *&rot)//kd-tree的范围搜索
{
    //将判断条件嵌套起来，是为了节省时间，因为对于之前以及判断过结点的x,y和全局变量的x,y，后面也需判断，所以为了节省判断的时间
    //递归查询
    if(rot->index->x>=x1)
    {
        if(rot->index->x<=x2)
        {
            if(rot->index->y>=y1)
            {
                if(rot->index->y<=y2)
                {
                    tatolTemper+=(rot->index->temper);
                    k++;
                    if(rot->isX)
                    {
                        if(rot->lc!=NULL) rangeSearch(rot->lc);
                        if(rot->rc!=NULL) rangeSearch(rot->rc);
                    }else
                    {
                        if(rot->lc!=NULL) rangeSearch(rot->lc);
                        if(rot->rc!=NULL) rangeSearch(rot->rc);
                    }
                }else
                {
                    if(rot->isX)
                    {
                        if(rot->lc!=NULL) rangeSearch(rot->lc);
                        if(rot->rc!=NULL) rangeSearch(rot->rc);
                    }else
                    {
                        if(rot->lc!=NULL) rangeSearch(rot->lc);
                    }
                }
            }else
            {
                if(rot->index->y<=y2)
                {
                    if(rot->isX)
                    {
                        if(rot->lc!=NULL) rangeSearch(rot->lc);
                        if(rot->rc!=NULL) rangeSearch(rot->rc);
                    }else
                    {
                        if(rot->rc!=NULL) rangeSearch(rot->rc);
                    }
                }else
                {
                    if(rot->isX)
                    {
                        if(rot->lc!=NULL) rangeSearch(rot->lc);
                        if(rot->rc!=NULL) rangeSearch(rot->rc);
                    }
                }
            }
        }else
        {
            if(rot->index->y>=y1)
            {
                if(rot->index->y<=y2)
                {
                    if(rot->isX)
                    {
                        if(rot->lc!=NULL) rangeSearch(rot->lc);
                    }else
                    {
                        if(rot->lc!=NULL) rangeSearch(rot->lc);
                        if(rot->rc!=NULL) rangeSearch(rot->rc);
                    }
                }else
                {
                    if(rot->isX)
                    {
                        if(rot->lc!=NULL) rangeSearch(rot->lc);
                    }else
                    {
                        if(rot->lc!=NULL) rangeSearch(rot->lc);
                    }
                }
            }else
            {
                if(rot->index->y<=y2)
                {
                    if(rot->isX)
                    {
                        if(rot->lc!=NULL) rangeSearch(rot->lc);
                    }else
                    {
                        if(rot->rc!=NULL) rangeSearch(rot->rc);
                    }
                }else
                {
                    if(rot->isX)
                    {
                        if(rot->lc!=NULL) rangeSearch(rot->lc);
                    }
                }
            }
        }

    }else
    {
        if(rot->index->x<=x2)
        {
            if(rot->index->y>=y1)
            {
                if(rot->index->y<=y2)
                {
                    if(rot->isX)
                    {
                        if(rot->rc!=NULL) rangeSearch(rot->rc);
                    }else
                    {
                        if(rot->lc!=NULL) rangeSearch(rot->lc);
                        if(rot->rc!=NULL) rangeSearch(rot->rc);
                    }
                }else
                {
                    if(rot->isX)
                    {
                        if(rot->rc!=NULL) rangeSearch(rot->rc);
                    }else
                    {
                        if(rot->lc!=NULL) rangeSearch(rot->lc);
                    }
                }
            }else
            {
                if(rot->index->y<=y2)
                {
                    if(rot->isX)
                    {
                        if(rot->rc!=NULL) rangeSearch(rot->rc);
                    }else
                    {
                        if(rot->rc!=NULL) rangeSearch(rot->rc);
                    }
                }else
                {
                    if(rot->isX)
                    {
                        if(rot->rc!=NULL) rangeSearch(rot->rc);
                    }
                }
            }
        }else
        {
            if(rot->index->y>=y1)
            {
                if(rot->index->y<=y2)
                {
                    if(!rot->isX)
                    {
                        if(rot->lc!=NULL) rangeSearch(rot->lc);
                        if(rot->rc!=NULL) rangeSearch(rot->rc);
                    }
                }else
                {
                    if(!rot->isX)
                    {
                        if(rot->lc!=NULL) rangeSearch(rot->lc);
                    }
                }
            }else
            {
                if(rot->index->y<=y2)
                {
                    if(!rot->isX)
                    {
                        if(rot->rc!=NULL) rangeSearch(rot->rc);
                    }
                }
            }
        }
    }
}
int main()
{
    int n=GetNumOfStation();
    for(int i=0;i<n;i++)
    {
        GetStationInfo(i,&(p[i].x),&(p[i].y),&(p[i].temper));
    }
    Tree t=Tree();
    makeTree(t.root,0,n-1,true);//递归构造kd-tree
    while(GetQuery(&x1,&y1,&x2,&y2))
    {
        k=0;
        tatolTemper=0;
        rangeSearch(t.root);
        if(k!=0) Response((tatolTemper/k));//返回平均温度
        else Response(0);//如果k为零，则返回零，不能直接除零
    }
    return 0;
}


```