 
#include<map>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define inf 0x3f3f3f3f
#define N 101234
#define M 3001234
#define ll long long
using namespace std;
map<pair<int,int> ,int>nd;
int c,r,n,cnt=1,s,t,lst[N],h[N],x[N],y[N],v[N];
struct edge{int to,nxt,cap;}e[M];queue<int>q;
void ins(int a,int b,int c){e[++cnt]=(edge){b,lst[a],c};lst[a]=cnt;}
void lnk(int a,int b,int c){ins(a,b,c);ins(b,a,0);}
bool bfs(){
	memset(h,-1,sizeof(h));
	h[s]=0;q.push(s);
	while(!q.empty()){
		int c=q.front();q.pop();
		for(int i=lst[c];i;i=e[i].nxt){
			if(!~h[e[i].to]&&e[i].cap>0){
				h[e[i].to]=h[c]+1;
				q.push(e[i].to);
			}
		}
	}
	return ~h[t];
}
int dfs(int v,int f){
	if(v==t)return f;
	int used=0,w;
	for(int i=lst[v],b;b=e[i].to,i;i=e[i].nxt){
		if(h[b]==h[v]+1&&e[i].cap>0){
			w=dfs(b,min(e[i].cap,f-used));
			used+=w;e[i].cap-=w;e[i^1].cap+=w;
			if(used==f)return used;
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
void build_0(int i,int x,int y,int v){
	if(y&1)lnk(s,i,v);
	else{
		nd[make_pair(x+1,y)]?lnk(nd[make_pair(x+1,y)],i,inf),0:0;
		nd[make_pair(x,y+1)]?lnk(nd[make_pair(x,y+1)],i,inf),0:0;
		nd[make_pair(x,y-1)]?lnk(nd[make_pair(x,y-1)],i,inf),0:0;
	}
}
void build_1(int i,int x,int y,int v){
	if(~y&1)lnk(s,i,v);
	else{
		nd[make_pair(x-1,y)]?lnk(nd[make_pair(x-1,y)],i,inf),0:0;
		nd[make_pair(x,y+1)]?lnk(nd[make_pair(x,y+1)],i,inf),0:0;
		nd[make_pair(x,y-1)]?lnk(nd[make_pair(x,y-1)],i,inf),0:0;
		nd[make_pair(x+1,y)]?lnk(i,nd[make_pair(x+1,y)],min(::v[nd[make_pair(x+1,y)]],v)),0:0;
	}
}
void build_2(int i,int x,int y,int v){
	if(~y&1)lnk(i,t,v);
	else{
		nd[make_pair(x+1,y)]?lnk(i,nd[make_pair(x+1,y)],inf),0:0;
		nd[make_pair(x,y+1)]?lnk(i,nd[make_pair(x,y+1)],inf),0:0;
		nd[make_pair(x,y-1)]?lnk(i,nd[make_pair(x,y-1)],inf),0:0;
	}
}
void build_3(int i,int x,int y,int v){
	if(y&1)lnk(i,t,v);
	else{
		nd[make_pair(x-1,y)]?lnk(i,nd[make_pair(x-1,y)],inf),0:0;
		nd[make_pair(x,y+1)]?lnk(i,nd[make_pair(x,y+1)],inf),0:0;
		nd[make_pair(x,y-1)]?lnk(i,nd[make_pair(x,y-1)],inf),0:0;
		nd[make_pair(x+1,y)]?lnk(nd[make_pair(x+1,y)],i,min(::v[nd[make_pair(x+1,y)]],v)),0:0;
	}
}
int main(){
	freopen("block.in","r",stdin);
	freopen("block.out","w",stdout);
	int i,j,k;
	scanf("%d%d%d",&c,&r,&n);
	for(i=1;i<=n;i++)scanf("%d%d%d",x+i,y+i,v+i),nd[make_pair(x[i],y[i])]=i;
	for(t=n+1,i=1;i<=n;i++){
		j=x[i]&3;
		if(j==0)build_0(i,x[i],y[i],v[i]);
		if(j==1)build_1(i,x[i],y[i],v[i]);
		if(j==2)build_2(i,x[i],y[i],v[i]);
		if(j==3)build_3(i,x[i],y[i],v[i]);
	}
	printf("%d",dinic());
}
