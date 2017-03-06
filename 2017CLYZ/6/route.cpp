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
#define L 20
struct edge{int to,nxt;}e[M];int n,cnt,lst[N],a[N];
void ins(int a,int b){e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;}
void lnk(int a,int b){ins(a,b);ins(b,a);}
int g[N][L],d[N],du[N];long long h[N][L],bs[N];

void dfs(int v,int f=0){
	g[v][0]=f;h[v][0]=du[v]; 
	for(int i=1;i<L;i++){
		cerr<<v<<","<<i<<endl;
		g[v][i]=g[g[v][i-1]][i-1];
		h[v][i]=h[v][i-1]+h[g[v][i-1]][i-1]*bs[i-1];
	}
	for(int i=lst[v],b;i;i=e[i].nxt){
		cerr<<"-> "<<e[i].to<<endl; 
		if((b=e[i].to)==f)continue;
		d[b]=d[v]+1;
		dfs(b,v);
	}
} 
int xy(int x,int y){
	for(int i=L-1;~i;i--)if(h[x][i]==h[y][i])x=g[x][i],y=g[y][i];
	return g[x][0]<g[y][0];
}
int height(int x,int y){
	int ans=0;
	for(int i=L-1;~i;i--)if(d[x]>=(1<<i)&&h[x][i]==h[y][i])x=g[x][i],y=g[y][i],ans+=(1<<i);			
	return ans;
}
int rk[N];
int main(){
	FO(route);
	n=gi;
	for(int i=1,x,y;i<n;i++)du[x=gi]++,du[y=gi]++,lnk(x,y);
	bs[0]=23333333;for(int i=1;i<L;i++)bs[i]=bs[i-1]*bs[i-1]; 
	d[1]=1;dfs(1);
	for(int i=1;rk[i]=i,i<n;i++);
	sort(rk+1,rk+n+1,xy);
	ll ans=0;
	for(int i=2;i<=n;i++)
		ans=ans+d[i]-height(rk[i],rk[i-1]);
	cout<<ans;
	return 0;
}

