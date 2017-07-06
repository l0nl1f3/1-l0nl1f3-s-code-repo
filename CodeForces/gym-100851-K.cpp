#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
#define fir first
#define sec second
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){ return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){ return a<b?a=b,1:0;}
#define N 101234
#define NoSol return puts("There is no route, Karl!"),0; 
vector<int>e[N],g;
int n,m,bc,ed[N],id[N],od[N],v[N],son[N];
struct ufs{
	int f[N];
	void init(){ for(int i=1;i<=n;i++)f[i]=i;}
	int find(int x){ return f[x]==x?x:f[x]=find(f[x]);}
	void mrg(int x,int y){ f[find(x)]=find(y);}
}fs,gs;
void dfs(int x){
	if(v[x])return;
	v[x]=1;printf("%d ",x);
	if(e[x].size()==1)
		dfs(e[x][0]);
	else dfs(e[x][son[x]]);
}
void dfs0(int d){
	if(d==g.size()){
		int zy=0;
		for(auto i:g) if(++id[e[i][son[i]]]>1) zy=1;
		for(auto i:g) --id[e[i][son[i]]];
		if(zy)return;
		for(auto i:g){
			int x=fs.find(i),y=fs.find(e[i][son[i]]);
			gs.f[x]=x;gs.f[y]=y;
		}
		int cnt=bc;
		for(auto i:g){
			int x=fs.find(i),y=fs.find(e[i][son[i]]);
			x=gs.find(x);y=gs.find(y);
			if(x!=y) {gs.f[x]=y;--cnt;}
		}
		if(cnt==1){
			memset(v,0,sizeof(v));
			dfs(1);puts("1");exit(0);
		}
	}else
		for(int i=0;i<e[g[d]].size();i++) son[g[d]]=i,dfs0(d+1);
}
int main(){
	int i,j,k;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
		scanf("%d%d",&j,&k),e[j].push_back(k);
	if(m<n)NoSol;
	for(i=1;i<=n;i++){
		if(!e[i].size()||(m-e[i].size()+1)<n)NoSol;
		if(e[i].size()>1)g.push_back(i);
	}
	fs.init();gs.init();
	if(g.size()>20)NoSol;
	for(bc=n,i=1;i<=n;i++){
		if(e[i].size()>1)continue;
		k=e[i][0];
		if(++id[k]>1)NoSol;
		if(fs.find(i)!=fs.find(k))
			fs.mrg(i,k),--bc;
	}
	dfs0(0);
	NoSol;
	return 0;
}


