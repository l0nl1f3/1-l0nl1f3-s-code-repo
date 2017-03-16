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
#define M 201234
#define N 101234
int n,q,r,d[N];bool sb=1,sl=1;
struct edge{int to,nxt;}e[M];int cnt,lst[N],v[N];
void ins(int a,int b){e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;} 
void lnk(int a,int b){d[a]++;d[b]++;ins(a,b);ins(b,a);}
void dfs0(int v,int f,int d){
	::v[v]=1;
	for(int i=lst[v],b;b=e[i].to,i;i=e[i].nxt){
		if(d+1<=r&&f!=v){
			dfs0(b,v,d+1);
		}
	}
}
void BF(){
	while(q--){
		int k=gi;
		for(int i=1;i<=k;i++){
			int a;a=gi;r=gi;
			dfs0(a,0,0);
		}
		int ans=0;
		for(int i=1;i<=n;i++)ans+=v[i];
		printf("%d\n",ans);
		memset(v,0,sizeof(v));
	} 
}int s,dfn[N],dn; 
void dfs1(int v,int f=0){
	dfn[v]=++dn;
	for(int i=lst[v],b;b=e[i].to,i;i=e[i].nxt)
		if(b!=f)dfs1(b,v);
}
int a[N*10],rdx[N*10];Pii rg[N*10];
void GS(){
	for(int i=1;i<=n;i++)if(d[i]==1)s=i;
	dfs1(s);
	while(q--){
		int k=gi;for(int i=1;i<=k;i++)a[i]=gi,rdx[i]=gi;
		for(int i=1;i<=k;i++)rg[i]=mp(max(1,dfn[a[i]]-rdx[i]),min(dfn[a[i]]+rdx[i],n));
		sort(rg+1,rg+k+1);
		int ans=0,L=0,R=-1;
		for(int i=1,l,r;i<=k;i++){
			l=rg[i].fi;r=rg[i].se;
			if(l>R){
				ans+=R-L+1;
				L=l	;R=r; 
			}else gmax(R,r);
		}
		printf("%d\n",ans+R-L+1);
	}
}
int main(){
	FO(guard);n=gi;
	for(int i=1;i<n;i++)lnk(gi,gi); 
	for(int i=1;i<=n;i++)if(d[i]>2)sb=0;
	q=gi;sl=(n<=1000);
	if(sb)GS();
	else if(sl)BF(); 
	return 0;
}

