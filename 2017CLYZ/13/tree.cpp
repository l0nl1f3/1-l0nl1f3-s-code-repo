#include <map>
#include <stack>
#include <queue>
#include <cstdio>
#include <string>
#include <bitset>
#include <vector>
#include <cstring>
#include <complex>
#include <iostream>
#include <assert.h>
#include <algorithm>
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
#define mod 998244353
const int N=5000;
int fp(int x,int n){
	int res=1;for(;n;n>>=1,x=(ll)x*x%mod)if(n&1)res=(ll)res*x%mod;
	return res;
}
int n,k;ll f[N][N],a[N],ans,ny[N]; 
struct edge{int to,nxt;ll p;}e[N];int cnt,lst[N];
void ins(int a,int b,ll p){e[++cnt]=(edge){b,lst[a],p};lst[a]=cnt;} 
void lnk(int a,int b,ll p){ins(a,b,p);ins(b,a,p);}
struct ntt{
	ll w[2][N];
	int K;
	void fftinit(int n){
	    for(K=1;K<n;K<<=1);
	    w[0][0]=w[0][K]=1;
	    ll g=fp(3,(mod-1)/K);
	    for(int i=1;i<K;i++) w[0][i]=w[0][i-1]*g%mod;
	    for(int i=0;i<=K;i++) w[1][i]=w[0][K-i];
	}
	void fft(ll* x,int v){
	    for(int i=0,j=0;i<K;i++){
	        if(i>j) swap(x[i],x[j]);
	        for(int l=K>>1;(j^=l)<l;l>>=1);
	    }
	    for(int i=2;i<=K;i<<=1){
        for(int j=0;j<K;j+=i){
            for(int l=0;l<i>>1;l++){
                ll t=(ll)x[j+l+(i>>1)]*w[v][K/i*l]%mod;
                x[j+l+(i>>1)]=(x[j+l]-t>=0)?(x[j+l]-t):(x[j+l]-t+mod);
                x[j+l]=(x[j+l]+t<mod)?(x[j+l]+t):(x[j+l]+t-mod);
            }
        }
       }
	    if(!v) return;
	    ll rv=fp(K,mod-2);
	    for(int i=0;i<K;i++) x[i]=x[i]*rv%mod;
	}
	void mul(ll *a,ll* b){
		fft(a,0);fft(b,0);
		for(int i=0;i<K;i++)a[i]=a[i]*b[i]%mod;
		fft(a,1); 
		for(int i=k+1;i<K;i++)a[i]=0; 
	}
}ZY;
void dfs(int v,int fa){
	f[v][0]=1;
	for(int i=1;i<=k;i++)f[v][i]=f[v][i-1]*a[v]%mod*ny[i]%mod;
	for(int i=lst[v],b;b=e[i].to,i;i=e[i].nxt){
		if(b==fa)continue;
		dfs(b,v);
		for(int x=1;x<k;x++)f[b][x]=f[b][x]*e[i].p%mod;f[b][k]=0;
		ZY.mul(f[v],f[b]); 
	} 
	ans=(ans+f[v][k])%mod;
}
int main(){
	n=gi;k=gi;
	for(int i=1;i<=n;i++)a[i]=gi;
	for(int i=1;i<=k;i++)ny[i]=fp(i,mod-2);
	for(int i=1;i<n;i++){
		int a=gi,b=gi,c=gi,d=gi;
		lnk(a,b,c*(ll)fp(d,mod-2)%mod);
	}
	ZY.fftinit(k+k+1);
	dfs(1,0);
	for(int i=1;i<=k;i++)ans=(ans*i)%mod; 
	cout<<ans;
} 
