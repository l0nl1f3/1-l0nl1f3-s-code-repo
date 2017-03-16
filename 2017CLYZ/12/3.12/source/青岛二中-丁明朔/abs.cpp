#include<cstdio>
#define ll long long
#define mod 998244353
using namespace std;

ll ksm(ll a,ll b){
	ll ret=1;
	while(b){
		if(b&1) ret=ret*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ret;
}

int main(){
	freopen("abs.in","r",stdin);
	freopen("abs.out","w",stdout);
	int n;
	ll l,r;
	scanf("%d",&n);
	scanf("%I64d%I64d",&l,&r);
	if(r<=0){
		ll d=((-r)+(-l))*ksm(2,mod-2)%mod;
		printf("%I64d\n",d);
	}else if(l>=0){
		ll d=(r+l)*ksm(2,mod-2)%mod;
		printf("%I64d\n",d);
	}else{
		ll d=(r*r%mod+l*l%mod)*ksm((r-l)*2,mod-2)%mod;
		printf("%I64d\n",d);
	}
	return 0;
}
