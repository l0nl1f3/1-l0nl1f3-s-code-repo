#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct RS{
	#define N 3201234
	int p,q,mod,ph,f[N],g[N];
	int exp(int a,ll n){
		int res=1;
		for(;n;n>>=1,a=(ll)a*a%mod)
			if(n&1)res=(ll)res*a%mod;
		return res;
	}
	ll cnt(ll a){
		ll res=0;
		while(a)res+=a/=p;
		return res;
	}
	int inv(int a){return exp(a,ph-1);}
	ll chk(int a){return a%p?a:1;}
	void build(){
		for(int i=f[0]=1;i<mod;i++)f[i]=f[i-1]*chk(i)%mod;
		for(int i=g[0]=1;i<ph*2;i++)g[i]=(ll)f[mod-1]*g[i-1]%mod;
	}
	int tp(ll n){return n<=ph?g[n]:g[ph+n%ph];}
	int dfac(ll n){return n<p?f[n]:(ll)f[n%mod]*tp(n/mod)%mod*dfac(n/p)%mod;}
	int c(ll n,ll m){
		if(m<0||n<m)return 0;
		ll r=exp(p,cnt(n)-cnt(m)-cnt(n-m));
		return r?r*dfac(n)%mod*inv(dfac(m))%mod*inv(dfac(n-m))%mod:0;
	}
	#undef N	
}; 
RS a,b;ll mod,invA,invB;
int crt(int a,int b){return ((ll)invA*b+(ll)invB*a)%mod;}
int exp(int x,ll n){return crt(a.exp(x,n),b.exp(x,n));}
int c(ll n,ll m){ll A=a.c(n,m),B=b.c(n,m);return crt(A,B);}
int dec(int o){return o<0?o+mod:o;} 
int work(ll n,ll m,int k){
	if(n==m)
		return dec(exp(2,n+n-1)-c(n+n,n)/2)%exp(10,k);
	else{
		swap(n,m);
		ll res=exp(2,n+m-1);
		if(!(n+m&1))res=(res+c(n+m,(n+m)/2)/2);
		for(ll j=(n+m)/2+1;j<=m-1;j++)res=res+c(n+m,j);
		return res%exp(10,k);
	}	
}
int main(){
	a.p=2;a.mod=1024;a.ph=512;a.build();
	b.p=5;b.mod=1953125;b.ph=1562500;b.build();
	mod=a.mod*b.mod;
	invA=b.inv(a.mod)*a.mod;
	invB=a.inv(b.mod)*b.mod;
	ll n,m;int k;
	while(scanf("%lld%lld%d",&n,&m,&k)!=EOF){
		int x=work(n,m,k);
		string str="";
		for(int i=1;i<=k;i++)str.push_back(x%10+'0'),x/=10;
		reverse(str.begin(),str.end());
		cout<<str<<endl;
	}
} 
