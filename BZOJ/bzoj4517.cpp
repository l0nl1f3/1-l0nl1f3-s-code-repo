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
#define N 1001234
#define mod 1000000007
int fac[N],ny[N],f[N];
int Fp(int a,int n){
	int res=1;
	for(;n;n>>=1,a=(ll)a*a%mod)if(n&1)res=(ll)res*a%mod;
	return res;
}
int c(int n,int m){return (ll)fac[n]*ny[m]%mod*ny[n-m]%mod;}
int main(){
	FO(qaq);
	int T=gi;
	f[2]=f[0]=1;
	for(int i=3;i<N;i++)f[i]=(ll)(f[i-1]+f[i-2])*(i-1)%mod;
	for(int i=fac[0]=1;i<N;i++)fac[i]=(ll)fac[i-1]*i%mod;
	ny[N-1]=Fp(fac[N-1],mod-2);
	for(int i=N-1;i;i--)ny[i-1]=(ll)ny[i]*i%mod;
	while(T--){
		int n=gi,m=gi;
		if(m>n)puts("0");
		else printf("%d\n",(ll)f[n-m]*c(n,m)%mod);
	}
	return 0;
}

