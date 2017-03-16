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
#define S 1001234 
#define N 4001234
#define M 12001234
string s;vector<int>g[S];
struct edge{int to,nxt;}e[M];
int n,scc,cnt,lst[N],bel[N],low[N],dfn[N],st[N],in[N],sn,ind;
void ins(int a,int b){e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;}
void dfs(int v){
    dfn[v]=low[v]=++ind;in[st[++sn]=v]=1;
    for(int i=lst[v],b;b=e[i].to,i;i=e[i].nxt){
        if(!dfn[b])dfs(b),gmin(low[v],low[b]);
        else if(in[b])gmin(low[v],dfn[b]);
    }
    if(dfn[v]==low[v]){
        int x=-1;++scc;
        while(sn&&v!=x){
            in[x=st[sn--]]=0;
            bel[x]=scc;
        }
    }
} 
int ch[S][2],fa[S],tot; 
int insert(string s,int p=0){
	for(int i=0,q;i<s.length();i++){
		if(!ch[p][q=s[i]-'0']){
			ch[p][q]=++tot;fa[tot]=p;
		}
		p=ch[p][q];
	}
	return p;
}
int main(){
	FO(code);
	n=gi;for(int i=1,p;i<=n;i++){
		cin>>s;p=-1;
		for(int i=0;i<s.length();i++)if(s[i]=='?')p=i,i=s.length();
		if(~p)s[p]='0';g[insert(s)].pb(2*i-2);
		if(~p)s[p]='1';g[insert(s)].pb(2*i-1);
	}
	for(int i=1;i<=tot;i++)ins(fa[i]+2*n,i+2*n),ins(i+tot+2*n+1,fa[i]+2*n+tot+1);
	int id=2*(n+tot)+1;
	for(int i=1;i<=tot;i++){
		for(int j=0;j<g[i].size();j++){
        	ins(g[i][j],i+2*n);
        	ins(fa[i]+2*n,g[i][j]^1);
          	ins(g[i][j],fa[i]+2*n+tot+1);
          	ins(i+2*n+tot+1,g[i][j]^1);
		}
		for(int j=0;j<g[i].size();j++){
			ins(g[i][j],++id);
			if(j)ins(id-1,id),ins(id-1,g[i][j]^1);
		}
		for(int j=0;j<g[i].size();j++){
			ins(++id,g[i][j]^1);
			if(j)ins(id,id-1),ins(g[i][j],id-1);
		}
	}
	for(int i=0;i<=id;i++)if(!dfn[i])dfs(i);
	for(int i=1;i<=n;i++)if(bel[2*i-1]==bel[2*i-2]){puts("NO");exit(0);}
	puts("YES");return 0;
}

