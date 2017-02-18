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
#define bg begin
#define ed end
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
#define L 20
#define M N*2
#define N 101234
#define S 2001234
struct PersisdentTree{
	int ls[S],rs[S],s[S],rt[N],mx,cnt;
	void insert(int x,int &y,int l,int r,int p){
		s[y=++cnt]=s[x]+1;
		if(l==r){
		//	printf("put 1 in [%d,%d]\n",l,r);
			return;
		}
		ls[y]=ls[x];rs[y]=rs[x];
		if(p<=(l+r)/2)insert(ls[x],ls[y],l,(l+r)/2,p);
		else insert(rs[x],rs[y],(l+r)/2+1,r,p);
	}
	void insert(int x,int y,int w){
	//	printf("%d->%d v=%d\n",x,y,w); 
		insert(rt[x],rt[y],1,mx,w);
	}
	int query(int w,int x,int y,int z,int l,int r,int k){
		if(l==r)return l;
		int p=s[ls[w]]+s[ls[x]]-s[ls[y]]-s[ls[z]]; 
		//printf("[%d,%d]=%d\n",l,r,k); 
		if(p<k)return query(rs[w],rs[x],rs[y],rs[z],(l+r)/2+1,r,k-p);
		else return query(ls[w],ls[x],ls[y],ls[z],l,(l+r)/2,k);
	}
	int que(int x,int y,int z,int g,int k){return query(rt[x],rt[y],rt[z],rt[g],1,mx,k);}
}PT;
struct Edge{int to,nxt;};
struct Graph{
	Edge e[M];vector<int>v;
	int n,m,cnt,lst[N],w[N],a[N],d[N],f[N][L];
	void ins(int a,int b){e[++cnt]=(Edge){b,lst[a]};lst[a]=cnt;}
	void lnk(int a,int b){ins(a,b);ins(b,a);}
	void dfs(int x,int fa=0){
		PT.insert(fa,x,w[x]);f[x][0]=fa;
		for(int i=1;i<L;i++)f[x][i]=f[f[x][i-1]][i-1];
		for(int b,i=lst[x];i;i=e[i].nxt){
			if((b=e[i].to)==fa)continue;
			d[b]=d[x]+1;dfs(b,x);
		}
	}
	int lca(int x,int y){
		if(d[y]>d[x])swap(x,y);
		for(int i=L-1;~i;i--)if(d[x]-d[y]>=(1<<i))x=f[x][i];
		if(x==y)return x;
		for(int i=L-1;~i;i--)if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
		return x==y?x:f[x][0];
	}
	void prep(int zy,int sb){
		m=(n=zy)-1;
		for(int i=1;i<=n;i++)v.pb(w[i]=gi);
		sort(v.bg(),v.ed());v.erase(unique(v.bg(),v.ed()),v.ed());
		for(int i=1,t;i<=n;gmax(PT.mx,t),i++){
		 	t=lower_bound(v.bg(),v.ed(),w[i])-v.bg()+1;
			a[t]=w[i];
		 	w[i]=t;
		}
		//for(int i=1;i<=n;i++)printf("%d:%d\n",w[i],a[w[i]]);puts("");
		for(int i=1;i<=m;i++)lnk(gi,gi);
		int lans=0;
		for(dfs(1);sb--;){
			int x,y,z,g,k;
			x=gi^lans;y=gi;k=gi;
			g=f[z=lca(x,y)][0];
			int t=PT.que(x,y,z,g,k);
			printf("%d",lans=a[t]);
			if(sb)puts("");
			//printf("%d+%d-%d-%d = a[%d] = %d\n",x,y,z,g,t,lans=a[t]);
		}
	}
	
}G;int n,q;
int main(){
	FO(qaq);
	n=gi;G.prep(n,q=gi);
	return 0;
}

