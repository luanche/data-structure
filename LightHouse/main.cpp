#include<cstdio>
#include <iostream>
#define N 4000001

using namespace std;

typedef long long ll;
typedef struct Point{
	ll x,y;
}Point;//�����ṹ��

ll *b=new ll[N];
ll y[N];

void adjust(Point *arr,int i,int length)//����������Ѻ���
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

void sortArr(Point *arr,int len)//������
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
			if(k<ic) sum+=ic-k;//��˳��Ը���
		}
		if(k<ic&&c[k]<=b[j])a[i++]=c[k++];
	}
}


void mergeSort(ll *y,int lo,int hi)//�鲢����
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
	sortArr(ps,n);//��x��߶Խ���������
	for(int i=0;i<n;i++)
    {
        //��Ϊ������Ҫ��y���й鲢���򣬶�x����Ѿ�û������
        //���Խ�yȥ��������������y[]�У����ں���Ĺ鲢������˳���
        y[i]=ps[i].y;
    }
	mergeSort(y,0,n);//��y���й鲢����
	printf("%lld\n",sum);
	return 0;
}
