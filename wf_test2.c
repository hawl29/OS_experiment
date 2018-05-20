#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define INF 1000000
int SIZE;
int memory_capacity;
typedef struct node
{
  int no;
  int start;
  int size;
  struct node *next;
}node;
node* init_link_table(int memory_capacity)
{
  node *head=(node*)malloc(sizeof(node));
  head->next=(node*)malloc(sizeof(node));
  head->next->no=-1;
  head->next->start=0;
  head->next->size=memory_capacity;
  head->next->next=NULL;
  return head;
}
int add(node *head,int no,int size)  //内存分配模块
{
    int max=0;                   //wf算法首先找到所有大于待分配作业大小的空闲区，再从中找出容量最大的空闲区，完成分配
    node *p,*q=NULL;
    for(p=head->next;p;p=p->next)
    {  
      if(p->no==-1&&p->size>=size)  //先找满足容量大于作业大小的空闲区
      {
         if(p->size>max)       //再找容量与作业大小最接近的空闲区
         {
          max=p->size;
          q=p;
         }
      } 
    } 
    if(q==NULL) return 0;         //如果没找到满足要求的空闲区，则分配失败
    if(q->size-size>SIZE)          //SIZE是我们设置的碎片大小，若分配后空闲区剩余空间容量大于碎片大小，则需为剩余空间新建一个链表结点来记录它
    {
       node *temp=(node*)malloc(sizeof(node)); 
       temp->no=-1;                          
       temp->start=q->start+size;              //为剩余空间创建新结点，它的始址为该空闲块原始址+作业大小
       temp->size=q->size-size;                //该结点大小即为原空闲块大小-作业大小
       temp->next=q->next;                     //将新建结点插入原空闲结点之后
       q->next=temp;
    }  
    q->no=no;                     //将作业存入该空闲区中
    q->size=(q->size-size>SIZE?size:q->size);  //若为剩余空间创建了新结点，则存入作业后，该结点大小即为作业大小
    return 1;
}
int del(node *head,int no)  //内存回收模块
{
     node *p,*m,*n;
     p=head->next;
     while(p&&p->no!=no) p=p->next;
     if(p==NULL) return 0;
     p->no=-1; 
     m=head->next;n=m->next;
     while(n) 
     { 
        if(m->no==-1&&n->no==-1&&m->start+m->size==n->start)    //判断m,n指向相邻块
        { 
            m->size+=n->size; 
            m->next=n->next;
            free(n);
            n=m->next; 
        }
        else 
        {
          m=n; 
          n=n->next;
        }  
     }
     return 1;
}
int main()
{
  printf("请输入内存空间大小: ");
  scanf("%d",&memory_capacity);
  printf("请输入碎片大小: ");
  scanf("%d", &SIZE);
  int test_count;
  printf("请输入测试次数:");
  scanf("%d",&test_count);
  int taskcount=0;
  srand((unsigned int)time(NULL));
  for(int i=0;i<test_count;i++)
  {
    node *head=init_link_table(memory_capacity);
    int flag=0;
    int no=0;
    int k;
    while(flag<3)
    {
      k=add(head,++no,rand()%memory_capacity/5);
      if(k==0) flag++;
      else taskcount++,flag=0;  
    }
    node *p,*q;
    p=head,q=p->next;
    while(q!=NULL)
    {
      free(p);
      p=q,q=q->next;
    }   
  }
  printf("%d\n",taskcount);
  printf("平均任务个数：%.2f\n",(float)taskcount/test_count);
  return 1;
}


































