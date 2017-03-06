#include<map>
#include<time.h>
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
#define M 31234
#define N 1234
int n,m,k,sum;
int cnt=1,lst[N],g[N][N];

struct edge{int to,nxt,cap;}e[M];
void ins(int a,int b,int c){e[++cnt]=(edge){b,lst[a],c};lst[a]=cnt;}
void lnk(int a,int b,int c){ins(a,b,c/*,d*/);ins(b,a,0/*,-d*/);}
/*int dis[N],ans,pr[N];bool inq[N];queue<int>q;
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
}*/
int h[N],S,T;queue<int>q;
bool bfs(){
	memset(h,-1,sizeof(h));
	q.push(S);h[S]=0;
	while(!q.empty()){
		int c=q.front();q.pop();
		for(int i=lst[c],b;i;i=e[i].nxt){
			if(h[b=e[i].to]==-1&&e[i].cap){
				h[b]=h[c]+1;
				q.push(b);
			}
		}
	}
	return h[T]!=-1;
}
int dfs(int v,int f){
	if(v==T)return f;
	int used=0,w=0;
	for(int i=lst[v],b;i;i=e[i].nxt){
		if(h[b=e[i].to]==h[v]+1&&e[i].cap){
			w=dfs(b,min(e[i].cap,f-used));
			e[i].cap-=w;
			e[i^1].cap+=w;
			used+=w;
			if(used==f)return used;
		}
	}
	if(!used)h[v]=-1;
	return used;
}
void dinic(){while(bfs())sum-=dfs(S,inf);}
int sx[N],sy[N],x[N],y[N];
bool chk(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			sx[i]+=g[i][j],sy[j]+=g[i][j];
	} 
	for(int i=1;i<=n;i++)if(sx[i]+x[i]>m)return 1;
	for(int i=1;i<=m;i++)if(sy[i]+y[i]>n)return 1;
	return 0;
}
int main(){
	FO(chessman);
	n=gi;m=gi;k=gi;
	S=0;T=n+m+1;	
	for(int i=1,j;i<=n;i++)sum+=x[i]=gi,lnk(S,i,x[i]);
	for(int i=1,j;i<=m;i++)sum+=y[i]=gi,lnk(i+n,T,y[i]);
	for(int i=1,x,y;i<=k;i++)g[x=gi][y=gi]=1;
	if(chk()){puts("No Solution");return 0;}
	for(int x=1;x<=n;x++)
		for(int y=1;y<=m;y++){
			if(!g[x][y])lnk(x,y+n,1);
		}
	//cout<<sum+min_cost_flow();
	dinic();cout<<sum;
	return 0;
}
/*


*/

