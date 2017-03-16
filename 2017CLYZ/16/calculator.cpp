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
int z,y,P;
int Fp(int a,int n,int p){
	int ans=1;
	for(;n;n>>=1,a=(ll)a*a%p)if(n&1)ans=(ll)ans*a%p;
	return ans;
}
int gcd(int a,int b){return !b?a:gcd(b,a%b);}
int exgcd(int a,int b,int &x,int &y){
	if(!b)x=1,y=0;
	else{
		exgcd(b,a%b,y,x);
		y-=(a/b)*x;
	}
}
inline int inverse(int a,int b) {
	int x,y;
	exgcd(a,b,x,y);
	if(x<0) x+=b;
	return x;
}
namespace Log{
	map<int,int> f;
	inline int bsgs(int a,int b,int p){
	    if(b==1)
	      return 0;
	    if(a==0)
	      if(b==0)
	        return 1;
	      else
	        return -1;
	    int i,j,k,l,c=gcd(a,p),d=1,q=0;
	    while(c>1)
	      {
	       if(b%c)
	         return -1;
	       b/=c;
	       p/=c;
	       d=(ll)d*a/c%p;
	       q++;
	       if(b==d)
	         return q;
	       c=gcd(a,p);
	      }
	    k=sqrt(p);
	    f.clear();
	    for(i=0,j=b;i<k;i++,j=(ll)j*a%p)
	      f[j]=i+1;
	    for(i=1,j=1;i<=k;i++)
	      j=(ll)j*a%p;
	    for(i=1,l=(ll)d*j%p;(i-1)*k<=p;i++,l=(ll)l*j%p)
	      if(f[l])
	        return i*k-f[l]+1+q;
	    return -1;
	}
	int main(){
		int ans=bsgs(y%P,z%P,P);
		if(~ans)printf("%d\n",ans);
		else puts("Math Error");
	}
}
namespace Binomial{
	#define N 1001 
	int C[N][N];bool ined=0;
	void Triangle(){
		for(int i=C[0][0]=1;i<N;i++){
			C[i][0]=1;
			for(int j=1;j<=i;j++){
				C[i][j]=C[i-1][j-1]+C[i-1][j];
				if(C[i][j]>=P)C[i][j]-=P; 
			}
		}
		printf("%d\n",C[z][y]);
	} 
	int Choose(int x,int y,int mod){
		int sx=1LL,sy=1LL;
		while(y){
			sx=(ll)sx*x%mod;
			sy=(ll)sy*y%mod;
			x--;y--;
		}
		return sx*(ll)Fp(sy,mod-2,mod)%mod;
	}
	int lucas(int x,int y,int mod){
		if(y==0) return 1LL;
		return Choose(x%mod,y%mod,mod)*(ll)lucas(x/mod,y/mod,mod)%mod;
	}
	int c1(int n,int p,int pk){  
		if(!n)return 1;  
		int ans=1;  
		for(int i=2;i<=pk;i++)if(i%p)ans=(ll)ans*i%pk;  
		ans=Fp(ans,n/pk,pk);  
		for(int k=n%pk,i=2;i<=k;i++)if(i%p)ans=(ll)ans*i%pk;  
		return (ll)ans*c1(n/p,p,pk)%pk;  
	}  
	int cal(int n,int m,int p,int pi,int pk){  
	  int k=0,a,b,c,ans;  
	  a=c1(n,pi,pk),b=c1(m,pi,pk),c=c1(n-m,pi,pk);  
	  for(int i=n;i;i/=pi)k+=i/pi;  
	  for(int i=m;i;i/=pi)k-=i/pi;  
	  for(int i=n-m;i;i/=pi)k-=i/pi;  
	  ans=(ll)a*inverse(b,pk)%pk*(ll)inverse(c,pk)%pk*(ll)Fp(pi,k,pk)%pk;  
	  return (ll)ans*(p/pk)%p*(ll)inverse(p/pk,pk)%p;  
	}  
	int exLucas(){  
	  	int n=z,m=y,p=P,ans=0;
	  	for(int x=p,i=2,k;x>1;i++)if(x%i==0){  
	    	for(k=1;x%i==0;x/=i)k*=i;  
	    	ans=(ans+cal(n,m,p,i,k))%p;  
		}  
	  printf("%d\n",ans);  
	}  
	int main(){exLucas();}
}
int main(){
	FO(calculator);
	for(int T=gi,o;T--;){
		o=gi;y=gi;z=gi;P=gi;
		if(o==1){
			printf("%d\n",Fp(y%P,z,P));
		}
		if(o==2){
			Log::main();
		}
		if(o==3){
			Binomial::main(); 
		}
	}

	return 0;
}

