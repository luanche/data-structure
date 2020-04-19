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
    //int *arr=new int[n];
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
