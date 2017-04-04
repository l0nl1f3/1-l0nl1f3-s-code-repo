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
ll f[N],iv[N],a[N],b[N];
int main(){
	int i,k,n;ll j;
	for(scanf("%d",&n),k=1;k<=(n+1);k*=2);
	for(f[0]=i=1;i<=n;i++)f[i]=f[i-1]*i%p;
	for(iv[i=n]=fpow(f[n],p-2);i;i--)iv[i-1]=iv[i]*i%p;
	for(i=0;i<=n;i++)a[i]=(i&1?p-iv[i]:iv[i]);
	for(b[i=1]=n,i++;i<=n;i++)b[i]=(ll)((fpow(i,n+1)-i)%p+p)%p*fpow(i-1,p-2)%p*iv[i]%p;
	fftinit(k*2);fft(a,0);fft(b,0);k=1;
	for(i=0;i<K;i++)a[i]=a[i]*b[i]%p;
	for(fft(a,j=i=k++);i<=n;i++,k=(k+k)%p)j=(j+(ll)a[i]*k%p*f[i]%p)%p;
	return printf("%lld",j),0;
} 
