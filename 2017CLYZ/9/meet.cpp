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
#define N 101234
#define M 201234
#define L 19
int n,q,f[N][L],l[N][L],d[N],dep[N],et[N],etc,etn[N];
struct edge{int to,nxt,v;}e[M];int cnt,lst[N];
void ins(int a,int b,int c){e[++cnt]=(edge){b,lst[a],c};lst[a]=cnt;}
void lnk(int a,int b,int c){ins(a,b,c);ins(b,a,c);}
void dfs(int v,int fa=0){
	f[et[etn[v]=++etc]=v][0]=fa;
	for(int i=1;i<L;i++){
		f[v][i]=f[f[v][i-1]][i-1];
		l[v][i]=l[v][i-1]+l[f[v][i-1]][i-1];
	} 
	for(int i=lst[v],b;b=e[i].to,i;i=e[i].nxt){
		if(b!=fa){
			l[v][0]=mx[v][0]=e[i].v;
			d[b]=d[v]+1;dep[b]=dep[v]+e[i].v;
			dfs(b,v);
			et[++etc]=v;
		}
	}
}
int minn(int i,int j){return d[i]<d[j]?i:j;}
int st[M][L+1],lg[M];
void rmq_init(){
	for(int i=1;i<=etc;i++)st[i][0]=et[i];
	for(int i=etc;i;i--)for(int j=1;j<=L;j++)st[i][j]=minn(st[i][j-1],st[min(i+(1<<j-1),etc)][j-1]);
	for(int i=2;i<=etc;i++)lg[i]=lg[i>>1]+1;
}
int chk(int u,int v,ll t){
	for(int k=L-1;~k;k--)if(d[u]>=w[v]+(1<<k)){
		if(mx[u][k]>t)return 1;u=f[u][k];
	}
	return 0;
}
int lca(int i,int j){
	i=etn[i];j=etn[j];if(i>j)swap(i,j);
	int k=lg[j-i];return minn(st[i][k],st[j-(1<<k)+1][k]);
}
int uu(int u1,int v1,ll t1,int u2,int v2,ll t2,int k){return (d[k=lca(u1,u2)]<=d[v1]||d[k]<=d[v2])?0:chk(k,v1+v2-minn(v1,v2),abs(t1-t2+dep[u1]+dep[u2]-2*dep[k]));}
int dd(int u1,int v1,ll t1,int u2,int v2,ll t2){return uu(u1,v1,t2+dep[u2]-dep[v2],u2,v2,t1+dep[u1]-dep[v1]);}

int main(){
	FO(meet);
	n=gi;q=gi;
	for(int i=1,a,b,c;i<n;i++){a=gi;b=gi;c=gi;lnk(a,b,c);}
	d[1]=1;dfs(1);
	rmq_init();
	while(q--){
		int u1,v1,t1,u2,v2,t2,l1,l2;
		u1=gi;v1=gi;t1=gi;u2=gi;v2=gi;t2=gi;
		l1=lca(u1,v1);l2=lca(u2,v2);
		cout<<l1<<","<<l2<<endl;
	} 
	return 0;
}

