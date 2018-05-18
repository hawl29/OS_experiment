#include <stdio.h>
typedef struct reco             //定义结构体，用来存储页面号，和缺页标记
{
  int no;
  int misspage;
}reco;
int main()
{
  int n,count,no;
  printf("请输入进程分区大小: \n");
  scanf("%d",&n);
  int que[n];                   //定义循环队列
  int size=0                    //用size记录队列中存放元素个数，用来判断循环队列，队满队空。
  int front=0,rear=0; 
  for(int i=0;i<n;i++) que[i]=0;
  printf("请输入页号序列长度：\n");
  scanf("%d",&count);
  reco page[count];                   //reco型的数组，记录每次输入页号时，当前物理块否缺页
  int block[n][count];                //用二维数组记录各物理块中存放过的页号
  for(int i=0;i<n;i++)               //初始化,i表示物理块编号，j表示页面输入时的顺序
  {   
     for(int j=0;j<count;j++)
     {
       block[i][j]=-1;
     }
  }       
  printf("请依次输入页号序列:\n");
  for(int i=0;i<count;i++)
  {
     scanf("%d",&no);
     page[i].no=no;
     for(int j=0;j<n;j++)                  //在物理块队列中查找当前输入页号，若没找到则标记缺页，反之，未缺页
     {                                     
       if(que[j]==no)  
       {
         page[i].misspage=0;
         break;
       }
       else page[i].misspage=1;
     }
     if(page[i].misspage==1)               //缺页，进行页面置换。若物理块队列不满，则将该页号插入队尾
     {                                     //未缺页，则只需记录未缺页标记即可
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
