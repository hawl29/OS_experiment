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
int add(node *head,int no,int size) 
{
    node *p=head->next;
    for(;p;p=p->next)     if( -1==p->no && p->size>=size ) break;  // 找到第一个未分配且大于size的内存空间节点
    if(p==NULL) return 0;
    if(p->size-size>SIZE) 
    {
        node *temp = (node*)malloc(sizeof(node));
        temp->no = -1; temp->start = p->start+size;
        temp->size = p->size-size; temp->next = p->next;
        p->next = temp;
    }  
    p->no=no;p->size=(p->size-size>SIZE?size:p->size);
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
  int no=0;
  srand((unsigned int)time(NULL));
  node *head=init_link_table(memory_capacity);
  int rep[test_count];
  int k,j,m,n;
  for(int i=0;i<test_count;i++) rep[i]=0;
  for(int i=0;i<test_count;i++)
  {
    if(rand()%2==1)
    {
      k=add(head,++no,rand()%memory_capacity/5);
      if(k==1) taskcount++;
    }
    else if(rand()%2==0&&no>0)
    {
      j=rand()%no;
      m=n=j;
      for(int i=0;m>=0&&n<no;)
      {
        if(rep[m]==1) 
        {
          j=m;
          break;
        }  
        else if(rep[n]==1) 
        {
          j=n;
          break;
        }  
        else
        {
          if(m>0) m--;
          if(n<no) n++;
        }
      }
      del(head,j);    
    }   
  }
  printf("存入任务个数%d\n",taskcount);
  return 1;
}



































