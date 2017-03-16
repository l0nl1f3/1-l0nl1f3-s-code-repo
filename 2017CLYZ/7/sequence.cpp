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
#define N 160
int T,n,rk[N],a[N],v[N],e[N];
int h[N],nxt[N][N],f[N][N][N],g[N][N][N],b[N][N][N];
void dp(int i,int j,int k){
	if(b[i][j][k]||j<i||j+k>n)return;
	b[i][j][k]=1;dp(i,j-1,0);
	int &x=f[i][j][k],&y=g[i][j][k];
	x=y=f[i][j-1][0]+v[k+1];
	if(e[rk[j]]-e[rk[j]-1]==1){
		int d=rk[j]-1;
		for(int p=nxt[d][j];p>=i;p=nxt[d][p]){
			dp(i,p,k+1);dp(p+1,j-1,0);
			gmax(x,g[i][p][k+1]+f[p+1][j-1][0]);
			gmax(y,g[i][p][k+1]+f[p+1][j-1][0]);
		}
	}
	if(e[rk[j]+1]-e[rk[j]]==1){
		int d=rk[j]+1;
		for(int p=nxt[d][j];p>=i;p=nxt[d][p]){
			dp(i,p,k+1);dp(p+1,j-1,0);
			gmax(x,f[i][p][k+1]+f[p+1][j-1][0]);
			gmax(x,g[i][p][k+1]+f[p+1][j-1][0]);
		}
	}
}
int main(){
	n=gi;
	for(int i=1;i<=n;i++)v[i]=gi;
	for(int i=1;i<=n;i++)a[i]=e[i]=gi;
	sort(e+1,e+n+1);
	int s=unique(e+1,e+n+1)-e-1;
	e[0]=-inf;e[s+1]=inf;
	for(int i=1;i<=n;i++){
		rk[i]=lower_bound(e+1,e+s+1,a[i])-e;
		nxt[rk[i]][i+1]=i;for(int j=1;j<=s;j++)if(j!=rk[i-1])nxt[j][i]=nxt[j][i-1];	
	}
	for(int i=1;i<=n;i++)for(int j=i;j<=n;j++)for(int k=0;k<=n;k++)dp(i,j,k);
	for(int i=1;i<=n;i++){
		h[i]=h[i-1];
		for(int j=i;j;j--)gmax(h[i],h[j-1]+f[j][i][0]);
	}
	cout<<h[n];
	return 0;
}

