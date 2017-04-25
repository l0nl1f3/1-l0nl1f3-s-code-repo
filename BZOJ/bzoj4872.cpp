#include<bits/stdc++.h>
#define N 101234
#define p 100003
#define ll long long
using namespace std;
int n,K,a[N],f[N],g[N];
vector<int>d[N];
int exp(int a,int n){
	int res=1;
	for(;n;n>>=1,a=(ll)a*a%p)
		if(n&1)res=(ll)res*a%p;
	return res;
}
int main(){
	int i,j,k;
	scanf("%d%d",&n,&K);
	for(i=1;i<=n;i++)scanf("%d",a+i);
	for(i=1;i<=n;i++)
		for(j=i;j<=n;j+=i)
			d[j].push_back(i);
	for(i=n,k=0;i;i--){
		if(!a[i])continue;
		for(j=0;j<d[i].size();j++)a[d[i][j]]^=1;
		++k;
	}
	if(k<=K){
		for(i=1;i<=n;i++)k=(ll)k*i%p;
		return printf("%d",k),0;
	}
	int inv=exp(n,p-2);
	f[n]=g[n]=1;
	for(i=n-1;i-K;i--){
		j=exp((1-(ll)(n-i)*inv%p*f[i+1]%p+p)%p,p-2);
		f[i]=(ll)i*inv%p;
		g[i]=(ll)(n-i)*inv%p*g[i+1]%p+1; 
		f[i]=(ll)f[i]*j%p;
		g[i]=(ll)g[i]*j%p;
	}
	for(i=K+1,j=K;i<=k;i++)
		j=((ll)f[i]*j%p+g[i])%p;
	for(i=1;i<=n;i++)j=(ll)j*i%p; 
	return printf("%d",j),0;
}

