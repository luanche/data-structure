#### �㷨��˼·
- �����ж����������֮���жϣ�ʱ�临�Ӷ���$O(n^2)$��Ч���ر�ͣ��϶�������������ʱ���Ҫ�����ǿ����ñ���㷨��ȥ���ϲ��˲��ַ����Ĵ洢����ʹ���ַ���hash��ֻҪ�ҵ����ʵ�hash�������Ϳ��ԺܺõĴ洢�ַ�����������hash�洢�ķ�ʽ�����ڲ���ĳ���ַ�����Ч���ر�ã�����֮��ͨ��hash�������嵽���ַ����Ĵ洢λ�á�����ʹ�õ�hash�����ķ�ʽΪ��õĳ�����������Ҳ���д�����hash��ͻ�ķ���Ҳ��������������hash��
- �������hash���������Ҫ�úÿ��ǡ���ȥ���ϲ��˲鳣�õ��ַ���hash��hash������������������ַ����ʣ�BKDRhash�����ǳ�ͻ��͵ġ������Ҿ�����BKDRhash��������ȷ��hashֵ��BKDRhash�����ǽ��ַ���������ĳ�����Ƶ�����Ȼ��֮�����hashֵ�����о�����������ʵĽ���Ϊ31��131��1331��13131��������������������������������̫�󣬻����ַ���̫���������hashֵ���ر������û�취ȷ��һ�������hashֵ�����ǿ������޷��ų�����(unsigned long int),�Ǽ�������Ȼ��������Ͳ����ٿ���ȡ������֤hashֵ̫������⡣
- ��hashֵ�ļ�����Ϊ�൱����k����ת10���ƵĹ��̡������ַ���"abc"�������ļ��������$hash=a{\times}k^2+b{\times}k+c$�����ڼ�����У����������ʽ����$hash=a{\times}k{\times}k+b{\times}k+c$�����ַ����ܳ�ʱ����Ҫ����ܶ�γ˷��������뵽�˼��㷽���������ؾ����㷨���ͳ˷�չ��Ϊ$hash=(a{\times}k+b){\times}k+c$�����Լ��ټ��������
---
#### ���������⼰����취
- һ��ʼ��֪���ַ���hash�ķ�������û��ͷ����ֱ�ӽ��в��ң�Ƕ������ѭ������ʱ���ر𳤣����������ˡ����Ա���û�һ��������ȥ���Ͽ��˹����ַ����Ĵ洢���⣬�������ַ���hash��
---
#### ʱ�临�ӶȺͿռ临�Ӷ�
- ��Ϊ��hash�洢�������ַ����Ĵ�ȡ���ظ���ѯ�ǱȽϿ�ģ�����ֱ��ͨ���±���ȷ��������ʱ�临�Ӷȴ�ԼΪ$O(n)$�����ڿռ临�ӵģ��ڳ�ͻ�ٵ�����£���Լ�����ַ�������Ĵ洢�ռ䡣��ͻ���ˣ�����΢��һ�㡣
---
#### �������
```c++
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

```