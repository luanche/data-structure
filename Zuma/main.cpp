#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

class ListNode{//�������Ķ���
public:
    char data;
    //˫����������pre��next����ָ�룬�ֱ�ָ��ǰһ��Ԫ�غͺ�һ��Ԫ��
    ListNode *pre;
    ListNode *next;
    ListNode(char c){data=c;pre=NULL;next=NULL;}

};
class SeqList{
public:
    //��ͷָ��first��βָ��last��βָ����Ϊ�˱�������Ԫ��
    ListNode *first;
    ListNode *last;
    SeqList();
    void insertOne(int k,char &c);//����һ��Ԫ��
    void addOne(char &c);//����һ��Ԫ��ʹ�ú�巢
    void printAll();//��ӡ�����ĺ���
    void deleteOne(ListNode *d);//ɾ��һ��Ԫ��
    void update(ListNode *p);//����ڵ�����zuma�����������������ľ�ɾ�������Ҳ���������Ӧ
    bool isThree(ListNode *p);//�жϽ��p�����Ƿ�����������������������Ԫ��
};
bool SeqList::isThree(ListNode *p)
{
    //�жϽ��p�����Ƿ�����������������������Ԫ��
    //�з���true��û�з���false
    char t=p->data;
    if(p->pre->data==t)
    {
        if(p->pre->pre->data==t||p->next->data==t) return true;
    }else if(p->next->data==t)
    {
        if(p->next->next->data==t||p->pre->data==t) return true;
    }
    return false;
}
void SeqList::update(ListNode *q)
{
    //����ڵ�����zuma�����������������ľ�ɾ�������Ҳ���������Ӧ
    while(isThree(q))//�ж��Ƿ���������
    {

        while(q->pre->data==q->data) deleteOne(q->pre);//�Ӹýڵ���ǰ�ж��Ƿ�͸ýڵ�data��ͬ����ͬ��ɾ��
        while(q->next->data==q->data) deleteOne(q->next);//�Ӹýڵ������ж��Ƿ�͸ýڵ�data��ͬ����ͬ��ɾ��
        if(q->next!=last) {q=q->next;deleteOne(q->pre);}//���p�������һ����㣬��p�����ƣ�����ɾ��֮ǰ��p
        else if(q->pre!=first) {q=q->pre;deleteOne(q->next);}//����p��ǰ��
        else {deleteOne(q);break;}//�ٷ������ֻʣ��p��㣬��ֻ��ɾ��p����
    }
}
void SeqList::deleteOne(ListNode *d)
{
    //ɾ�����p
    d->pre->next=d->next;
    d->next->pre=d->pre;
    delete d;
}
void SeqList::printAll()
{
    //��ӡ���н��
    ListNode *p=first->next;
    if(first->next==last)//û�нڵ����"-";
    {
        printf("-");
    }
    while(p!=NULL)
    {
        printf("%c",p->data);
        p=p->next;
    }
}
SeqList::SeqList()
{
    //��ʼ��ʱ�����ͷ�ڵ�Ϳ�β���
    first=new ListNode('#');
    last=new ListNode('\n');//Ϊ�ڵ��ֵ���'\n'�����������ʱ���ֱ�����β��㣬����ֱ�ӻ���
    first->next=last;
    last->pre=first;
}
void SeqList::addOne(char &c)
{
    //β�巨���ӽڵ�
    ListNode *q=last->pre;
    ListNode *p=new ListNode(c);
    q->next=p;
    p->pre=q;
    p->next=last;
    last->pre=p;
}
void SeqList::insertOne(int n,char &c)
{
    //��λ��n������һ���ڵ�
    ListNode *p=first->next;
    for(int i=0;i<n;i++)
    {
        p=p->next;
    }
    ListNode *q=p->pre;
    ListNode *newNode=new ListNode(c);
    q->next=newNode;
    newNode->pre=q;
    p->pre=newNode;
    newNode->next=p;
    update(newNode);//����ڵ��ֱ�ӵ��ø��º���������zuma��
}
int main()
{
    SeqList li;
    while(1)
    {
        char c;
        scanf("%c",&c);
        if(c=='\n') break;
        else li.addOne(c);
    }
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int k;
        char c;
        scanf("%d %c",&k,&c);
        li.insertOne(k,c);
        li.printAll();
    }
    return 0;
}