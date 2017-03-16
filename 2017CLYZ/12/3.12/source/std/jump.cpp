#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
int t,x,y;
int main()
{
	freopen("jump.in","r",stdin);
	freopen("jump.out","w",stdout);
	scanf("%d",&t);
	while(t--)
	  {
       scanf("%d%d",&x,&y);
       x=abs(x);
       y=abs(y);
       if(x<y)
         swap(x,y);
       if(x==1 && y==0)
         printf("3\n");
       else if(x==2 && y==2)
         printf("4\n");
       else if(x<=2*y)
         printf("%d\n",(x+y)/3+(x+y)%3);
       else
         printf("%d\n",(x-2*y)/4*2+(x-2*y)%4+y);
      }
	return 0;
}

