#include <iostream>
#include <cstdio>
#include <cstring>

#define MAXSIZE 600001

using namespace std;

//BKDRhash

char str[MAXSIZE][45];//�ַ������飬���ڴ�������Ĳ���


//hash��Ĵ洢�ṹ���ڽӱ�Ĵ洢�ṹ������ͬ
class LinkNode//hash�����ڽ����ͻ�������
{
public:
    char *data;
    LinkNode *link;
    bool isDup;//�Ƿ��������ı�־����Ϊ���ǵ�����ֻ���һ�Σ����������bool���͵�isDup���
    LinkNode(char *c)
    {
        isDup=false;
        data=c;
    }
};

class TabNode//hash��Ľ��
{
public:
    LinkNode *first;
    TabNode()
    {
        first=NULL;
    }
};

class HashTable//hash�ṹ����
{
public:
    TabNode *tab;
    HashTable()
    {
        tab=new TabNode[MAXSIZE];
    }
};

//BKDRHash���ǹ����ַ���hash�ĺܺõ�һ��hash�������൱�ڰ��ַ���������һ��һ�����Ƶ����������Ӧ��hashֵ
//��������ƣ����˾������ʵ�ֱ�����ȡ31��131��1331...������������ͻ�Ŀ����Ի��С
//���ǳ�ͻ�ǲ��ܱ���ģ�ֻ�ܽ��ͣ����Խ��hash��ͻҲ�Ǳ����
unsigned long BKDRHash(char *s)
{
    unsigned long adeci=131;//����
    unsigned long hashValue=0;//hashValueΪ�ַ�����hashֵ����ʼ��Ϊ0
    //���޷��ų�����unsigned long �洢hashֵ������hashֵ�ǲ��ÿ���ֵ��������⣬���ֵ̫��ʹ����Ȼ���������
    for(int i=0;s[i]!='\0';i++)
    {
        //����hashֵ
        hashValue=hashValue*adeci+(s[i]-'a');//�����ؾ����㷨�����ʽչ�����Լ���������
    }
    return hashValue%MAXSIZE;//��������鳤��ȡ��(����������)
}
void hashColli(TabNode &tn,char *s)//���hash��ͻ
{
    //�����������hash��ͻ�ȽϷ��㣬Ҳ�ȽϺ�ʵ��
    LinkNode *p=new LinkNode(s);
    p->link=tn.first;
    tn.first=p;
}

int main()
{
    int n;
    HashTable ht;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%s",str[i]);
        int index=BKDRHash(str[i]);//����hashֵ
        LinkNode *p=ht.tab[index].first;
        while(p!=NULL)//�������±�λ�ö�Ӧ�������ַ���
        {
            if(strcmp(p->data,str[i])==0)//����ַ�����ͬ����ʾ������
            {
                if(!p->isDup)//���û����������������������isDup���Ϊtrue����һ���������Ͳ������
                {
                    p->isDup=true;
                    printf("%s\n",p->data);
                    break;
                }else break;
            }
            p=p->link;
        }
        if(p==NULL)//�������������Ȼû����������֮�佫�ַ��������λ�õ�������
        {
            hashColli(ht.tab[index],str[i]);
        }
    }
    
    return 0;
}
