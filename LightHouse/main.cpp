#include<cstdio>
#include <iostream>
#define N 4000001

using namespace std;

typedef long long ll;
typedef struct Point{
	ll x,y;
}Point;//坐标点结构体

ll *b=new ll[N];
ll y[N];

void adjust(Point *arr,int i,int length)//堆排序调整堆函数
{
    int k;
    Point temp;
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
}

void sortArr(Point *arr,int len)//堆排序
{
    Point t;
    for(int i=len/2-1;i>=0;i--)
    {
        adjust(arr,i,len);
    }
    for(int i=len-1;i>0;i--)
    {
        t=arr[0];
        arr[0]=arr[i];
        arr[i]=t;
        adjust(arr,0,i);
    }
}
ll sum=0;
void Merge(ll *y,int l,int m,int h)
{
	ll *a=y+l,*c=y+m;
	int ib=m-l,ic=h-m;
	for(int i=0;i<ib;b[i]=a[i++]);
	for(int i=0,j=0,k=0;j<ib;)
	{
		if(ic<=k||b[j]<c[k])
        {
			a[i++]=b[j++];
			if(k<ic) sum+=ic-k;//求顺序对个数
		}
		if(k<ic&&c[k]<=b[j])a[i++]=c[k++];
	}
}


void mergeSort(ll *y,int lo,int hi)//归并排序
{
	if(hi-lo<2)return;
	int mi=(hi+lo)>>1;
	mergeSort(y,lo,mi);
	mergeSort(y,mi,hi);
	Merge(y,lo,mi,hi);
}
int main()
{
	int n;
	scanf("%d",&n);
	Point *ps=new Point[n];
	for(int i=0;i<n;i++)
    {
        scanf("%lld %lld",&ps[i].x,&ps[i].y);
    }
	sortArr(ps,n);//按x左边对结点进行排序
	for(int i=0;i<n;i++)
    {
        //因为后面需要将y进行归并排序，而x左边已经没有用了
        //所以将y去除单独放在数组y[]中，便于后面的归并排序求顺序对
        y[i]=ps[i].y;
    }
	mergeSort(y,0,n);//对y进行归并排序
	printf("%lld\n",sum);
	return 0;
}
