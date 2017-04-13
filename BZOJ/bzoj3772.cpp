#include<bits/stdc++.h>
#define ll long long
#define N 101234
#define M 202333
#define Z M*L 
#define L 19 
using namespace std;
vector<int>a[N];
pair<int,int>pt[N];
struct edge{int to,nxt;}e[M];
int n,m,cnt,dfn,d[N],lst[N],fs[N],os[N],g[N][L];ll fz,fm;
void ins(int a,int b){e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;}
void lnk(int a,int b){ins(a,b);ins(b,a);}
void dfs(int x){
	fs[x]=++dfn;
	for(int i=1;i<L;i++)g[x][i]=g[g[x][i-1]][i-1];
	for(int i=lst[x],b;b=e[i].to,i;i=e[i].nxt){
		if(b!=g[x][0]){
			g[b][0]=x;d[b]=d[x]+1;
			dfs(b);
		}
	}
	os[x]=++dfn;
}
int ls[Z],rs[Z],sh[Z],rot[N],o;
int edt(int x,int l,int r,int p,int d){
	int i=++o;
	ls[i]=ls[x];rs[i]=rs[x];
	if(l==r)sh[i]=sh[x]+d;else{
		if(p<=(l+r)/2)ls[i]=edt(ls[i],l,(l+r)/2,p,d);
		else rs[i]=edt(rs[i],(l+r)/2+1,r,p,d);
		sh[i]=sh[ls[i]]+sh[rs[i]];
	}return i;
}
int query(int a,int b,int c,int d,int l,int r,int s,int t){
	if(s>r||t<l)return 0;
	if(s<=l&&r<=t)return sh[a]+sh[b]-sh[c]-sh[d];
	return query(ls[a],ls[b],ls[c],ls[d],l,(l+r)/2,s,t)+
			query(rs[a],rs[b],rs[c],rs[d],(l+r)/2+1,r,s,t);
}
void build(int x){
	rot[x]=rot[g[x][0]];
	for(int i=0;i<a[x].size();i++){
		rot[x]=edt(rot[x],1,dfn,fs[a[x][i]],1);
		rot[x]=edt(rot[x],1,dfn,os[a[x][i]],-1);
	}
	for(int i=lst[x];i;i=e[i].nxt)
		if(e[i].to!=g[x][0])build(e[i].to);
}
int lca(int x,int y){
	if(d[x]<d[y])swap(x,y);
	int k=d[x]-d[y],i;
	for(i=0;i<L;i++)if(k&(1<<i))x=g[x][i];
	if(x==y)return x;
	for(i=L-1;~i;i--)if(g[x][i]!=g[y][i])x=g[x][i],y=g[y][i];
	return g[x][0];
}
int main(){
	int i,j,k,l;
	for(scanf("%d%d",&n,&m),i=1;i<n;i++){
		scanf("%d%d",&j,&k);lnk(j,k);
	}
	for(i=1;i<=m;i++){
		scanf("%d%d",&j,&k);
		a[j].push_back(k);
		pt[i]=make_pair(j,k);
	}
	sort(pt+1,pt+m+1);
	dfs(1);
	build(1);
	for(i=1;i<=m;i++){
		j=pt[i].first;k=pt[i].second;l=lca(j,k);
		fz+=query(rot[j],rot[k],rot[l],rot[g[l][0]],1,dfn,fs[l],fs[j]);
		fz+=query(rot[j],rot[k],rot[l],rot[g[l][0]],1,dfn,fs[l],fs[k]);
		fz-=query(rot[j],rot[k],rot[l],rot[g[l][0]],1,dfn,fs[l],fs[l]);
		fz--;
	} 
	for(i=1;i<=m;i=j)
		for(j=i;pt[j].first==pt[i].first&&pt[j].second==pt[i].second;j++)
			fz-=(ll)(j-i)*(j-i-1)/2;
	fm=(ll)m*(m-1)/2;
	printf("%lld/%lld",fz/__gcd(fz,fm),fm/__gcd(fz,fm));
}

