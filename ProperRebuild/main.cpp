#include <iostream>
#include<cstdio>

using namespace std;

//不构建树，在递归时直接输出中序遍历，省去了构建树的时间，以及储存树的空间

void build(int *pre,int *post,int prl,int prr,int pol,int por)
{
    //pre是前序序列的数组，post是后序序列的数组
    //prl是当前结点结点为根的树的前序序列在pre的左下标，prr是右下标
    //pol是当前结点结点为根的树的前序序列在post的左下标，por是右下标
    //递归输出中序遍历
    int i;
    int j;
    if(prl==prr){//prl==prr表示已经是叶子节点，直接输出即可
        printf("%d ",pre[prl]);
        return;
    }else
    {
        i=prr;
        for(;pre[i]!=post[por-1];i--){}//在前序序列中从右向左查找右子树根节点的下标
        j=por-(prr-i+1);//通过右子树根节点的下标直接算出左子树根节点的下标
        build(pre,post,prl+1,i-1,pol,j-1);//递归调用继续遍历左子树
        printf("%d ",pre[prl]);//输出根节点
        build(pre,post,i,prr,j,por-1);//递归调用继续遍历右子树
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
    //输入前序遍历
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pre[i]);
    }
    //输入后续遍历
    for(int i=0;i<n;i++)
    {
        scanf("%d",&post[i]);
    }
    build(pre,post,0,n-1,0,n-1);//递归遍历二叉树
    printf("\n");
    return 0;
}
