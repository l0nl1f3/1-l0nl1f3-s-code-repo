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
#define M 423456
#define N 123456
struct edge{int to,nxt,v;};
struct graph{
	edge e[M];int n,m,lst[N],cnt;
	void resize(int a,int b){n=a;m=b;cnt=0;memset(lst,0,sizeof(lst));}
	graph(){cnt=0;}
	graph(int n,int m):n(n),m(m){}
	edge operator[](int a){return e[a];};
	void ins(int a,int b,int c){e[++cnt]=(edge){b,lst[a],c};lst[a]=cnt;}
	void lnk(int a,int b,int c){ins(a,b,c);ins(b,a,0);}
};
struct Max_Flow{
	graph G;
	int h[N],s,t;
	Max_Flow(){G.cnt=1;}
	bool bfs(){
		memset(h,-1,sizeof(h));
		queue<int>q;q.push(s);h[s]=0; 
		while(!q.empty()){
			int c=q.front();q.pop();
			for(int i=G.lst[c],b;i;i=G[i].nxt)
				if(h[b=G[i].to]==-1&&G[i].v){
					h[b]=h[c]+1;q.push(b);
				}
		}
		return h[t]!=-1;
	}
	int dfs(int v,int f){
		if(v==t)return f;
		int used=0,w;
		for(int i=G.lst[v],b;i;i=G[i].nxt){
			if(h[b=G[i].to]==h[v]+1){
				w=dfs(b,min(G[i].v,f-used));
				G.e[i].v-=w;
				G.e[i^1].v+=w;
				used+=w;if(used==f)return used;
			}
		}
		if(!used)h[v]=-1;
		return used;
	}
	int dinic(){
		int ans=0;
		while(bfs())ans+=dfs(s,inf);
		return ans;
	}
}_;
int n,m;char mp[70][70];
int h[70][70],s[70][70],hn,sn;
int main(){
	n=gi;m=gi;
	for(int i=1;i<=n;i++)scanf("%s",mp[i]+1);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		if(mp[i][j]=='#')continue;
		if(!h[i][j]){
			h[i][j]=++hn;
			for(int k=j+1;mp[i][k]!='#'&&k<=m;k++)h[i][k]=h[i][j];
			for(int k=j-1;mp[i][k]!='#'&&k;k--)h[i][k]=h[i][j];
		}
		if(!s[i][j]){
			s[i][j]=++sn;
			for(int k=i+1;mp[k][j]!='#'&&k<=n;k++)s[k][j]=s[i][j];
			for(int k=i-1;mp[k][j]!='#'&&k;k--)s[k][j]=s[i][j];
		}
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
		if(mp[i][j]=='*')_.G.lnk(s[i][j],sn+h[i][j],1);
	_.s=sn+hn+1;_.t=sn+hn+2;
	for(int i=1;i<=sn;i++)_.G.lnk(_.s,i,1);	
	for(int i=1;i<=hn;i++)_.G.lnk(i+sn,_.t,1);
	cout<<_.dinic();
	return 0;
} 

