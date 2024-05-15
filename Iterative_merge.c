#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void merge(int arr[],int l,int m,int r)
{
  int i,j,k;
  int n1=m-l+1;
  int n2=r-m;
  int* L=(int*)malloc(n1*sizeof(int));
  int*R=(int*)malloc(n2*sizeof(int));
  for(i=0;i<n1;i++)
  L[i]=arr[l+i];
  for(j=0;j<n2;j++)
  R[j]=arr[m+1+j];
  i=0;
  j=0;
  k=l;
  while(i<n1&&j<n2)
  {
   if(L[i]<=R[j])
   { arr[k]=L[i];
   i++;
   }
   else
   {
     arr[k]=R[j];
     j++;
   }
     k++;
  }
  while(i<n1)
  {
    arr[k]=L[i];
    i++;
    k++;
  }
  while(j<n2)
  {
   arr[k]=R[j];
   j++;
   k++;
   }
   free(L);
   free(R);
}
void mergesort(int arr[],int low,int high)
{
  int currentsize;
  int leftstart;

  for(currentsize=1;currentsize<=high-low;currentsize=2*currentsize)
  {
   for(leftstart=low;leftstart<high;leftstart+=2*currentsize)
   {
    int mid=leftstart+currentsize-1;
    int 
rightend=(2*currentsize+leftstart-1<high)?(2*currentsize+leftstart-1):high;
    merge(arr,leftstart,mid,rightend);
    }
   }
  }
  int mergemain(int x)
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
      mergesort(arr,0,n-1);
      printf("Sorted Array:");
      for(i=0;i<n;i++)
      printf("%d ",arr[i]);
      printf("\n");
      return 0;
      }
      int main()
      {
      int N[]={10,100,1000,10000};
      int num=sizeof(N)/sizeof(int);
      clock_t start,end;
      double time_taken;
      for(int i=0;i<num;i++)
      {
      start=clock();
      mergemain(N[i]);
      end=clock();
      time_taken=((double)(end-start))/CLOCKS_PER_SEC;
      printf("time taken for iterative sort with N=%d is 
%f\n",N[i],time_taken);
      }
      return 0;
      }
