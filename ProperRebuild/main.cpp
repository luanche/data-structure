#include <iostream>
#include<cstdio>

using namespace std;

//�����������ڵݹ�ʱֱ��������������ʡȥ�˹�������ʱ�䣬�Լ��������Ŀռ�

void build(int *pre,int *post,int prl,int prr,int pol,int por)
{
    //pre��ǰ�����е����飬post�Ǻ������е�����
    //prl�ǵ�ǰ�����Ϊ��������ǰ��������pre�����±꣬prr�����±�
    //pol�ǵ�ǰ�����Ϊ��������ǰ��������post�����±꣬por�����±�
    //�ݹ�����������
    int i;
    int j;
    if(prl==prr){//prl==prr��ʾ�Ѿ���Ҷ�ӽڵ㣬ֱ���������
        printf("%d ",pre[prl]);
        return;
    }else
    {
        i=prr;
        for(;pre[i]!=post[por-1];i--){}//��ǰ�������д�������������������ڵ���±�
        j=por-(prr-i+1);//ͨ�����������ڵ���±�ֱ��������������ڵ���±�
        build(pre,post,prl+1,i-1,pol,j-1);//�ݹ���ü�������������
        printf("%d ",pre[prl]);//������ڵ�
        build(pre,post,i,prr,j,por-1);//�ݹ���ü�������������
    }
}
int main()
{
    setvbuf(stdin,new char[1<<20],_IOFBF,1<<20);
    setvbuf(stdout,new char[1<<20],_IOFBF,1<<20);
    int n;
    scanf("%d",&n);
    int *pre=new int[n];
    int *post=new int[n];
    //����ǰ�����
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pre[i]);
    }
    //�����������
    for(int i=0;i<n;i++)
    {
        scanf("%d",&post[i]);
    }
    build(pre,post,0,n-1,0,n-1);//�ݹ����������
    printf("\n");
    return 0;
}
