#include <queue>
#include <cstdio>
#include <cstring> 
#include <iostream>
#define inf 0x3f3f3f3f
#define N 501
#define V N*N*2 
#define E V*3 
using namespace std;
struct edge{int to,nxt,cap;}e[E];
int n,s,t,sum,cnt=1,lst[V],h[V];
void ins(int a,int b,int c){e[++cnt]=(edge){b,lst[a],c};lst[a]=cnt;}
void lnk(int a,int b,int c){ins(a,b,c);ins(b,a,0);}
queue<int>q;
bool bfs(){
	memset(h,-1,sizeof(h));
	q.push(s);h[s]=0;
	while(!q.empty()){
		int c=q.front();q.pop();
		for(int i=lst[c],b;b=e[i].to,i;i=e[i].nxt){
			if(!~h[b]&&e[i].cap){
				h[b]=h[c]+1;
				q.push(b);
			}
		}
	}
	return ~h[t];
} 
int dfs(int v,int f=inf){
	if(v==t)return f;
	int used=0,w;
	for(int i=lst[v],b;b=e[i].to,i;i=e[i].nxt){
		if(h[b]==h[v]+1&&e[i].cap>0){
			w=dfs(b,min(e[i].cap,f-used));
			e[i].cap-=w;e[i^1].cap-=w;
			used+=w;
			if(used==f)return used;
		}
	}
	if(!used)h[v]=-1;
	return used;
}
int dinic(){
	int ans=0;
	while(bfs())ans+=dfs(s);
	return ans; 
}
int main(){
	scanf("%d",&n);
	t=n*(n+1)+1;
	for(int i=1;i<=n;i++)
		for(int j=1,k;j<=n;j++){
			scanf("%d",&k);sum+=k;
			lnk(i,i*n+j,inf);
			lnk(j,i*n+j,inf);
			lnk(i*n+j,t,k);
		}
	for(int i=1,k;i<=n;i++){
		scanf("%d",&k);
		lnk(s,i,k);
	}
	printf("%d\n",sum-dinic()); 
	return 0;
}
