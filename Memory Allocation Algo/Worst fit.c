#include<stdio.h>
int main(){
   
   int p,m;  
   printf("Enter number of processes:");
   scanf("%d",&p);
   printf("Enter number of Memory blocks:");
   scanf("%d",&m);
   
   int parr[p];
   struct mem{
          int id;
          int size;
   }marr[m];
   int i;
   for(i=0;i<p;i++)
   {
     printf("Enter size of process %d:",i+1);
     scanf("%d",&parr[i]);      
   }
   for(i=0;i<m;i++)
   {
     printf("Enter size of memory %d:",i+1);
     scanf("%d",&marr[i].size);   
     marr[i].id=i+1;   
   }
   int j;
   for(i=0;i<m;i++)
   for(j=i+1;j<m;j++)
   if(marr[i].size<marr[j].size)
   {
    struct mem t=marr[i];
    marr[i]=marr[j];
    marr[j]=t;                               
   }
   for(i=0;i<p;i++){
       for(j=0;j<m;j++){
         if(marr[j].size>=parr[i]){
              marr[j].size-=parr[i];
              printf("Allocating process %d to memory %d\n Size remaining in it after allocation %d\n\n",i+1,j+1,marr[j].size);   
              break;              
         }  
         
        
     }    
      if(j==m)
         {printf("Not enough memory for process %d",i);break;}        
   }
  getch();  
}