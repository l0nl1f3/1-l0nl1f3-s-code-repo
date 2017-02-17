//Ð´²»ÍêµÄhnoi2016
//I can't finish even one problem in hnoi2016 
#include<map>
#include<stack>
#include<queue>
#include<cstdio>
#include<string>
#include<bitset>
#include<vector>
#include<cstdlib>
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
#define N 101234
#define M 201234
struct edge{int to,nxt;};
struct graph{
	edge e[M];int n,m,lst[N],cnt;
	void resize(int a,int b){n=a;m=b;cnt=0;memset(lst,0,sizeof(lst));}
	graph(){cnt=0;}
	graph(int n,int m):n(n),m(m){}
	edge operator[](int a){return e[a];};
	void ins(int a,int b){e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;}
	void lnk(int a,int b){ins(a,b);ins(b,a);}
};
struct dheap{
	priority_queue<int>pq,dl;
	void push(int x){pq.push(x);}
	int top(){
		while(!dl.empty()&&pq.top()==dl.top()){
			pq.pop(),dl.pop();
		}
		return pq.empty()?-1:pq.top();
	}
	int pop(){int ans=top();if(!pq.empty())pq.pop();return ans;}
	int del(int x){dl.push(x);}
};
struct SegmentTree{
	dheap d[N*10];
	void change(int k,int l,int r,int a,int b,int v,int tag){
		//cerr<<"^^"<<k<<","<<l<<","<<r<<","<<a<<","<<b<<endl;
		//for(int i=1;i<=100000000;i++);
		if(a>r||b<l)return;
		if(a<=l&&r<=b){if(tag)d[k].push(v);else d[k].del(v);return;}
		change(k+k,l,(l+r)/2,a,b,v,tag);
		change(k+k+1,(l+r)/2+1,r,a,b,v,tag);
	}
	int query(int k,int l,int r,int p){
		if(l==r){
			return d[k].top();
		}
		if(p<=(l+r)/2)return max(d[k].top(),query(k+k,l,(l+r)/2,p));
		else return max(d[k].top(),query(k+k+1,(l+r)/2+1,r,p));
	}
};
struct hld{
	graph G;SegmentTree T;
	vector<Pii >v;
	int n,son[N],siz[N],an[N],fa[N],dep[N],dfn[N],nfd;
	void dfs1(int x,int f=0){
		siz[x]=1;fa[x]=f;
		for(int b,i=G.lst[x];i;i=G[i].nxt){
			if((b=G[i].to)==f)continue;
			dep[b]=dep[x]+1;
			dfs1(b,x);siz[x]+=siz[b];
			if(siz[b]>siz[son[x]])son[x]=b;
		}
	}
	void dfs2(int x,int y=1){
		dfn[x]=++nfd;an[x]=y;
		if(son[x])dfs2(son[x],y);
		for(int i=G.lst[x];i;i=G[i].nxt)if(G[i].to!=fa[x]&&G[i].to!=son[x])dfs2(G[i].to,G[i].to);
	}
	void prep(){dfs1(1);dfs2(1);} 
	void upd(int x,int y,int u,int tag){
		v.clear();
	    while(an[x]!=an[y]){
	        if(dep[an[x]]<dep[an[y]])swap(x,y);
	        v.pb(mp(dfn[an[x]],dfn[x]));
	        x=fa[an[x]];
	    }
	    if(dep[x]<dep[y])swap(x,y);
	    v.pb(mp(dfn[y],dfn[x]));sort(v.begin(),v.end());
	    x=1;
	    for(int i=0;i<v.size();x=v[i].se+1,i++)
	        T.change(1,1,n,x,v[i].fi-1,u,tag);
	    T.change(1,1,n,x,n,u,tag);
	}
	int query(int s){return T.query(1,1,n,dfn[s]);}
}H;
int n,q;
int a[M],b[M],c[M]; 
int main(){
	FO(qaq);
	H.n=n=gi;q=gi;
	for(int i=1,u,v;i<n;i++){
		u=gi;v=gi;H.G.lnk(u,v);
	}H.prep(); 
	for(int i=1;i<=q;i++){
		int s=gi,t;
		if(s==0){a[i]=gi;b[i]=gi;c[i]=gi;H.upd(a[i],b[i],c[i],1);}
		if(s==1){t=gi;H.upd(a[t],b[t],c[t],0);}
		if(s==2)printf("%d\n",H.query(gi));
	}
	return 0;
}

