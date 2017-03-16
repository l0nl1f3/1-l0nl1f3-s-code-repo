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
#define N 301234
#define M 601234
int n,m,w[N],ct[N];ll ans[N];
struct graph{
	struct edge{int to,nxt;}e[M];int cnt,lst[N];
	void ins(int a,int b){e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;}
	void lnk(int a,int b){ins(a,b),ins(b,a);}
	int dfn[N],big[N],siz[N],d;
	int sum[N],tag[N],len,s,fn;
	void dfs0(int x,int f=0){
		dfn[++d]=x;
		siz[x]=1;big[x]=0;
		for(int i=lst[x],b;i;i=e[i].nxt){
			if((b=e[i].to)==f||tag[b])continue;
			dfs0(b,x);
			siz[x]+=siz[b];
			gmax(big[x],siz[b]);
		}
	}
	void dfs1(int x,int f,int sgn){
		if(!ct[w[x]]++)sum[w[x]]+=sgn*siz[x],++len;
		s+=sgn*len;
		for(int i=lst[x],b;i;i=e[i].nxt){
			if((b=e[i].to)==f||tag[b])continue;
			dfs1(b,x,sgn);
		} 
		if(!--ct[w[x]])--len;
	}
	int add(int x,int y){if(!ct[x]++)fn+=y-sum[x];}
	int del(int x,int y){if(!--ct[x])fn-=y-sum[x];}
	void dfs2(int x,int f,int sgn){
		add(w[x],sgn);
		ans[x]+=fn+s;
		for(int i=lst[x],b;i;i=e[i].nxt)if((b=e[i].to)!=f&&!tag[b])dfs2(b,x,sgn);
		del(w[x],sgn);
	}
	void main(int x){
		d=0;dfs0(x);
		int i;
		for(i=1;i<=d;i++)
			if(max(siz[x]-siz[dfn[i]],big[dfn[i]])*2<=siz[x]){
				i=dfn[i];
				break;
			}
		d=0;dfs0(i);
		for(int j=lst[i];j;j=e[j].nxt)
			if(!tag[e[j].to])
				dfs1(e[j].to,i,1);
		add(w[i],siz[i]);
		ans[i]+=fn+s;
		del(w[i],siz[i]);
		for(int j=lst[i],b;j;j=e[j].nxt){
			if(!tag[b=e[j].to]){
				dfs1(b,i,-1);
				add(w[i],siz[i]-siz[b]);
				dfs2(b,i,siz[i]-siz[b]);
				del(w[i],siz[i]-siz[b]);
				dfs1(b,i,1); 
				
			}
		}
		for(int i=1;i<=d;i++)sum[w[dfn[i]]]=0;
		s=0;tag[i]=1;
		for(int j=lst[i],b;j;j=e[j].nxt)if(!tag[b=e[j].to])main(b);
	}
}G;
int main(){
	FO(mushroom);
	n=gi;
	for(int i=1;w[i]=gi,i<n;i++);
	for(int i=1;i<n;i++)G.lnk(gi,gi);
	G.main(1);
	for(int i=1;printf("%I64d\n",ans[i++]),i<=n;);
		
	return 0;
}

