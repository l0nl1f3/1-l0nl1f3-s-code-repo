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
#define M 55
#define N 302
ll f[N][N];int t[N][N],n,m,p;  
int dp(){
	for(int i=0;i<=m;i++)f[0][i]=f[i][0]=f[m+1][i]=f[i][m+1]=infll;
	for(int i=1;i<=n;i++){
       	for(int j=1;j<=m;j++)for(int k=1;k<=m;k++)f[j][k]=f[j][k]+t[i][j]+t[i][k];
       	for(int j=1;j<=m;j++)f[j][j]=infll;
       	for(int j=1;j<=m;j++)for(int k=1;k<=m;k++)gmin(f[j][k],min(f[j-1][k]+p,f[j][k-1]+p));
       	for(int j=m;j;j--)	 for(int k=m;k;k--)	  gmin(f[j][k],min(f[j+1][k]+p,f[j][k+1]+p));
    }
    ll ans=infll;
    for(int i=1;i<=m;i++)for(int j=1;j<=m;j++)gmin(ans,f[i][j]);
    printf("%lld\n",ans);
}
int main(){
	FO(room);
	n=gi;m=gi;p=gi;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)t[i][j]=gi;
	dp();
	return 0;
}

