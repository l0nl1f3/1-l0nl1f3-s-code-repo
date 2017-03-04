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
#define N 550
#define M 1001234
int n,m,t,x[N],y[N],z[N],g[N+N],f[N][N];
/*所有的横坐标，所有的纵坐标，打乱顺序
猜n个互不相同的位置，满足无论他什么猜，都能猜对k个 
*/
void lisan(int x[N]){
	for(int i=1;i<=n;i++)z[i]=x[i];
	sort(z+1,z+n+1);
	t=unique(z+1,z+n+1)-z-1;
	for(int i=1;i<=n;i++)x[i]=lower_bound(z+1,z+t+1,x[i])-z; 
}
struct edge{int to,nxt,cst,cap;}e[M];
int cnt=1,lst[N],rp[M],S,T; 
void ins(int a,int b,int c,int d){
	e[++cnt]=(edge){b,lst[a],c,d};lst[a]=cnt;
	e[++cnt]=(edge){a,lst[b],-c,0};lst[b]=cnt; 
}
int dis[N],ans,pr[N];bool inq[N];queue<int>q;
bool spfa(){
	memset(dis,0x3f,sizeof dis);
	q.push(S);inq[S]=1;dis[S]=0;
	while(!q.empty()){
		int c=q.front();inq[c]=0;q.pop();
		for(int i=lst[c],b;i;i=e[i].nxt){
			if(dis[c]+e[i].cst<dis[b=e[i].to]&&e[i].cap>0){
				dis[b]=dis[c]+e[i].cst;
				pr[b]=i;
				rp[i]=c; 
				if(!inq[b])q.push(b),inq[b]=1; 
			}
		}
	}
	return dis[T]!=0x3f3f3f3f;
} 
int min_cost_flow(){
	while(spfa()){
		int v=inf;
		for(int i=pr[T];i!=S;i=pr[rp[i]])gmin(v,e[i].cap);
		for(int i=pr[T];i!=S;i=pr[rp[i]]){
			e[i].cap-=v,e[i^1].cap+=v,ans+=v*e[i].cst;
		}
	}
	return ans;
}
int main(){
	FO(guess);
	n=gi;for(int i=1;i<=n;i++)x[i]=gi,y[i]=gi;
	lisan(x);m=t;lisan(y);
	for(int i=1;i<=n;i++){
		g[x[i]]++;g[y[i]+m]++;
		f[x[i]][y[i]]=1;
	}
	S=0;T=m+t+1;
	for(int i=1;i<=m;i++)if(g[i])ins(0,i,0,g[i]);
	for(int i=m+1;i<=m+t;i++)if(g[i])ins(i,T,0,g[i]);
	for(int i=1;i<=m;i++)	
		for(int j=1;j<=t;j++)
			ins(i,j+m,f[i][j],1);
	cout<<min_cost_flow();
	return 0;
}

