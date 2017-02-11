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
#define M 1001234
#define N 501234
#define D 22
int n,m,d,a[N],b[N],f[N][D],g[N][D];
struct edge{int to,nxt;};
struct graph{
	edge e[M];int lst[N],cnt;
	void ins(int a,int b){e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;}
	void lnk(int a,int b){ins(a,b),ins(b,a);}
	void dfs(int v,int fa=0){
		f[v][d+1]=inf;
		if(a[v])g[v][0]=f[v][0]=b[v];
		for(int i=d;i;i--)f[v][i]=b[v];
		for(int i=lst[v],b;i;i=e[i].nxt){
			if((b=e[i].to)==fa)continue;
			dfs(b,v);
			for(int j=d;~j;j--)f[v][j]=min(f[v][j+1],min(f[v][j]+g[b][j],f[b][j+1]+g[v][j+1]));
			g[v][0]=f[v][0];for(int j=1;j<=d+1;j++)g[v][j]=min(g[v][j-1],g[v][j]+g[b][j-1]);
		}
	}
} G;
int main(){
	n=gi;d=gi;
	for(int i=1;b[i]=gi,i<n;i++);
	m=gi;for(int i=1;i<=m;i++)a[gi]=1;
	for(int i=1;i<n;i++)G.lnk(gi,gi);
	return G.dfs(1),printf("%d",g[1][0]),0;
}

