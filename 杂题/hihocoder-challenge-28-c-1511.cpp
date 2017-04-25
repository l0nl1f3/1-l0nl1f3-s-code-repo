#include<bits/stdc++.h>
#define p 998244353
#define N 1000001
#define ll long long
using namespace std;
int f[N],inv[N];
int exp(int a,int n){
	int r=1;
	for(;n;n>>=1,a=(ll)a*a%p)
		if(n&1)  r=(ll)r*a%p;
	return r;
}
int c(int n,int m){
	return n<0||m<0||n<m?0:(ll)f[n]*inv[m]%p*inv[n-m]%p;
}
int main(){
	int n,i,j,k;
	cin>>n;
	for(i=f[0]=1;i<=n;i++)f[i]=(ll)f[i-1]*i%p;
	for(i=n,inv[i]=exp(f[i],p-2);i;i--)inv[i-1]=(ll)inv[i]*i%p;
	for(i=n-2,j=0,k=1;~i;i--){
		j=(j+(ll)(i+1)*(i+1)%p*n%p*k%p*c(n-2,i)%p)%p;
		k=(ll)k*(n-1)%p;
	}
	j=j-(ll)(n+n-2)*(n+n-2)%p*exp(n,n-3)%p;
	j=(ll)j%p*exp(n,p-2)%p;
	if(j<0)j+=p; 
	return printf("%d",j),0;
}
