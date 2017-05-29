#include<bits/stdc++.h>
#define ll long long
#define N 101234
#define p 1000000007
using namespace std;
int n,K,tag[N];ll ans,a[N];
int exp(int a,int n){
	int res=1;
	for(;n;n>>=1,a=(ll)a*a%p)
		if(n&1)res=(ll)res*a%p;
	return res;
}
int main(){
	int i,j,k;
	scanf("%d%d",&n,&K);
	for(i=1;i<=n;i++)scanf("%lld",a+i),tag[i]=1;
	for(k=1;(1ll<<k)<=1e18;k++);
	for(;~k;k--){
		for(i=1,j=0;i<=n;i++)
			if(tag[i]&&a[i]>>k&1)j++;
		if(j>=K){
			ans|=1ll<<k; 
			for(i=1;i<=n;i++)if(tag[i])tag[i]=a[i]>>k&1;
		}
	}
	for(i=1,j=0;i<=n;i++)if(tag[i])j++;
	for(i=j,k=1;i>j-K;i--)k=(ll)k*i%p;
	for(i=1;i<=K;i++)k=(ll)k*exp(i,p-2)%p; 
	printf("%lld\n%d",ans,k);
	return 0;
} 
