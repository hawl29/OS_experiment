#include <stdio.h>
typedef struct reco
{
  int no;
  int misspage;
}reco;
int main()
{
  int n,count,no;
  printf("请输入进程分区大小: \n");
  scanf("%d",&n);
  int que[n];
  int front=0,rear=0; 
  for(int i=0;i<n;i++) que[i]=0;
  printf("请输入页号序列长度：\n");
  scanf("%d",&count);
  reco page[count];
  int block[n][count];               //用二维数组记录物理块中存放的页号
  for(int i=0;i<n;i++) 
  {   
     for(int j=0;j<count;j++)
     {
       block[i][j]=-1;
     }
  }       
  printf("请依次输入页号序列:\n");
  int size=0;
  for(int i=0;i<count;i++)
  {
     scanf("%d",&no);
     page[i].no=no;
     for(int j=0;j<n;j++)
     {
       if(que[j]==no)  
       {
         page[i].misspage=0;
         break;
       }
       else page[i].misspage=1;
     }
     if(page[i].misspage==1)               //缺页，若物理块队列不满，则将该页号插入队尾
     {
       if(size<n)
       {
         que[rear]=no;
         rear=(rear+1)%n;
         size++;
       }
       else                               //队列满，则将队头页号覆盖
       {
         que[rear]=no;
         rear=(rear+1)%n;
       }
       for(int k=0;k<n;k++)   block[k][i]=que[k];     //记录下缺页时页面置换后，各物理块中存储的页号
     }     
  }
  printf("访问页面");
  for(int i=0;i<count;i++) printf("%2d",page[i].no);
  printf("\n");
  for(int j=0;j<n;j++)
  {
    printf("物理块%d ",j);
    for(int k=0;k<count;k++) 
    { 
      if(block[j][k]==-1)  printf("  ");
      else printf("%2d",block[j][k]);
    }
    printf("\n");
  }
  printf("缺页否  ");
  float temp=0;
  for(int i=0;i<count;i++) 
  {
    if(page[i].misspage==1) printf(" *"),temp++;
    else printf("  ");
  }
  printf("\n缺页率:%.2f%\n",temp/count*100);
  return 1;
}
