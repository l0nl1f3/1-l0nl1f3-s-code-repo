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
int n,k,s[1234];
struct LCG{
	int a,b,c,x,fi,se;
	void Gen(){
		memset(s,0,sizeof(s));
		while(!s[x]){
			s[x]=1; 
			x=(x*a+b)%c;
		}
		for(int i=c-1;i;i--)if(s[i]&&k%i!=0){
			if(!fi)fi=i;else 
			if(!se)se=i;else 
			break;
		}
	}
}L[N];
int main(){
	int i;
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++){
		scanf("%d%d%d%d",&L[i].x,&L[i].a,&L[i].b,&L[i].c);L[i].Gen();
	}
	ll ans=0;
	for(i=1;i<=n;i++)ans+=L[i].fi;
	if(!(ans%k)){
		int j=1,k=0;
		for(i=1;i<=n;i++)
			if(cmax(k,L[i].se))j=i;
		ans=ans-L[j].fi+k;
	}
	if(!(ans%k))puts("-1");
	else printf("%I64d",ans);
	return 0;
}


