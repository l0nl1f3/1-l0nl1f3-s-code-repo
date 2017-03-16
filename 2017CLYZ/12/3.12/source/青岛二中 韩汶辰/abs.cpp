#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int mod=998244353;
ll ans;
ll ksm(ll x,int y)
{
	ll res=1;
	while(y)
	{
		if(y&1)res=(res*x)%mod;
		x=(x*x)%mod;y>>=1;
	}
	return res;
}
int main()
{
	freopen("abs.in","r",stdin);
	freopen("abs.out","w",stdout);
	int i,j,k,n,l,r;
	scanf("%d%d%d",&n,&l,&r);
	if(l>=0)ans=((ll)(l+r)*ksm(2,mod-2))%mod;
	else if(r<=0)ans=((ll)(-l-r)*ksm(2,mod-2))%mod;
	else
	{
		ans=((ll)(-l)*(ll)(-l)+(ll)r*(ll)r)%mod;
		ans=(ans*ksm(-2*l+2*r,mod-2))%mod;
	}
	cout<<ans<<endl;
	return 0;
}
