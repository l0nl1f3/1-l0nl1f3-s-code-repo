#include<iostream>
#include<stdio.h>
using namespace std;
long long n,i,l,r,temp1=0,temp2=0;
long long pow (long long a,long long b)
{
	if (b==0)
	return 1;
	long long c=pow(a,b/2);
	if (b&1)
	return a*c%998244353*c%998244353;
	return c*c%998244353;
}
int main ()
{
	freopen("abs.in","r",stdin);
	freopen("abs.out","w",stdout);
	scanf("%lld",&n);
	for (i=1;i<=n;i++)
	{
		scanf("%lld %lld",&l,&r);
		temp1+=l;
		temp2+=r;
	}
	if (temp1<0&&temp2>0)
	printf("%lld",(temp1*temp1%998244353+temp2*temp2%998244353)%998244353*pow((temp2-temp1)%998244353*2%998244353,998244351)%998244353);
	else
	printf("%lld",(temp2-temp1)*pow(2,998244351)%998244353);
	return 0;
}
