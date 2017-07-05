#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
#define fir first
#define sec second
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){ return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){ return a<b?a=b,1:0;}
#define M 501234
#define N 51234
struct edge{int to,nxt;}e[M];int cnt=1,lst[N];
void ins(int a,int b){ e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;}
void lnk(int a,int b){ ins(a,b);ins(b,a);}

int n,m,f[N],siz[N],sz[N],dfn[N],g[N],ge[N],cir[M],suc[N],D;
ll ans,s[N];
int find(int x){ return f[x]==x?x:f[x]=find(f[x]);}
void mrg(int x,int y){
	x=find(x);y=find(y);
	if(x!=y)siz[y]+=siz[x],f[x]=y;
}
int qs(int x){return siz[find(x)];}

void dfs(int x,int fa=0){
	int i,j,b;dfn[x]=++D;
	for(i=lst[x];b=e[i].to,i;i=e[i].nxt)
		if(b!=fa)
			if(!dfn[b])ge[b]=i,dfs(b,g[b]=x);
			else if(dfn[b]<dfn[x]){
				for(cir[i]=cir[i^1]=1,suc[j=x]=b;g[j]!=b;j=g[j])
					suc[g[j]]=j,cir[ge[j]]=cir[ge[j]^1]=1;
				cir[ge[j]]=2;cir[ge[j]^1]=1;
			}	
}
void dfs1(int x,int fa=0){
	sz[x]=1;
	for(int i=lst[x],b;b=e[i].to,i;i=e[i].nxt)
		if(b!=fa)
			if(cir[i]!=1){
				dfs1(b,x);sz[x]+=sz[b];
				if(!cir[i]) ans+=(ll)sz[b]*(n-sz[b])-1; 
			}
	if(suc[x]&&dfn[suc[x]]>dfn[x])
		dfs1(suc[x],x),sz[x]+=sz[suc[x]];
}	

int main(){
	int i,j,k,p,q;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
		for(scanf("%d%d",&k,&p);--k;)
			scanf("%d",&q),lnk(p,q),p=q;
	dfs(1);	
	dfs1(1);
	for(i=1;i<=n;i++)f[i]=i,siz[i]=1;
	for(k=1;k<=n;k++)
		for(i=lst[k];i;i=e[i].nxt)	
			if(!cir[i]) mrg(k,e[i].to);
	for(i=1;i<=n;i++)
		if(find(i)==i&&qs(i)>2) s[i]=(ll)qs(i)*(qs(i)-1)/2-qs(i)+1,s[0]+=s[i];
	for(k=1;k<=n;k++)
		for(i=lst[k];i;i=e[i].nxt)
			if(cir[i]&2){
				ll p=s[0]-s[find(k)],L=1,ts=qs(k);
				for(q=e[i].to;q!=k;q=suc[q]) ++L,ts+=qs(q),p-=s[find(q)];
				ans=ans+(ll)L*(ts*(ts-1)/2-ts)+L*p;
			}
	cout<<ans;
	return 0;
}


