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
#define N 301234
#define M 1001234
int n,q,ty,cnt,lastans,d[N],lst[N];
struct edge{int to,nxt;}e[M];
void ins(int a,int b){e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;}
void lnk(int a,int b){ins(a,b),ins(b,a);}
void dfs0(int x,int f=0){
	for(int i=lst[x],b;b=e[i].to,i;i=e[i].nxt){
		if(b!=f)d[b]=d[x]+1,dfs0(b,x);
	}
}
namespace sol{
	struct node{
		node *ch[2],*f;int s;bool rev;
		node(){}node(node *l,node *r,node *f):ch{l,r},f(f),s(0){}
		void push(){
			if(rev){
				ch[0]->rev^=1;ch[1]->rev^=1;
				swap(ch[0],ch[1]);
				rev^=1;
			}
		}
		inline void pushup(){s=ch[0]->s+ch[1]->s+1;}
		inline bool nroot(){return f->ch[0]==this||f->ch[1]==this;}
	}*nil=new node(0,0,0); 
	void rot(node *x){
		x->push();node *y=x->f;
		int d= x==y->ch[0];
        (y->ch[d^1]=x->ch[d])->f=y;
        if (x->f=y->f,y->nroot()) y->f->ch[y->f->ch[1]==y]=x;
		y->f=x;
        (x->ch[d]=y)->pushup();
	} 
	void splay(node *x){
		for(x->push();x->nroot();rot(x)){
			node *y=x->f,*z=y->f;
			if(y->nroot())z->push();
			y->push();
			if(y->nroot())rot((x==y->ch[1])^(y==z->ch[1])?x:y);
		}
        x->pushup();
    }
	inline void access(node *x){for(node *y=nil;x!=nil;(y=x)->pushup(),x=x->f)splay(x),x->ch[1]=y;}
	inline void evert(node *x){access(x);splay(x);x->rev^=1;x->push();}
	inline void lnk(node *x,node *y){evert(x);x->f=y;}
	node z[N];
	int f[N];pair<int,Pii>dia[N];
	void init(){for(int i=1;i<=n;i++)f[i]=i,dia[i]=mp(0,mp(i,i));}
	inline int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
	int dis(int u, int v) {evert(z+u);access(z+v);splay(z+v);return z[v].s;}
	Pii query(int u) {
	    int fu=find(u);
	    return max(mp(dis(u,dia[fu].se.fi),dia[fu].se.fi),mp(dis(u,dia[fu].se.se),dia[fu].se.se));
	}
	void link(int u, int v) {
		node *x=z+u,*y=z+v;
	    int fu=find(u),fv=find(v);
	    Pii a=query(u),b=query(v);
		lnk(x,y);
	    dia[fu]=max(mp(a.fi+b.fi,mp(a.se,b.se)),max(dia[fu],dia[fv]));
	    f[fv]=fu;
	}
	int main(){
		init();
		for(int i=1;i<=n;i++)z[i]=node(nil,nil,nil);
		for(int i=1,o,x,y;i<=q;i++){
			o=gi;if(o==1){
				x=gi^lastans;y=gi^lastans;link(x,y);
			}else{
				x=gi^lastans;printf("%d\n",lastans=query(x).fi-1);
				if(!ty)lastans=0;
			}
		}
	}
}
int main(){
	FO(hike);
	ty=gi;n=gi;q=gi;
	sol::main();
	return 0;
}

