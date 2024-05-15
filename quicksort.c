#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int partition(int arr[],int low,int high)
{
int random=low+rand()%(high-low+1);
int pivot=arr[random];
int i=low-1;
int j=high+1;
while(1)
{
   do
   {
    i++;
   }while(arr[i]<pivot);
   do
   {
   j--;
   }
   while(arr[j]>pivot);
   if(i>=j)
   return j;
   int temp=arr[i];
   arr[i]=arr[j];
   arr[j]=temp;
   }
   }
   void quicksort(int arr[],int low,int high)
   {
   if(low<high)
   {
   int pi=partition(arr,low,high);
   quicksort(arr,low,pi);
   quicksort(arr,pi+1,high);
   }
}
   int quickmain(int x)
   {
    int i,n;
    int arr[x];
    FILE* fp;
    fp=fopen("random_numb.text","r");
    if(fp==NULL)
    {
     printf("ERROR OPENING FILE!\n");
     exit(1);
    }
    n=0;
    while(fscanf(fp,"%d",&arr[n])!=EOF)
    {
     n++;
      if(n>x)
      break;
      }
      fclose(fp);
      quicksort(arr,0,n-1);
      printf("Sorted Array:");
      for(i=0;i<n;i++)
      printf("%d ",arr[i]);
      printf("\n");
      return 0;
      }
      int main()
      {
      int N[]={10,100,1000,10000,100000,1000000};
      int num=sizeof(N)/sizeof(int);
      clock_t start,end;
      double time_taken;
      for(int i=0;i<num;i++)
      {
      start=clock();
      quickmain(N[i]);
      end=clock();
      time_taken=((double)(end-start))/CLOCKS_PER_SEC;
      printf("time taken for quicksort with N=%d is %f\n",N[i],time_taken);
      }
      return 0;
      }
