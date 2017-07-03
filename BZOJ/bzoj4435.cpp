#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
#define fir first
#define sec second
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){ return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){ return a<b?a=b,1:0;}
#define N 3333
#define M 10888
struct edge{int to,nxt;}e[M];
int n,m,cnt=1,s[N],sn,lst[N],f[N],dfn[N],low[N],isd[M],bel[N],flow[N][N],scc,ind;
unsigned long long  hs[N];
const unsigned long long sd=10007;
void ins(int a,int b){
	e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;
}
void lnk(int a,int b){
	ins(a,b);ins(b,a);
}
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}

void dfs(int x,int fa=0){
	dfn[x]=low[x]=++ind;
	s[++sn]=x;
	for(int i=lst[x],b,c;b=e[i].to,i;i=e[i].nxt)
		if(!isd[i]&&b!=fa)
			if(!dfn[b]){
				dfs(b,x); cmin(low[x],low[b]);
				if(low[b]>dfn[x])
					for(++scc,c=0;c!=b;){
						c=s[sn--];
						hs[c]=hs[c]*sd+scc;
					}
			}
			else cmin(low[x],dfn[b]);
} 
void tarjan(){
	scc=ind=0;
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	for(int i=1;i<=n;i++)
		if(!dfn[i]){
			dfs(i);++scc;
			while(sn){
				int c=s[sn--];
				hs[c]=hs[c]*sd+scc;
			}
		}
}
int main(){
	int i,j,k;FO(flow);
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)f[i]=i;
	for(i=1;i<=m;i++){
		scanf("%d%d",&j,&k);
		lnk(j,k);f[find(j)]=find(k);
	}
	memset(flow,-1,sizeof(flow));
	tarjan();
	for(i=1;i<=n;i++)
		for(j=i+1;j<=n;j++)
			if(find(i)!=find(j))
				flow[i][j]=0;
			else if(hs[i]!=hs[j])
				flow[i][j]=1;
	memset(hs,0,sizeof(hs));
	for(i=2;i<=cnt;i+=2){
		isd[i]=isd[i^1]=1;
		tarjan();
		isd[i]=isd[i^1]=0;
	}
	//for(i=1;i<=n;i++)printf("%d %llu\n",i,hs[i]);
	//puts("");for(i=1;i<=n;i++)printf("%llu ",hs[i]);
	for(i=1;i<=n;i++)
		for(j=i+1;j<=n;j++){
			if(~flow[i][j])continue;
			if(hs[i]==hs[j])flow[i][j]=3;
			else flow[i][j]=2;
		}
	int ans=0;
	for(i=1;i<=n;i++)
		for(j=i+1;j<=n;j++)
			ans+=flow[i][j];
	cout<<ans;
	return 0;
}

