#include<map>
#include<stack>
#include<queue>
#include<cstdio>
#include<string>
#include<bitset>
#include<vector>
#include<cstring>
#include<complex>
#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;
#define fi first
#define se second
#define il inline
#define mp make_pair
#define pb push_back
#define ll long long
#define gc getchar()
#define inf 1001001001
#define Ri register int
#define Pii pair<int,int>
#define gmax(a,b) (a)=max((a),(b))
#define gmin(a,b) (a)=min((a),(b))
#define infll 1001001001001001001LL
#define dbg(vari) cerr<<#vari<<" = "<<(vari)<<endl
#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
il int read(){bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;}
#define gi read()
#define N 501234
struct edge{int a,b;ll c;}e[N+N];
bool cmp(edge a,edge b){return a.c<b.c;} 
int n,m,q,f[N];ll v[N],t=infll;int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
int fst(){
	ll ans=0;
	sort(e+1,e+m+1,cmp);for(int i=1,u,v;i<=m;i++){
		u=find(e[i].a);v=find(e[i].b);if(u!=v)f[u]=v,ans+=e[i].c;
	}
	cout<<ans<<endl;
}
int main(){
	n=gi;q=gi;
	for(int i=0;i<=n;i++)f[i]=i,v[i]=infll;
	for(int i=1,a,b;i<=q;i++){
		e[++m].a=gi;e[m].b=gi;e[m].c=gi;
		gmin(v[e[m].a],e[m].c+1);gmin(v[e[m].b],e[m].c+2);
	}
	for (int i=0,x=0;i<3*n;i++,x=(x+1)%n){
		v[x]=min(v[x],t);
		t=min(t,v[x])+2;
	}
	for(int i=0;i<n;i++)e[++m]=(edge){i,(i+1)%n,v[i]};fst();
	return 0;
}

