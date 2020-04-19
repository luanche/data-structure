#### 算法与思路
- 这个题对时间复杂度有一定的要求，所以直接查找，时间复杂度为$O(m*n)$，不能通过所有的用例，所以就要考虑改进算法。因为这个题每次用例是给定一定的结点，之后有多次区间查找都是基于之前给的n个结点。所以先对n个结点排序，之后对于区间的查找就会方便。
- 排序算法用的是堆排序，堆排序的时间复杂度为$O(nlogn)$，快查找的时间复杂度也为$O(nlogn)$，但堆排序我认为比快速排序好写，所以我就用堆排序了。
- 查找算法用的是二分查找，二分查找对于有序的数据查找最快。
---
#### 遇到的问题及解决办法
- 利用二分查找会有找不到元素的情况，对于不同的用例，可能出现左区间是没有的元素，或右区间是没有的元素，或两个区间都是没有元素的情况。这就需要讨论，但是每次在循环里讨论，就降低了代码运算的效率。于是我将a,b两个端点查找函数分开，对于左区间a如果查不到相等的元素，则返回比它大一个的元素的下标，同样的b如果查不到相等的元素，则返回比它小一个的元素的下标。则在main方法的中所有情况元素个数都为$num=b_i-a_i+1$，就不需要额外考虑。
---
#### 时间复杂度和空间复杂度
- 堆排序算法时间复杂度为$O(nlogn)$，二分查找每次查找的时间复杂度为$O(logn)$，则m次对应时间复杂度为$O(mlogn)$。则所以时间复杂度为$O((m+n)logn)$。
- 空间复杂度为n个点储存的空间，以及堆排序所用的额外一点空间。
---
#### 程序代码
```c++
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;
int searchIndexA(int a,int *arr,int len)
{
    //二分查找b的位置
    int k=0,l=len-1,m;
    while(k<=l)
    {
        m=k+(l-k)/2;
        if(arr[m]==a)return m;
        else if(arr[m]>a) l=m-1;
        else k=m+1;
    }
    return k;//如果没找到则返回a比大一个的元素下标
}
int searchIndexB(int a,int *arr,int len)
{
    //二分查找b的位置
    int k=0,l=len-1,m;
    while(k<=l)
    {
        m=k+(l-k)/2;
        if(arr[m]==a) return m;
        else if(arr[m]>a) l=m-1;
        else k=m+1;
    }
    return l;//如果没找到则返回比b小一个的元素下标
}
void adjust(int *arr,int i,int length)
{
    //堆排序调整函数
    int x,temp;
    for(temp=arr[i];2*i+1<length;i=x)
    {
        x=2*i+1;
        if(x<length-1&&arr[x+1]>arr[x]) x++;
        if(temp<arr[x])
        {
            arr[i]=arr[x];
            arr[x]=temp;
        }
        else break;
    }
}

void sortArr(int *arr,int len)
{
    int t;
    for(int i=len/2-1;i>=0;i--)
    {
        adjust(arr,i,len);
    }
    for(int i=len-1;i>0;i--)
    {
        //交换堆顶元素和最后一个元素
        t=arr[0];
        arr[0]=arr[i];
        arr[i]=t;
        //调整堆
        adjust(arr,0,i);
    }
}
int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int arr[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    sortArr(arr,n);//用堆排序将坐标轴上的点进行排序
    for(int i=0;i<m;i++)
    {
        //考虑输入区间左区间比右区间大的情况
            //如果左区间大于右区间则交换左右区间
        int a,b;
        scanf("%d %d",&a,&b);
        //利用二分查找找出左右区间a,b对应的位置
        //通过a,b位置直接算出点的个数
        printf("%d\n",searchIndexB(b,arr,n)-searchIndexA(a,arr,n)+1);
    }
    return 0;
}

```