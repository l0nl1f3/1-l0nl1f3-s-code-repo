#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
#define fir first
#define sec second
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){ return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){ return a<b?a=b,1:0;}
#define N 10123
int n,k;
struct LCG{
	int a,b,c,x,fi,se,s[1234];
	void Gen(){
		memset(s,-1,sizeof(s));
		int i=0;
		while(!~s[x]){
			s[x]=i++; 
			x=(x*a+b)%c;
		}
		fi=se=-1;
		for(i=c-1;~i;i--)
			if(~s[i]){
				if(!~fi)fi=i;
				else {
					if(!~se)
						if(i%k!=fi%k)se=i;
				}
			}
	}
}L[N];
int main(){
	int i;//FO(generators);
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++){
		scanf("%d%d%d%d",&L[i].x,&L[i].a,&L[i].b,&L[i].c);L[i].Gen();
	}
	ll ans=0;
	for(i=1;i<=n;i++)ans+=L[i].fi;
	if(!(ans%k)){
		int j=1,K=-1e9;
		for(i=1;i<=n;i++)
			if(~L[i].se&&cmax(K,L[i].se-L[i].fi))j=i;
		if(K>-1e9)ans=ans+K;
		if(!(ans%k))puts("-1");
		else{
			for(printf("%d\n",ans),i=1;i<=n;i++)
				printf("%d ",i==j?L[i].s[L[i].se]:L[i].s[L[i].fi]);
		}
	}else{
		for(printf("%d\n",ans),i=1;i<=n;i++)
			printf("%d ",L[i].s[L[i].fi]);	
	}
	return 0;
}


