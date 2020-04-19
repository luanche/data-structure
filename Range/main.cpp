#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;
int searchIndexA(int a,int *arr,int len)
{
    //���ֲ���b��λ��
    int k=0,l=len-1,m;
    while(k<=l)
    {
        m=k+(l-k)/2;
        if(arr[m]==a)return m;
        else if(arr[m]>a) l=m-1;
        else k=m+1;
    }
    return k;//���û�ҵ��򷵻�a�ȴ�һ����Ԫ���±�
}
int searchIndexB(int a,int *arr,int len)
{
    //���ֲ���b��λ��
    int k=0,l=len-1,m;
    while(k<=l)
    {
        m=k+(l-k)/2;
        if(arr[m]==a) return m;
        else if(arr[m]>a) l=m-1;
        else k=m+1;
    }
    return l;//���û�ҵ��򷵻ر�bСһ����Ԫ���±�
}
void adjust(int *arr,int i,int length)
{
    //�������������
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
        //�����Ѷ�Ԫ�غ����һ��Ԫ��
        t=arr[0];
        arr[0]=arr[i];
        arr[i]=t;
        //������
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
    sortArr(arr,n);//�ö������������ϵĵ��������
    for(int i=0;i<m;i++)
    {
        //������������������������������
            //�������������������򽻻���������
        int a,b;
        scanf("%d %d",&a,&b);
        //���ö��ֲ����ҳ���������a,b��Ӧ��λ��
        //ͨ��a,bλ��ֱ�������ĸ���
        printf("%d\n",searchIndexB(b,arr,n)-searchIndexA(a,arr,n)+1);
    }
    return 0;
}
