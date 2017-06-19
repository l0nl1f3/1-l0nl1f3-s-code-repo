#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){	return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){	return a<b?a=b,1:0;}
const int N=100010,M=600010;
char a[N],b[N],p[N];
int n,m,len,i,j,x,y,z,g[N],v[N<<1],w[N<<1],nxt[N<<1],ed,G[N],V[N<<2],W[N<<2],NXT[N<<2];
int size[N],son[N],f[N],fs[N],d[N],top[N],loc[N],seq[N],dfn,ans[N];
inline void add(int x,int y){v[++ed]=y;nxt[ed]=g[x];g[x]=ed;}
inline void ADD(int x,int y,int z){V[++ed]=y;W[ed]=z;NXT[ed]=G[x];G[x]=ed;}
void dfs(int x){
  size[x]=1;
  for(int i=g[x];i;i=nxt[i])if(v[i]!=f[x]){
    f[v[i]]=x,d[v[i]]=d[x]+1;
    dfs(v[i]),size[x]+=size[v[i]];
    if(size[v[i]]>size[son[x]])son[x]=v[i];
  }
}
void dfs2(int x,int y){
  seq[loc[x]=++dfn]=x;top[x]=y;
  if(son[x])dfs2(son[x],y);
  for(int i=g[x];i;i=nxt[i])if(v[i]!=son[x]&&v[i]!=f[x])dfs2(v[i],v[i]);
}
inline int lca(int x,int y){
  for(;top[x]!=top[y];x=f[top[x]])if(d[top[x]]<d[top[y]])swap(x,y);
  return d[x]<d[y]?x:y;
}
inline int kth(int x,int y){
  while(d[x]-d[top[x]]<y)y-=d[x]-d[top[x]]+1,x=f[top[x]];
  return seq[loc[x]-y];
}
namespace KMP{
int nxt[M];
inline void cross(int x,int y,int&ret){
  int t=0,i,j,A=kth(x,d[x]-min(d[z]+len-1,d[x])),B=kth(y,d[y]-min(d[z]+len-1,d[y]));
  for(nxt[0]=j=-1,i=1;i<len;nxt[i++]=j){
    while(~j&&a[j+1]!=a[i])j=nxt[j];
    if(a[j+1]==a[i])j++;
  }
  for(j=-1;A!=z;A=f[A]){
    while(~j&&a[j+1]!=fs[A])j=nxt[j];
    if(a[j+1]==fs[A])j++;
    if(j==len-1)ret++,j=nxt[j];
  }
  while(B!=z)b[++t]=fs[B],B=f[B];
  b[++t]=fs[z];
  while(t){
    while(~j&&a[j+1]!=b[t])j=nxt[j];
    if(a[j+1]==b[t])j++;
    if(j==len-1)ret++,j=nxt[j];
    t--;
  }
}
}
namespace AC{
int tot,son[M][26],f[M],q[M],g[M],nxt[M],st[M],en[M],dfn,bit[M];
inline void addedge(int x,int y){nxt[y]=g[x];g[x]=y;}
inline int ins0(){
  int x=0;
  for(int i=0;i<len;i++){
    if(!son[x][a[i]])son[x][a[i]]=++tot;
    x=son[x][a[i]];
  }
  return x;
}
inline int ins1(){
  int x=0;
  for(int i=len-1;~i;i--){
    if(!son[x][a[i]])son[x][a[i]]=++tot;
    x=son[x][a[i]];
  }
  return x;
}
void dfs(int x){
  st[x]=++dfn;
  for(int i=g[x];i;i=nxt[i])dfs(i);
  en[x]=dfn;
}
inline void add(int x,int p){for(x=st[x];x<=dfn;x+=x&-x)bit[x]+=p;}
inline int sum(int x){int t=0;for(;x;x-=x&-x)t+=bit[x];return t;}
inline int ask(int x){return sum(en[x])-sum(st[x]-1);}
void make(){
  int h=1,t=0,i,j,x;f[0]=-1;
  for(i=0;i<26;i++)if(son[0][i])q[++t]=son[0][i];
  while(h<=t)for(x=q[h++],i=0;i<26;i++)
    if(son[x][i])f[son[x][i]]=son[f[x]][i],q[++t]=son[x][i];
    else son[x][i]=son[f[x]][i];
  for(i=1;i<=tot;i++)addedge(f[i],i);
  dfs(0);
}
}
void dfs3(int x,int y){
  AC::add(y,1);
  for(int i=G[x];i;i=NXT[i]){
    int o=W[i];
    if(o>0)ans[o]+=AC::ask(V[i]);else ans[-o]-=AC::ask(V[i]);
  }
  for(int i=g[x];i;i=nxt[i])if(v[i]!=f[x])dfs3(v[i],AC::son[y][fs[v[i]]]);
  AC::add(y,-1);
}
int main(){
  scanf("%d%d",&n,&m);
  scanf("%s",a);
  scanf("%s",p);
  for(i=1;i<=n;i++)fs[i]=a[i-1]-'a'; 
  for(i=1;i<n;i++)scanf("%d%d",&x,&y),add(x,y),add(y,x);
  dfs(1),dfs2(1,1);
  for(ed=0,i=1;i<=m;i++){
    scanf("%d%d",&x,&y);
	strcpy(a,p);
	len=strlen(p);z=lca(x,y);
	for(j=0;j<len;j++)a[j]-='a';
    KMP::cross(x,y,ans[i]);
    if(d[x]-d[z]>=len){
      j=AC::ins1();
      ADD(x,j,i);
      ADD(kth(x,d[x]-d[z]-len+1),j,-i);
    }
    if(d[y]-d[z]>=len){
      j=AC::ins0();
      ADD(y,j,i);
      ADD(kth(y,d[y]-d[z]-len+1),j,-i);
    }
  }
  AC::make();
  dfs3(1,0);
  for(i=1;i<=m;i++)printf("%d\n",ans[i]);
  return 0;
}
