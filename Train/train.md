#### �㷨��˼·
- �����˵�������ԣ�����վ����һ��ջ�������ջģ���������վ��ʮ�ֺ�������������վ�Ĳ������Ǿ����Գ�ʼ״̬Ϊ����һ���������ṹ�����������վ��˳�򣬾��Ƕ�����������ı������õݹ���ģ�����ֲ������ǶԶ���������ȱ����������ҵ��㷨������һ��ջ�͵ݹ������
---
#### ���������⼰����취
- ���ڵݹ�������棬�жϳ�ջ������ջ�������Ƚϸ��ӣ�����������Ƕ���������������ߵݹ��Ч�ʡ���������ϸ�о����⼸��������Ƕ�׹�ϵ�����������ķ�������д����Search()������ע�����ˡ�
---
#### ʱ�临�ӶȺͿռ临�Ӷ�
- ���㷨��ʱ�临�ӶȾ��ǵݹ������ʱ�临�ӵģ�����������ȱ�����ʱ�临�Ӷ�$O(n)$����Ϊ������Ҫ�������е������������������ʱ�Ϳ����˳������ʱ�临�Ӷ�С��$O(n)$���ռ临�Ӷ�������������˳�������a�Ŀռ䣬���г�ջ��ջ��������seq�Ŀռ临�Ӷȡ��������ʱ������������������õ�bool�������洢��������ʵ�õĿռ䲻̫��
---
#### �������
```c++
#include <iostream>
#include <cstdio>

using namespace std;


//seq�����ǲ������͵����飬���������ջ��ջ˳��true��ʾpush��false��ʱpop
//��Ϊ��Ҫ�ж���������˳���Ƿ����������ҽ�seq�ĵ�һ��Ԫ����Ϊ�������ı�ʶ
//����ÿһ�����ᣬ������ջ�ͳ�ջ�������������seq�ĳ���Ϊ����������ֵ������
bool *seq=new bool[3200005];
//seqNumΪ��¼˳��ĸ���
int seqNum=1;

class Stack{//˳��ջ�������䵱�г�����վ
public:
    int maxSize;
    int num;
    int *data;
    Stack(int ms);
    ~Stack();
    void push(int x);//��ջ
    int pop();//��ջ
    int topData();//���ջ��Ԫ�أ��ò���ջ��ֻ���ڱȽ�
    bool isEmpty();//ջ��
    bool isFull();//ջ��

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
    //�ݹ�ģ���ջ��ջ����
    //ջ���൱�ڵ���վ��Ԫ���൱�ڳ��ᣬ�����ջģ�⳵���������վ�Ĳ��������������ջ��ջ��˳�򣬻����Ƿ�������˳��
    if(out==n)//out��ʾ��ջ������out==nʱ�˳��ݹ�
    {
        seq[0]=true;//����������˳��
        return;
    }
    if(in>n)//in��ʾ��ջ������in>n��ʾԪ���Ѿ�ȫ����ջ����ֻ�ܽ��г�ջ����
    {
        if(s.topData()!=a[out]) return;//ջ��Ԫ�ز����㵱ǰ˳���˳�
        s.pop();//�������ջ
        seq[seqNum++]=false;//��¼��ջ������false��ʾ��ջ
        Search(s,a,out+1,in,n);//�����ݹ�
    }else
    {
        if(s.isFull())//ջ����ֻ�ܳ�ջ
        {
            if(s.topData()!=a[out]) return;
            else
            {
                s.pop();
                seq[seqNum++]=false;
                Search(s,a,out+1,in,n);
            }
        }
        else if(s.isEmpty())//ջ�գ�ֻ����ջ
        {
            s.push(in);
            seq[seqNum++]=true;
            Search(s,a,out,in+1,n);

        }
        else//ջ�Ȳ��գ�Ҳ����������ܳ�ջ��������ջ
        {
            if(s.topData()==a[out])//ջ��Ԫ�������˳�򣬳�ջ
            {
                s.pop();
                seq[seqNum++]=false;
                Search(s,a,out+1,in,n);
            }else//ջ��Ԫ�ز���������ջ
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
    seq[0]=false;//��ջ��ջ��¼����ĵ�һ��Ԫ��Ϊ��¼�Ƿ��������ʼ��Ϊfalse
    Search(s,a,0,1,n);//���еݹ��ջ��ջģ��
    if(seq[0])//��˳��������������ջ��ջ˳��
    {
        for(int i=1;i<=2*n;i++)
        {
            if(seq[i])printf("push\n");
            else printf("pop\n");
        }
    }else{printf("No\n");}//�����������No��

    return 0;
}

```