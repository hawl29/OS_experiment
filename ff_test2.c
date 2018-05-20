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



































