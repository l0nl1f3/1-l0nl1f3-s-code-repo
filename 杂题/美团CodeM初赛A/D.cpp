#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){	return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){	return a<b?a=b,1:0;}
#define N 101234
#define M 201234
struct edge{
	int to,nxt;
}e[M];
int cnt,lst[N],a[N],f[N];
map<int,vector<int>>mp;
typedef pair<int,pair<int,int>>pc;
pc rec[N];
#define fi first
#define se second 
int n,ft[N][20],l[N],r[N],gd[N],dep[N];
int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}
void ins(int a,int b){
	e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;
}
void lnk(int a,int b){ins(a,b);ins(b,a);}
void dfs(int x,int f=0){
	ft[x][0]=f;
	for(int i=1;i<20;i++)ft[x][i]=ft[ft[x][i-1]][i-1];
	for(int i=lst[x],b;b=e[i].to,i;i=e[i].nxt){
		if(b!=f){
			dep[b]=dep[x]+1;
			dfs(b,x);
		}
	}
}
int lca(int x,int y){
	int i;
	if(dep[x]<dep[y])swap(x,y);
	for(i=19;~i;i--)
		if(dep[ft[x][i]]>=dep[y])
			x=ft[x][i];
	if(x==y)return x;
	for(i=19;~i;i--)
		if(ft[x][i]!=ft[y][i])
			x=ft[x][i],y=ft[y][i];
	return ft[x][0];
}
int dist(int x,int y){
	return dep[x]+dep[y]-2*dep[lca(x,y)];
}
pc mrg(int a,int b){return pc(dist(a,b),make_pair(a,b));}
pc operator*(pc a,pc b){
	pc o=max(a,b);
	cmax(o,mrg(a.se.fi,b.se.fi));cmax(o,mrg(a.se.fi,b.se.se));
	cmax(o,mrg(a.se.se,b.se.fi));cmax(o,mrg(a.se.se,b.se.se));
	return o;
}
int zy(vector<int>&b){
	for(auto i:b)
		rec[f[l[i]]=l[i]]=pc(0,make_pair(l[i],l[i])), 
		rec[f[r[i]]=r[i]]=pc(0,make_pair(r[i],r[i]));
	int ans=0;
	for(auto i:b){
		int x=find(l[i]),y=find(r[i]);
		rec[x]=rec[x]*rec[y];f[y]=x;
		cmax(ans,rec[x].fi);		
	}
	return ans;
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<n;i++)scanf("%d%d",&j,&k),lnk(l[i]=j,r[i]=k);
	dfs(1);
	for(i=1;i<=n;i++)scanf("%d",a+i);
	for(i=1;i<n;i++){
		j=__gcd(a[l[i]],a[r[i]]);
		for(k=2;k*k<=j;k++)
			if(j%k==0)for(mp[k].push_back(i);j%k==0;j/=k);
		if(j>1)mp[j].push_back(i);
	}
	int ans=0;
	for(auto i:mp)cmax(ans,zy(i.se));
	cout<<ans+1;
	return 0;
}



