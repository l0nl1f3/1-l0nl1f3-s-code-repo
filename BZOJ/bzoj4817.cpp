//#include<bits/stdc++.h>
#include<cstdio>
#include<iostream>
#define ll long long
using namespace std;
int read(){
	int x=0;char ch;
	for(ch=getchar();!isdigit(ch);ch=getchar());
	for(;isdigit(ch);x=x*10+ch-'0',ch=getchar());
	return x;
} 
#define N 151234
#define M N+N 
#define L 20
int max(int a,int b){
	return a<b?b:a; 
}
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
//Seg Tree
int s[M*10],tag[M*10];
int pu(int x){s[x]=max(s[x+x],s[x+x+1]);}
int cov(int x,int l,int r,int v){s[x]+=v;tag[x]+=v;}
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
	//fprintf(stderr,"-%d %d %d %d\n",l,r,p,q);
	if(p<=l&&r<=q){cov(x,l,r,d);return;}
	if(tag[x])pd(x,l,r);
	modify(x+x,l,(l+r)/2,p,q,d);
	modify(x+x+1,(l+r)/2+1,r,p,q,d);
	pu(x);
}
int query(int x,int l,int r,int p,int q){
	if(p>r||q<l)return 0;
	//printf("%d %d %d %d\n",l,r,p,q);
	if(p<=l&&r<=q)return s[x];
	if(tag[x])pd(x,l,r);
	return max(query(x+x,l,(l+r)/2,p,q),query(x+x+1,(l+r)/2+1,r,p,q));
}
void modify(int w,ll v){if(!w)return;modify(1,1,n,lb[w],rb[w],v);}
int query(int x){return query(1,1,n,lb[x],rb[x]);}
int qit(int x){return query(1,1,n,lb[x],lb[x]);}
//END
//LCT
namespace LCT{
    int fa[N],ch[N][2],l[N],r[N];bool rev[N];
    inline bool is_root(int x){
		return !fa[x]||ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
	}
    inline void puu(int x){
        if (!x) return;
        l[x]=r[x]=x;
        if(ch[x][0]) l[x]=l[ch[x][0]];
        if(ch[x][1]) r[x]=r[ch[x][1]];
    }
    void reverse(int x){
		if(!x) return; 
		swap(l[x],r[x]),swap(ch[x][0],ch[x][1]);
		rev[x]^=1;
	}
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
		while(!is_root(x)){
            y=fa[x];
            if(!is_root(y))
				if(ch[fa[y]][0]==y^ch[y][0]==x)
					rot(x);
				else 
					rot(y);
            rot(x);
        }
        puu(x);
    }
    inline void access(int x){
		for(int y=0;x;y=x,x=fa[x])
			splay(x),
			modify(l[y],-1),
			modify(l[ch[x][1]],1),
			ch[x][1]=y,
			puu(x);
	}
    int init(){for(int i=1;i<=n;i++)fa[i]=g[i][0],l[i]=r[i]=i;}
}using namespace LCT;
//END
int lca(int x,int y){
	if(d[x]<d[y])swap(x,y);
	int i,k=d[x]-d[y];
	for(i=L-1;~i;i--)
		if(k&(1<<i))x=g[x][i];
	if(x==y)return x;
	for(i=L-1;~i;i--)
		if(g[x][i]!=g[y][i])
			x=g[x][i],y=g[y][i];
	return g[x][0];
}
int main(){
	freopen("paint.in","r",stdin);
	freopen("paint.out","w",stdout);
	int i;
	for(i=n=read(),q=read(),i--;i;i--)
		lnk(read(),read());
	dfs0(1);
	build(1,1,n);init();
	while(q--){
		int o,x,y;
		scanf("%d%d",&o,&x);
		if(o==1){
			access(x);
		}		
		if(o==2){
			scanf("%d",&y);
			printf("%d\n",qit(x)+qit(y)-2*qit(lca(x,y))+1);
			//printf("Hai Mei Xie Hao.jpg\n");
		}
		if(o==3){
			printf("%d\n",query(x));
		}
	}
	return 0;
}

