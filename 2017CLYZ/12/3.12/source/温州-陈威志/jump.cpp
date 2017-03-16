#include<cstdio>
#include<cmath>
using namespace std;
int ans;

void swp(int &x,int &y)
{
  int t=x;
  x=y,y=t;
}

int main()
{
  int x,y,T;
  freopen("jump.in","r",stdin);
  freopen("jump.out","w",stdout); 
  scanf("%d",&T);
  while(T--)
    {
	  scanf("%d%d",&x,&y);
	  x=abs(x),y=abs(y),ans=0;
	  if(x>y) swp(x,y);
	  if(x*2<=y)
	    {
		   if(x==0 && y==1) ans+=2;
		   ans+=x,y-=2*x;
		   ans+=(y/4)*2+y%4;
		   printf("%d\n",ans);
		}
	  else
	    {
		  ans+=(x+y)/3;
		  if((x+y)%3==1) ans++;
		  else if((x+y)%3==2) ans+=2;
		  if(y%2==0 && y/2+1==x) ans+=2;
		  printf("%d\n",ans);
		}
	}
} 
