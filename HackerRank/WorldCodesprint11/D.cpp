#include<bits/stdc++.h>
#define N 51234
#define M 201234
using namespace std;
int n,m,Q,i,j,k,cnt,lst[N];bitset<N>bs[N];
int scc,dgr[N],bel[N],low[N],dfn[N],s[N],in[N],sn,ind;
struct edge{int to,nxt;}e[M];
void ins(int a,int b){
	++dgr[b];
	e[++cnt]=(edge){b,lst[a]};lst[a]=cnt; 
}
void dfs(int v){
    dfn[v]=low[v]=++ind;in[s[++sn]=v]=1;
    for(int i=lst[v],b;b=e[i].to,i;i=e[i].nxt){
        if(!dfn[b])dfs(b),low[v]=min(low[v],low[b]);
        else if(in[b])low[v]=min(low[v],dfn[b]);
    }
    if(dfn[v]==low[v]){
        int x=-1;++scc;
        while(sn&&v!=x){
            in[x=s[sn--]]=0;
            bel[x]=scc;
        }
    }
}
queue<int>q;
void topsort(){
	for(i=1;i<=n;i++){
		bs[i].set(i); 
		if(!dgr[i])q.push(i);
	}
	while(!q.empty()){
		int c=q.front();q.pop();
		for(i=lst[c];i;i=e[i].nxt){
			int b=e[i].to;
			bs[b]|=bs[c];
			if(!--dgr[b])
				q.push(b);
		}
	}
}
vector<pair<int,int> > vp,rq;
void tarjan(){
	for(i=1;i<=n;i++)if(!dfn[i])sn=0,dfs(i);
	for(i=1;i<=n;i++)
		for(j=lst[i],k;k=e[j].to,j;j=e[j].nxt)
			if(bel[i]!=bel[k])vp.push_back(make_pair(bel[i],bel[k]));
	n=scc;cnt=0;
	memset(dgr,0,sizeof(dgr));
	memset(lst,0,sizeof(lst)); 
	for(i=0;i<vp.size();i++)ins(vp[i].second,vp[i].first);
}
int main(){
	int i,j,k;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)scanf("%d%d",&j,&k),ins(j,k);
	scanf("%d",&Q);
	for(i=1;i<=Q;i++){
		int o,x,d;scanf("%d%d%d",&o,&x,&d);
		if(o==1){
			if(!d)ins(x,++n);
			else ins(++n,x);
		}else{
			rq.push_back(make_pair(x,d));
		}
	}
	tarjan();
	topsort();
	for(i=0;i<rq.size();i++){
		int x=rq[i].first,y=rq[i].second;
		if(bs[bel[x]][bel[y]])puts("Yes");else puts("No");
	}
	return 0;
}
