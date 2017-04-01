#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define p 998244353
#define N 888888
ll w[2][N];int K;
int fpow(int a,int n){
	int res=1;
	for(;n;n>>=1,a=(ll)a*a%p)
		if(n&1)res=(ll)res*a%p;
	return res;
}
void fftinit(int n){
    for(K=1;K<n;K<<=1);
    w[0][0]=w[0][K]=1;
    ll g=fpow(3,(p-1)/K);
    for(int i=1;i<K;i++) w[0][i]=w[0][i-1]*g%p;
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
            ll t=(ll)x[j+l+(i>>1)]*w[v][K/i*l]%p;
            x[j+l+(i>>1)]=(x[j+l]-t>=0)?(x[j+l]-t):(x[j+l]-t+p);
            x[j+l]=(x[j+l]+t<p)?(x[j+l]+t):(x[j+l]+t-p);
        }
    }
   }
    if(!v) return;
    ll rv=fpow(K,p-2);
    for(int i=0;i<K;i++) x[i]=x[i]*rv%p;
}
ll f[N],g[N],t[N];
void inverse(int n){
	if(n==1){f[0]=fpow(g[0],p-2);return;}
	inverse(n/2);int L=n*2;
	fftinit(L);
	for(int i=0;i<n;i++)t[i]=g[i];
	fft(t,0);fft(f,0);
	for(int i=0;i<L;i++)f[i]=f[i]*(2-f[i]*t[i]%p+p)%p;
	fft(f,1);
	for(int i=n;i<K;i++)f[i]=0;
}
ll iv[N],ans;int n;
int main(){
	int i,j,k;
	for(scanf("%d",&n),i=j=1;i<=n;j=(ll)j*i++%p);
	for(k=1;k<=n;k<<=1);
	for(iv[i=n]=fpow(j,p-2);i;i--)iv[i-1]=(ll)iv[i]*i%p;
	for(g[0]=i=1;i<=n;i++)g[i]=(p-iv[i])*2%p;
	inverse(k);
	for(ans=f[i=n];i;i--)ans=(ans*i+f[i-1])%p;
	return printf("%lld",ans),0;
}
