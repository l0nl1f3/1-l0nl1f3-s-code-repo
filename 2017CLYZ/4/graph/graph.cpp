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
#define M 12345 
int n,m,c,S,f[M],g[M];
struct edge{int u,v,w;}e[M];
bool cmp(edge a,edge b){return a.w<b.w;}
int gC(int x,int y=0){for(;x;x-=x&-x)y++;return y;}
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
int chk(int x){
	for(int i=1;i<=n;i++)f[i]=i;
	int cnt=n;
	for(int i=1;i<=m;i++){
		if(x>>(e[i].w-1)&1){
			//cout<<e[i].u<<","<<e[i].v<<endl;
			int fx=find(e[i].u),fy=find(e[i].v); 
			if(fx!=fy)cnt--,f[fx]=fy;
			//else printf("%d\n",i);
		}
	}
	//cerr<<cnt;
	return cnt==1;
}
vector<Pii>v;
void getS(int x){
	for(int i=1;i<=m;i++){
		if(x>>(e[i].w-1)&1){
			v.pb(mp(e[i].u,i));
		}
	}
	printf("%d\n",v.size());
	for(int i=0;i<v.size();i++)printf("%d\n",v[i].se);
	return;
}
int main(){
	FO(graph4);
	n=gi;m=gi;
	for(int i=1;i<=m;i++)e[i].u=gi,e[i].v=gi,e[i].w=gi,gmax(c,e[i].w);
	int ans=(1<<c)-1;
	for(S=0;S<(1<<c);S++){
		if(chk(S)){
			//cout<<gC(S)<<","<<gC(ans)<<endl;
			
			if(gC(S)<gC(ans))ans=S;
		}
	}
	getS(ans);
		
	return 0;
}

