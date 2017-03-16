#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define N 20
#define M 998244353ll
using namespace std;
typedef long long ll;
ll ans;
int l[N],r[N],n;
inline ll rev(ll x){
	int k=M-2;ll ret=1ll;
	while(k){
		if(k&1) ret=ret*x%M;
		x=x*x%M;k>>=1;
	}
	return ret;
}
inline void Aireen(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&l[i],&r[i]);
	if(n==1){
		if(1ll*l[1]*r[1]>0ll) printf("%lld\n",1ll*(abs(l[1])+abs(r[1]))*rev(2ll)%M);
		else printf("%lld\n",(1ll*(1+r[1])*r[1]/2+1ll*(1-l[1])*(-l[1])/2)%M*rev((ll)(r[1]-l[1]+1))%M);
	}
}
int main(){
	freopen("abs.in","r",stdin);
	freopen("abs.out","w",stdout);
	Aireen();
	fclose(stdin);
	fclose(stdout);
	return 0;
}

