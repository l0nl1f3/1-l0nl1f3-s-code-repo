#include <cstdio>
#include <iostream>
#define ll long long
#define p 1000003
int i,f[p],iv[p];
int pwr(int a,int n,int res=1){
	for(;n;n>>=1,a=(ll)a*a%p)
		if(n&1)res=(ll)res*a%p;
	return res;
}
int c(int n,int m){
	if(n<m)return 0;
	if(n<p&&m<p)return (ll)f[n]*iv[m]%p*iv[n-m]%p;
	return (ll)c(n/p,m/p)*c(n%p,m%p)%p;
}
int main(){
	for(i=f[0]=1;i<p;i++)f[i]=(ll)f[i-1]*i%p;
	for(iv[i=p-1]=pwr(f[p-1],p-2);i;i--)iv[i-1]=(ll)iv[i]*i%p;
	int t;scanf("%d",&t);
	while(t--){
		int n,l,r;scanf("%d%d%d",&n,&l,&r);
		printf("%d\n",(c(n+r-l+1,n)-1+p)%p);
	}
} 
