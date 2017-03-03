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
#define N 151234
#define M N+N 
#define L 20
struct edge{int to,nxt;};
edge e[M];int n,q,cnt,ans[N],lst[N],siz[N],cr[N],d[N];
void ins(int a,int b){e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;}
void lnk(int a,int b){ins(a,b);ins(b,a);}
int dfn[N],pos[N],lb[N],rb[N],g[N][L],nfd;
void dfs0(int x,int f=0){
	siz[x]=1;d[x]=d[f]+1;
	pos[++nfd]=x;dfn[x]=lb[x]=nfd;
	g[x][0]=f;for(int i=1;i<L;i++)g[x][i]=g[g[x][i-1]][i-1];
	for(int i=lst[x],b;i;i=e[i].nxt){
		if((b=e[i].to)==f)continue;
		dfs0(b,x);
		siz[x]+=siz[b];
	}
	rb[x]=nfd;
} 
ll s[M*10],tag[M*10];
int pu(int x){s[x]=s[x+x]+s[x+x+1];}
int cov(int x,int l,int r,int v){s[x]+=(r-l+1)*v;tag[x]+=v;}
int pd(int x,int l,int r){
	cov(x+x,l,(l+r)/2,tag[x]);
	cov(x+x+1,(l+r)/2+1,r,tag[x]);
	tag[x]=0;
} 
void build(int x,int l,int r){
	if(l==r)s[x]=d[pos[l]];
	else{
		build(x+x,l,(l+r)/2);
		build(x+x+1,(l+r)/2+1,r);
		pu(x);
	}
}
void modify(int x,int l,int r,int p,int q,int d){
	if(p>r||q<l)return;
	if(p<=l&&r<=q){cov(x,l,r,d);return;}
	if(tag[x])pd(x,l,r);
	modify(x+x,l,(l+r)/2,p,q,d);
	modify(x+x+1,(l+r)/2+1,r,p,q,d);
	pu(x);
}
ll query(int x,int l,int r,int p,int q){
	if(p>r||q<l)return 0;
	if(p<=l&&r<=q)return s[x];
	if(tag[x])pd(x,l,r);
	return query(x+x,l,(l+r)/2,p,q)+query(x+x+1,(l+r)/2+1,r,p,q);
}
void modify(int w,ll v){if(!w)return;modify(1,1,n,lb[w],rb[w],v);}
ll query(int x){return query(1,1,n,lb[x],rb[x]);}
namespace LCT{
    int fa[N],ch[N][2],l[N],r[N];bool rev[N];
    inline bool is_root(int x) {return !fa[x]||ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
    inline void puu(int x){
        if (!x) return;
        l[x]=r[x]=x;
        if(ch[x][0]) l[x]=l[ch[x][0]];
        if(ch[x][1]) r[x]=r[ch[x][1]];
    }
    void reverse(int x) {if(!x) return; swap(l[x],r[x]),swap(ch[x][0],ch[x][1]),rev[x]^=1;}
    void pud(int x) {if(!x) return; if(rev[x]) reverse(ch[x][0]),reverse(ch[x][1]),rev[x]^=1;}
    void rot(int x){
        int y=fa[x],w=ch[y][1]==x,z=fa[y];
        ch[y][w]=ch[x][w^1];
        if(ch[x][w^1])fa[ch[x][w^1]]=y;
        if(ch[z][0]==y)ch[z][0]=x;else if(ch[z][1]==y)ch[z][1]=x;
        fa[x]=z;fa[y]=x;ch[x][w^1]=y;puu(y);
    }
    int stack[N];
    inline void splay(int x){
        int t=x,top=0,y; 
		stack[++top]=x;
        while(!is_root(t)) stack[++top]=t=fa[t];
        while(top)pud(stack[top--]);
		while(!is_root(x)){
            y=fa[x];
            if(!is_root(y))if((ch[fa[y]][0]==y)^(ch[y][0]==x))rot(x);else rot(y);
            rot(x);
        }
        puu(x);
    }
    inline void access(int x){for(int y=0;x;y=x,x=fa[x])splay(x),modify(l[y],-1),modify(l[ch[x][1]],1),ch[x][1]=y,puu(x);}
    int init(){for(int i=1;i<=n;i++)fa[i]=g[i][0],l[i]=r[i]=i;}
}using namespace LCT;
int main(){
	FO(color);
	for(int i=(n=gi)-1;i;i--)lnk(gi+1,gi+1);
	dfs0(1);q=gi;
	build(1,1,n);init();
	while(q--){
		char c[3];int x;
		scanf("%s",c);x=gi+1;
		if(c[0]=='q')printf("%.10lf\n",1.0*(query(x)-siz[x])/siz[x]);
		else access(x);
	}
	return 0;
}

