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
#define p 1004535809
#define N 123 
ll pw(ll a,ll n){
	if(n<0)return 1;
	ll res=1;
	for(;n;n>>=1,a=(a*a)%p)if(n&1)(res*=a)%=p;
	return res;
} 
ll c[N][N],a[N],f[N][N][N];int n;
int main(){
	FO(tree);
	n=gi;
	for(int i=1;i<=n;i++)a[i]=gi;
	for(int i=0;i<=n;i++)for(int j=c[i][0]=1;j<=i;j++)c[i][j]=(c[i-1][j]+c[i-1][j-1])%p;
	f[0][0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<=n;k++){
				f[i][j][k]=f[i-1][j][k];
				if(j)for(int l=0;l<=k&&l<a[i];l++)	(f[i][j][k]+=f[i-1][j-1][k-l]*c[k][l])%=p;
			}	
		}
	}
	printf("%d ",n);
	for(int s=2;s<=n;s++)printf("%I64d ",f[n][s][s-2]%p);
	return 0;
}

