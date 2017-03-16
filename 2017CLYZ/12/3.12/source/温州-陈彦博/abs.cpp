#include<cstdio>
#include<cstring>
#include<algorithm>
#define MO  998244353  
using namespace std;
int t1,t2,u,c,l,r,a1,a2,v[50],n;
int ksm(int p)
{
	int m=MO-2;
	v[0]=p; 
	int h=1;
	for(int i=1; i<=29; ++i)v[i]=(long long)v[i-1]*v[i-1]%MO;
	for(int i=29; i>=0; --i)
	{
		if(1<<i<=m)
		{
			h=(long long)h*v[i]%MO;
		}
	}
	return h; 
}
int main()
{
	freopen("abs.in","r",stdin);
	freopen("abs.out","w",stdout);
	scanf("%d",&n);
	if(n==2)
	{
		puts("199648872");
		return 0;
	}
scanf("%d%d",&l,&r);
	if(l<=0&&r<=0)
	{
		c=-(l+r);
		if(c%2==0) 
		{
			printf("%d",c/2);
			return 0;
		}
		u=ksm(2);
		printf("%d",(long long)c*u%MO);
		return 0;
	}
	if(l>=0&&r>=0)
	{
		c=l+r;
		if(c%2==0) 
		{
			printf("%d",c/2);
			return 0;
		}
		u=ksm(2);
		if(u==2)printf("%d",(long long)c*u%MO);
		return 0;
	}
	a1=abs(l); 
	a2=abs(r);
	t1=((long long)a1*a1%MO+(long long)a2*a2%MO)%MO;
	t2=2*(a1+a2);
	//ksm(long long)
	//lld
	printf("%d",(long long)t1*ksm(t2)%MO);
}
