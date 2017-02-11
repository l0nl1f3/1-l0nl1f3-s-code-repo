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
#define N 123456
#define M 223456
int n,m,ans[N];
struct edge{int to,nxt;}; 
struct graph{
	edge e[M];int n,m,lst[N],cnt;
	int dg[N],gd[N];
	void resize(int a,int b){n=a;m=b;cnt=0;memset(lst,0,sizeof(lst));}
	graph(){cnt=0;}
	graph(int n,int m):n(n),m(m){}
	edge operator[](int a){return e[a];};
	void ins(int a,int b){e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;++dg[b];++gd[a];}
	int dfs(int v){
		if(!gd[v])return ans[v]=1;
		if(~ans[v])return ans[v];
		int res=0;
		for(int i=lst[v];i;i=e[i].nxt)res+=dfs(e[i].to);
		return ans[v]=res;
	}
}G;
int main(){	
	n=gi;m=gi;memset(ans,-1,sizeof(ans));
	for(int i=1,u,v;i<=m;i++)u=gi,v=gi,G.ins(u,v);
	int res=0;for(int i=1;i<=n;i++)if(!G.dg[i]&&G.gd[i])res+=G.dfs(i);
	return printf("%d\n",res),0;
}

