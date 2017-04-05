#include<bits/stdc++.h>
#define N 20001
#define M 888888
using namespace std;
struct edge{int to,nxt,cap;}e[M];int cnt=1,lst[N];
void ins(int a,int b,int c){e[++cnt]=(edge){b,lst[a],c};lst[a]=cnt;}
void lnk(int a,int b,int c){ins(a,b,c);ins(b,a,0);}
int s,t,l,n,m,a[M],b[M],c[M],h[M];queue<int>q;
bool bfs(){
	memset(h,-1,sizeof(h));h[s]=0;q.push(s);
	while(!q.empty()){
		int c=q.front();q.pop();
		for(int i=lst[c],b;b=e[i].to,i;i=e[i].nxt)
			if(e[i].cap>0&&!~h[b]){
				h[b]=h[c]+1;
				q.push(b);
			}
	}
	return ~h[t];
}
int dfs(int v,int f){
	if(v==t)return f;
	int w,used=0;
	for(int i=lst[v],b;b=e[i].to,i;i=e[i].nxt){
		if(h[b]==h[v]+1&&e[i].cap>0){
			w=dfs(b,min(e[i].cap,f-used));
			e[i].cap-=w;e[i^1].cap+=w;used+=w;
			if(used==f)return used;
		}
	}
	if(!used)h[v]=-1;
	return used;
}
int main(){
	int i,j,k,o;
	for(scanf("%d%d",&n,&m),m++,i=1;i<=m;i++)scanf("%d%d%d",a+i,b+i,c+i);
	for(s=a[m],t=b[m],i=1;i<m;i++)
		if(c[i]<c[m]){
			lnk(a[i],b[i],1);
			lnk(b[i],a[i],1);
		}
	for(j=0;bfs();)
		j+=dfs(s,1e9);
	memset(lst,0,sizeof(lst));
	for(s=a[m],t=b[m],i=cnt=1;i<m;i++)
		if(c[i]>c[m]){
			lnk(a[i],b[i],1);
			lnk(b[i],a[i],1);
		}
	for(;bfs();)
		j+=dfs(s,1e9);
	
	return printf("%d",j),0;
}
