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
#define N 501
#define M 251234
int n,m,ans,g[N][N],f[N][N],p[N];
Pii l[M],r[M];
struct edge{int to,nxt;};
struct graph{
	edge e[M];int lst[N],C,v[M],mt[N];
	void ins(int a,int b){e[++C]=(edge){b,lst[a]};lst[a]=C;}
	int mth(int u){
		v[u]=1;
		for(int b,i=lst[u];i;i=e[i].nxt){
			if(mt[b=e[i].to]==-1){
				mt[b]=u;
				return 1;
			}
		}
		for(int b,i=lst[u];i;i=e[i].nxt){
			if(!v[mt[b=e[i].to]]&&mth(mt[b])){
				mt[b]=u;
				return 1;
			}
		}
		return 0;
	}
	int QAQ(){
		ans=m;
		for(int i=1;i<=m;i++){
			mt[i]=-1;
			for(int j=1;j<=m;j++){
				if(i!=j&&r[i].se+g[r[i].fi][l[j].fi]<=l[j].se){
					ins(i,j);
				}
			}
		}
		for(int i=1;i<=m;i++){
			memset(v,0,sizeof(v));
			ans-=mth(i);
		}
		return printf("%d\n",ans),0;
	}
}G;
int main(){
	FO(flight); 
	n=gi;m=gi;
	for(int i=1;i<=n;i++)p[i]=gi;
	for(int i=1,a,b;i<=n;i++){
		for(int j=1;j<=n;j++){
			a=gi;
			g[i][j]=f[i][j]=a+(i!=j)*p[j];
		}
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				gmin(g[i][j],g[i][k]+g[k][j]);
		}
	for(int i=1,s,t,d;i<=m;i++){
		s=gi;t=gi;d=gi;
		l[i]=mp(s,d);
		r[i]=mp(t,d+f[s][t]); 
	}
	G.QAQ();
	return 0;
}

