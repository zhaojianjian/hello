#include "student_info.h"
#include <stdio.h>
#include<time.h>
#include<stdlib.h>
int main()
{
    int i,j,m=0,n=0,a[40];
	 srand((int)time(NULL));   
     for(i=0;i<=39;i++)   
      a[i]=i; 
	 while(m<=39)
     {
      j=rand()%40;
      for(i=0;i<40;i++)
	if(j==a[i])
       {  m++; 
		   a[i]=40;
		   if(m%4==1)
		   printf("第%d组:\n",++n);
		 printf("%d-%s\n",info[j].id,info[j].name);
        // if(m%4==0)  printf("\n");
       }
      }
	return 0;
}
