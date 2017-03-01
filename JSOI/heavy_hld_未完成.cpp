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
#define N 201234
#define M 401234
int n,rt;
int b[N],ls[N],rs[N],ans;
struct edge{int to,nxt;};
struct graph{
	edge e[M];int C;
	int lst[N],siz[N],son[N],d[N],an[N],f[N],dfn[N],pos[N],nfd;
	void ins(int a,int b){
		e[++C]=(edge){b,lst[a]};lst[a]=C;
	}
	void dfs(int v,int fa=0){
		siz[v]=1;f[v]=fa;
		for(int b,i=lst[v];i;i=e[i].nxt){
			if((b=e[i].to)!=fa&&!d[b]){
				dfs(b,v);
				d[b]=d[v]+1;
				siz[v]+=siz[b];
				if(siz[b]>siz[son[v]])son[v]=b;
			}
		}
	}
	int dfs2(int v,int fa=1){
		an[v]=fa;dfn[v]=++nfd;pos[nfd]=v;
		if(son[v])dfs2(son[v],fa);
		for(int b,i=lst[v];i;i=e[i].nxt)
			if((b=e[i].to)!=son[v]&&b!=f[v])dfs2(b,b);
	}
	int s[M+M],tag[M+M];bool h[M+M];
	void pd(int x,int l,int r){
		if(l==r)return;		
		tag[x+x]+=tag[x];tag[x+x+1]+=tag[x];
		s[x+x]+=tag[x];s[x+x+1]+=tag[x]; 
		tag[x]=0;
	}
	void pu(int x){s[x]=min(s[x+x],s[x+x+1]);h[x]=h[x+x]|h[x+x+1];}
	void change(int x,int l,int r,int a,int b,int d){
		if(a>r||b<l)return;
		pd(x,l,r);
		if(a<=l&&r<=b)tag[x]+=d,s[x]+=d;
		change(x+x,l,(l+r)/2,a,b,d);change(x+x+1,(l+r)/2+1,r,a,b,d);	
		pu(x);
	}
	int C1(int x,int l,int r,int p){
		pd(x,l,r);
		if(l==r)return h[x]^=1;
		p<=(l+r)/2?C1(x+x,l,(l+r)/2,p):C1(x+x+1,(l+r)/2+1,r,p);
		pu(x); 
	}
	int C2(int x,int l,int r,int p){
		pd(x,l,r);
		if(l==r)return s[x]*=-1;
		p<=(l+r)/2?C2(x+x,l,(l+r)/2,p):C2(x+x+1,(l+r)/2+1,r,p);
		pu(x); 
	}
	int Q1(int x,int l,int r){
		if(s[x]>=0)return 0;
		pd(x,l,r);
		if(l==r)return l;
		int k=Q1(x+x+1,(l+r)/2+1,r);
		return k?k:Q1(x+x,l,(l+r)/2);
	}
	int Q2(int x,int l,int r,int a,int b){
		if(a>r||b<l)return 0;
		if(s[x]>=0)return 0;
		pd(x,l,r);
		if(a<=l&&r<=b)return Q1(x,l,r);
		return Q2(x+x,l,(l+r)/2,a,b)|Q2(x+x+1,(l+r)/2+1,r,a,b);
	}
	int P1(int x,int l,int r){
		if(!h[x])return 0;
		pd(x,l,r);
		if(l==r)return l;
		int k=Q1(x+x+1,(l+r)/2+1,r);
		return k?k:Q1(x+x,l,(l+r)/2);
	}
	int P2(int x,int l,int r,int a,int b){
		if(a>r||b<l)return 0;
		if(!h[x])return 0;
		pd(x,l,r);
		if(a<=l&&r<=b)return Q1(x,l,r);
		return Q2(x+x,l,(l+r)/2,a,b)|Q2(x+x+1,(l+r)/2+1,r,a,b);
	}
	int build(int x,int l,int r){
		if(l==r){
			int y=pos[l];
			if(an[y]==y){
				h[x]=1;
				ans-=y;
			}
			s[x]=siz[ls[y]]-siz[rs[y]];
			if(s[x]<0)s[x]*=-1;
		}
		build(x+x,l,(l+r)/2);
		build(x+x+1,(l+r)/2+1,r);
		pu(x);
	}
	int main(){
	}
}G;
int main(){
	FO(heavy);
	n=gi;
	for(int i=1,l,r;i<=n;i++){
		if(rs[i])G.ins(i,rs[i]),b[rs[i]]=1;
		if(ls[i])G.ins(i,ls[i]),b[ls[i]]=1;
	}
	for(int i=1;i<=n;i++)if(!b[i])rt=i;
	G.main();	
	return 0;
}

