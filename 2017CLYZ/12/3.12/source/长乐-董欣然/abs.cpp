#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>
using namespace std;
typedef long long ll;
const int mod=998244353;
ll fz,fm;
int l[20],r[20],n;
ll ksm(ll x,int d)
{
	ll res=1;
	for (; d; d/=2, x=x*x%mod)
	if (d%2) res=res*x%mod;
	return res;
}
int main()
{
	freopen("abs.in","r",stdin);
	freopen("abs.out","w",stdout);
	scanf("%d",&n);
	for (int i=1; i<=n; ++i){
		scanf("%d%d",&l[i],&r[i]);
	}
	
	if (l[1]*r[1]>0){
		fz=abs(r[1]+l[1]);
		printf("%I64d",fz*ksm(2,mod-2)%mod);
	} 
	if (l[1]<0){
		fz=l[1]*l[1]+r[1]*r[1];
		fm=(r[1]-l[1])*2;
		//printf("%I64d %I64d\n",fz,fm);
		printf("%I64d",fz*ksm(fm,mod-2)%mod);
	}
}
