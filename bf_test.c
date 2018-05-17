#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define INF 1000000
int SIZE;
typedef struct node
{
  int no;
  int start;
  int size;
  struct node *next;
}node;
node* init_link_table()
{
  node *head=(node*)malloc(sizeof(node));
  head->next=(node*)malloc(sizeof(node));
  head->next->no=-1;
  head->next->start=0;
  printf("请输入内存空间大小: ");
  scanf("%d",&head->next->size);
  head->next->next=NULL;
  printf("请输入碎片大小: ");
  scanf("%d", &SIZE);
  return head;
}
void show(node *head) /*打印内存分配情况*/
{
    node *p=head->next,*q=head->next;
    int i=1, j=1;
    printf( "        已分配分区                  空闲分区\n" );
    printf( "(分区号, 作业, 始址, 大小)    (分区号, 始址, 大小)\n" );
    while(p||q) 
    {
        while(p&&p->no==-1)
        {
          p=p->next;
          i++; 
        }
        while(q&&q->no!=-1) 
       { 
          q=q->next; 
          j++;
       }
       if(p)
       { 
         printf(" %6d, %4d, %4d, %4d ",i,p->no,p->start,p->size); 
         p=p->next; 
         i++; 
       }
       else printf("                          ");
       if(q)
       { 
         printf("     %6d, %4d, %4d ",j,q->start,q->size);
         q=q->next;
         j++;
       }
       printf("\n");
    }
}
int add(node *head,int no,int size)  /*内存分配模块*/
{
    int min=INF;
    node *p,*q;
    for(p=head->next;p;p=p->next)
    {  
      if(p->no==-1&&p->size>=size)
      {
         if(p->size-size<min)
         {
          min=p->size-size;
          q=p;
         }
      } 
    } 
    if(q==NULL) return 0;
    if(q->size-size>SIZE) 
    {
       node *temp=(node*)malloc(sizeof(node));
       temp->no=-1; 
       temp->start=q->start+size;
       temp->size=q->size-size;
       temp->next=q->next;
       q->next=temp;
    }  
    q->no=no;
    q->size=(q->size-size>SIZE?size:q->size);
    return 1;
}
int del(node *head,int no)  /*内存回收模块*/
{
     node *p,*m,*n;
     p=head->next;
     while(p&&p->no!=no) p=p->next;
     if(p==NULL) return 0;
     p->no=-1; 
     m=head->next;n=m->next;
     while(n) 
     { 
        if(m->no==-1&&n->no==-1&&m->start+m->size==n->start) /*判断m,n指向相邻块*/
        { 
            m->size+=n->size; 
            m->next=n->next;
            free(n);
            n=m->next; 
            continue;
        }
        m=n; 
        n=n->next;
     }
     return 1;
}
int main()
{
  node *head=init_link_table();
  while(1)
  { 
    int op,no,size,state;
    printf("\n***************************************************\n");
    printf("   1: 为新作业分配内存        2: 撤销作业释放内存\n");
    printf("   3: 查看buddy算法内存分配   4: 退出");
    printf("\n***************************************************\n");
    printf("请输入操作: ");
    scanf("%d",&op);
    switch(op) 
        {
            case 1:
                printf("请输入作业id和作业大小size: ");
                scanf("%d%d",&no,&size);
                if(add(head,no,size)) printf("分配成功\n");
		else printf("分配失败\n");
                break;
            case 2:
                printf("请输入需要撤销的作业id: ");
                scanf("%d",&no);
                if(del(head,no)) printf("撤销成功\n");
		else printf("撤销失败\n");
                break;
            case 3:
                show(head);
                break;
            case 4: return 0;
        }
    }
    return 0;
}


































