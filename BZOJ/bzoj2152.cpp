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
#define N 41234
#define M 101234
struct edge{int to,nxt,v;};
struct graph{
	edge e[M];int n,m,lst[N],cnt;
	void resize(int a,int b){n=a;m=b;cnt=0;memset(lst,0,sizeof(lst));}
	graph(){cnt=0;}
	graph(int n,int m):n(n),m(m){}
	edge operator[](int a){return e[a];};
	void ins(int a,int b,int c){e[++cnt]=(edge){b,lst[a],c};lst[a]=cnt;}
	void lnk(int a,int b,int c){ins(a,b,c);ins(b,a,c);}
};
int n;
struct Dfz{
	graph G;
	int n,k,rt,siz[N],son[N],d[N],b[N],v[N];
	void resize(int QAQ){n=QAQ;}
	void dfs(int x,int fa=0){
		++b[d[x]];
		for(int y,i=G.lst[x];i;i=G[i].nxt){
			if((y=G[i].to)!=fa&&!v[y]){
				d[y]=(d[x]+G[i].v)%3;dfs(y,x);
			}
		}
	} 
	void groot(int x,int fa=0){
		son[x]=(siz[x]=1)-1;
		for(int y,i=G.lst[x];i;i=G[i].nxt){
			if((y=G[i].to)!=fa&&!v[y]){
				groot(y,x);
				siz[x]+=siz[y];
				gmax(son[x],siz[y]);
			}
		}
		son[x]=max(son[x],n-siz[x]);
		if(son[x]<son[rt])rt=x;
	}
	int cal(int x,int D=0){
		b[1]=b[2]=b[0]=0;d[x]=D;
		dfs(x);
		return b[1]*b[2]*2+b[0]*b[0]; 
	}
	int ans;
	int main(int x){
		ans+=cal(x);v[x]=1;
		for(int y,i=G.lst[x];i;i=G[i].nxt){
			if(!v[y=G[i].to]){
				ans-=cal(y,G[i].v);
				n=siz[y];rt=0;
				groot(y);main(rt);
			}
		} 
	}
	int main(){
		son[ans=0]=inf;
		groot(1);main(1);
		n=::n;
		int gcd=__gcd(ans,n*n);
		return printf("%d/%d",ans/gcd,n*n/gcd),0;
	}
}D;
int main(){
	FO(qaq);
	n=gi;
	for(int i=1,u,v,w;i<n;i++)u=gi,v=gi,w=gi%3,D.G.lnk(u,v,w);
	D.resize(n);D.main();
	return 0;
}

