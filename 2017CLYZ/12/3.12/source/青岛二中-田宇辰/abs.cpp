#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int mod=998244353;

ll power(ll x,int y){
	ll ret=1;
	for(;y;y>>=1,x=x*x%mod){
		if(y&1)	ret=ret*x%mod;
	}
	return ret;
}

int main(){
	freopen("abs.in","r",stdin);
	freopen("abs.out","w",stdout);
	int n,l,r;
	scanf("%d",&n);
	scanf("%d%d",&l,&r);
	int tmp;
	if(r<=0){
		tmp=1ll*(-l-r)*power(2,mod-2)%mod;
		printf("%d",tmp);return 0;
	}
	if(l>=0){
		tmp=1ll*(l+r)*power(2,mod-2)%mod;
		printf("%d",tmp);return 0;
	}
	l=-l;
	tmp=1ll*l*l%mod*power(2,mod-2)%mod;
	tmp=(tmp+1ll*r*r%mod*power(2,mod-2)%mod)%mod;
	tmp=1ll*tmp*power(l+r,mod-2);
	printf("%d",tmp);return 0;
}













