#### �㷨��˼·
- ��������������ʱ��Ҫ���ر��ϸ�������ͨ���㷨�϶��ǲ����ˡ�������Ŀ������ʾ����kd-tree����range-tree������ȥ�����˽���һ��kd-tree��˵����kd-tree�ǲ��ϵ�ͨ����x����Ͷ�y���򹹽�һ��ƽ�����������һ��Ľ���x�����ҳ��м�����Ϊ���ڵ㡣���ŵݹ鹹���ڶ���Ľ�㣬��y�����������м�����Ϊ��һ��ĸ��ڵ㡣���ϵݹ�ֱ�������н�㶼���ӵ��������ĳ�����ʹӸ��ڵ㿪ʼ�����жϸ��ڵ��Ƿ����㣬������ҵĵ�ȸ��ڵ�С����ݹ�����������֮�ݹ���������ֱ����Ҫ�ҵĽ���ҳ������Ͷ�����������˼��һ����ֻ����Ϊ�Ƕ�ά�����ݣ�������x��y������бȽϡ���������Ƿ�Χ���ң�����Ҫ�����жϽ���Ƿ��ڷ�Χ�ڡ�������������x1��x2ֱ�ӣ�����������Ҫ�����ݹ顣����������ķ�Χ�ǰ������������䣬��ô���ж����еĽڵ㣬ʱ����ر�����
- ���������õ���85�֣��������Ż��˺ܶ�ĵط��������ж�ʱ����������Ƕ���Լ����жϴ�����Ҳֻ�ܽ���19��������ʱ���ᵽ6100ms�����������������ɳ�ʱ���ҹ����������������кܶ��ȫ���ǵ����䣬���Բ�ѯ�ͺ�������˵�������õ��㷨����r-tree������r-tree��˼���ҿ���̫���ף����Ϲ�ϵr-tree��˵��Ҳ���١�
---
#### ���������⼰����취
- һ��ʼ��19��������ʱ��ӽ�10000ms���������ر��޵�����ˡ������������Ż�����㷨���Ӵ洢���ʱ�ýڵ�õ�ַ���棬�����ȴ��±�����һ�㡣�Լ��жϽڵ�ʱ���ж�����ͨ��Ƕ�ף������е������ظ��ж�������Ч�ʡ���󽫵�19��������ʱ����������6100ms������������������Ȼ�ǳ�ʱ�����ֻ����85�֡��ҹ�������㷨�ü��޾�ֻ�ܵ�85�֣����Ҫ��õķָ��ߣ�ֻ�ܻ�����㷨���Ͼ������Ҫ��ѯ�ķ�Χ���������н�㣬����㷨�͵ð�ÿ����㶼�����жϣ�Ч�ʱض�������������
---
#### ʱ�临�ӶȺͿռ临�Ӷ�
- ����㷨��ʱ�临�Ӷȣ�����n����㣬m����ѯ����õ������ʱ�临�Ӷ�ʱ$O(mlogn)$���������£�ʱ�临�Ӷ�����$O(mn)$���ռ临�ӶȾ���n�����洢��ƽ��������ÿռ䡣
---
#### �������
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

typedef struct //վ���㣬����λ��������¶�
{
public:
    int x,y;
    int temper;
}Point;

Point p[500005];

int k;
int x1,y1,x2,y2;//����ȫ�ֱ��������ڵ��ýӿںͺ����㷨ʹ��
long tatolTemper;

void adjust(Point *arr,int i,int length,bool X)//bool X��ʾ����x��������y������x����bool����XΪtrue
{//�������������
    int k;
    Point temp;
    if(X)//��x����
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
    }else//��y����
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

void sortArr(Point *arr,int len,bool X)//������
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

class TreeNode //kd-tree���
{
public:
    Point *index;//ָ��վ�����p���λ������Ӧ��ָ��
    bool isX;//��ʾ��xΪ�ο�������yΪ�ο�
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
void makeTree(TreeNode *&rot,int left,int right,bool X)//����kd-tree
{
    sortArr(p+left,right-left+1,X);
    int m=(left+right)>>1;
    rot=new TreeNode(&p[m],X);
    if(left<=m-1) makeTree(rot->lc,left,m-1,!X);
    if(m+1<=right) makeTree(rot->rc,m+1,right,!X);


}
void rangeSearch(TreeNode *&rot)//kd-tree�ķ�Χ����
{
    //���ж�����Ƕ����������Ϊ�˽�ʡʱ�䣬��Ϊ����֮ǰ�Լ��жϹ�����x,y��ȫ�ֱ�����x,y������Ҳ���жϣ�����Ϊ�˽�ʡ�жϵ�ʱ��
    //�ݹ��ѯ
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
    makeTree(t.root,0,n-1,true);//�ݹ鹹��kd-tree
    while(GetQuery(&x1,&y1,&x2,&y2))
    {
        k=0;
        tatolTemper=0;
        rangeSearch(t.root);
        if(k!=0) Response((tatolTemper/k));//����ƽ���¶�
        else Response(0);//���kΪ�㣬�򷵻��㣬����ֱ�ӳ���
    }
    return 0;
}


```