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
void show(node *head) //打印内存分配情况
{
    node *p=head->next,*q=head->next;
    int i=1, j=1;
    printf( "        已分配分区                  空闲分区\n" );
    printf( "(分区号, 作业, 始址, 大小)    (分区号, 始址, 大小)\n" );
    while(p||q) 
    {
        while(p&&p->no==-1)                //查找已分配分区的分区号
        {
          p=p->next;
          i++; 
        }
        while(q&&q->no!=-1)                //查找空闲分区的分区号
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
int add(node *head,int no,int size)  //内存分配模块
{
    int min=INF;                     //bf算法首先找到所有大于待分配作业大小的空闲区，再从中找出容量最小的空闲区，完成分配
    node *p,*q;
    for(p=head->next;p;p=p->next)
    {  
      if(p->no==-1&&p->size>=size)  //先找满足容量大于作业大小的空闲区
      {
         if(p->size<min)       //再找容量与作业大小最接近的空闲区
         {
          min=p->size;
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
  node *head=init_link_table();
  while(1)
  { 
    int op,no,size,state;
    printf("\n***************************************************\n");
    printf("   1: 为新作业分配内存        2: 撤销作业释放内存\n");
    printf("   3: 查看bf算法内存分配      4: 退出");
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


































