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
#define M N+N
#define B N/6
#define N 100001
bitset<B+3>f[N];
int n,m,t,l[N],r[N],x[N],y[N];
struct edge{int to,nxt;};
struct DAG{
	edge e[M];int n,cnt,lst[N],deg[N];
	void ins(int a,int b){deg[b]++;e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;}
	void topsort(int L,int R){
		queue<int>q;
		for(int i=1;i<=n;i++)f[i].reset();
		for(int i=1;i<=n;i++)if(!deg[i])q.push(i);
		while(!q.empty()){
			int c=q.front();q.pop();
			if(L<=c&&c<=R)f[c].set(c-L);
			for(int i=lst[c],b;b=e[i].to,i;i=e[i].nxt){
				f[b]|=f[c];
				if(!--deg[b])q.push(b);
			}
		}
		for(int i=1;i<=t;i++) if(L<=y[i]&&y[i]<=R&&f[x[i]][y[i]-L]==1){
			puts("NO");exit(0);
		}
	}
}D; 
struct Tarjan{
	edge e[M];int scc,cnt,lst[N],bel[N],low[N],dfn[N],s[N],in[N],sn,ind;
	void ins(int a,int b){e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;}
	void dfs(int v){
        dfn[v]=low[v]=++ind;in[s[++sn]=v]=1;
        for(int i=lst[v],b;b=e[i].to,i;i=e[i].nxt){
            if(!dfn[b])dfs(b),gmin(low[v],low[b]);
            else if(in[b])gmin(low[v],dfn[b]);
        }
        if(dfn[v]==low[v]){
            int x=-1;++scc;
            while(sn&&v!=x){
                in[x=s[sn--]]=0;
                bel[x]=scc;
            }
        }
    } 
    void tarjan(){
		for(int i=1;i<=n;i++)if(!dfn[i])sn=0,dfs(i);
		D.n=scc;
		for(int i=1;i<=n;i++)
			for(int j=lst[i],k;j;j=e[j].nxt)
				if(bel[i]!=bel[k=e[j].to])D.ins(bel[k],bel[i]);
	}
}T;
int main(){
	FO(gplt);
	n=gi;m=gi;for(int i=1;i<=m;i++)l[i]=gi,r[i]=gi,T.ins(l[i],r[i]);
	t=gi;for(int i=1;i<=t;i++)x[i]=gi,y[i]=gi;
	T.tarjan();
	for(int i=1;i<=t;i++)x[i]=T.bel[x[i]],y[i]=T.bel[y[i]];
	for(int L=1,R;R=min(D.n,L+B-1),L<=D.n;L+=B)D.topsort(L,R);
	puts("YES");
	for(int i=1;i<=m;i++)printf("%d %d\n",l[i],r[i]);
}
