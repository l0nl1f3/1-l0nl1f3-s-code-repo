#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
#define fir first
#define sec second
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){ return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){ return a<b?a=b,1:0;}
#define pLI pair<ll,int>
#define mpa make_pair
#define N 1001234 
vector<ll>v;
priority_queue<pLI,vector<pLI >,greater<pLI > >q;
int n,L,m;ll w[N],d[N];
int main(){
	int T,i;
	scanf("%d",&T);
	for(int _=1;_<=T;_++){
		scanf("%d%d%d",&L,&n,&m);
		while(!q.empty())q.pop();v.clear();
		for(i=1;i<=n;i++)scanf("%lld",w+i),q.push(mpa(w[i],i));
		for(i=1;i<=m;i++)scanf("%lld",d+i);
		for(i=1;i<=L;i++){
			pLI p=q.top();q.pop();v.push_back(p.first);
			q.push(mpa(p.first+w[p.second],p.second));
		}
		while(!q.empty())q.pop();
		for(reverse(v.begin(),v.end()),i=1;i<=m;i++)q.push(mpa(d[i],i));
		ll ans=0;
		for(i=0;i<L;i++){
			pLI p=q.top();q.pop();cmax(ans,v[i]+p.first);
			q.push(mpa(p.first+d[p.second],p.second));
		}
		printf("Case #%d: %lld\n",_,ans);
	}
	return 0;
}


