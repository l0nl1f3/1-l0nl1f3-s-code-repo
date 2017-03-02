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
#define N 101234
#define M 201234
#define S 30001234
struct Edge{int to,nxt;};
struct HLD{
	Edge e[M];int C,lst[N];
	int d[N],fa[N],an[N],son[N],siz[N],dfn[N],nfd;
	int n,q,w[N],c[N];
	int ls[S],rs[S],s[S],m[S],rt[N],D;
	void ins(int a,int b){e[++C]=(Edge){b,lst[a]};lst[a]=C;}
	void lnk(int a,int b){ins(a,b);ins(b,a);}
	void dfs1(int x,int f=0){
		siz[x]=1;fa[x]=f;
		for(int b,i=lst[x];i;i=e[i].nxt)
			if((b=e[i].to)!=f){
				d[b]=d[x]+1;dfs1(b,x);
				siz[x]+=siz[b];
				if(siz[b]>siz[son[x]])son[x]=b;
			}
	}
	void dfs2(int x,int t=1){
		dfn[x]=++nfd;an[x]=t;
		if(son[x])dfs2(son[x],t);
		for(int b,i=lst[x];i;i=e[i].nxt)
			if((b=e[i].to)!=fa[x]&&b!=son[x])dfs2(b,b);
	}
	void prep(){dfs1(1);dfs2(1);}
	int sum(int k,int l,int r,int a,int b){
		if(r<a||l>b)return 0;
		if(a<=l&&r<=b)return s[k];
		return sum(ls[k],l,(l+r)/2,a,b)+sum(rs[k],(l+r)/2+1,r,a,b);
	}
	int Max(int x,int y){return x>y?x:y;}
	int max(int k,int l,int r,int a,int b){
		if(r<a||l>b)return 0;
		if(a<=l&&r<=b)return m[k];
		return Max(max(ls[k],l,(l+r)/2,a,b),max(rs[k],(l+r)/2+1,r,a,b));
	}
	void add(int &k,int l,int r,int p,int d){
		if(!k)k=++D;
		if(l==r)s[k]=m[k]=d;
		else{
			p<=(l+r)/2?add(ls[k],l,(l+r)/2,p,d):add(rs[k],(l+r)/2+1,r,p,d);
			s[k]=s[ls[k]]+s[rs[k]];
			m[k]=Max(m[ls[k]],m[rs[k]]);
		}
	}
	int QS(int x,int y,int c){
		int ans=0;
		for(;an[x]!=an[y];x=fa[an[x]]){
			if(d[an[x]]<d[an[y]])swap(x,y);
			ans+=sum(rt[c],1,n,dfn[an[x]],dfn[x]);
		}
		if(d[x]>d[y])swap(x,y);
		return ans+sum(rt[c],1,n,dfn[x],dfn[y]);
	}
	int QM(int x,int y,int c){
		int ans=0;
		for(;an[x]!=an[y];x=fa[an[x]]){
			if(d[an[x]]<d[an[y]])swap(x,y);
			ans=Max(ans,max(rt[c],1,n,dfn[an[x]],dfn[x]));
		}
		if(d[x]>d[y])swap(x,y);
		return Max(ans,max(rt[c],1,n,dfn[x],dfn[y]));
	}
	
	int main(){
		n=gi;q=gi;
		for(int i=1;w[i]=gi,c[i]=gi,i<n;i++);
		for(int i=1;i<n;i++)lnk(gi,gi);
		prep();
		for(int i=1;i<=n;i++)add(rt[c[i]],1,n,dfn[i],w[i]); 
		while(q--){char op[5];int x,y,z;
			scanf("%s",op);x=gi;y=gi;z=dfn[x];
			if(op[0]=='C')
				if(op[1]=='C'){
					add(rt[c[x]],1,n,z,0);
					add(rt[c[x]=y],1,n,z,w[x]);
				}else if(op[1]=='W') add(rt[c[x]],1,n,z,w[x]=y);
			if(op[0]=='Q')
				if(op[1]=='S')printf("%d\n",QS(x,y,c[x]));
				else if(op[1]=='M')printf("%d\n",QM(x,y,c[x]));
		}
		return 0;
	}	
}H;
int main(){
	H.main();
	return 0;
}

