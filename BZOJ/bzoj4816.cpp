//#include<bits/stdc++.h>
#include<time.h>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define ll long long
#define p 1000000007
#define N 1001234
using namespace std;
int T,n,m,pn,f[N],inv[N],pr[N],phi[N],mu[N],ps[N];
bool np[N];
int fpow(int a,int n){
	int res=1;
	a=a%p;n=n%(p-1);
	for(;n;n>>=1,a=(ll)a*a%p)
		if(n&1)res=(ll)res*a%p;
	return res;
}
int prework(){
	phi[1]=mu[1]=1;
	for(int i=2;i<N;i++){
		if(!np[i]){
			mu[i]=-1;
			pr[++pn]=i;
		}
		for(int j=1;i*pr[j]<N&&j<=pn;j++){
			np[i*pr[j]]=1;
			if(i%pr[j]==0){
				mu[i*pr[j]]=0;
				break;
			}
			mu[i*pr[j]]=-mu[i]; 	
		}
	}
	for(int i=0;i<N;i++)ps[i]=1;
	for(int i=1;i<N;i++)
		for(int j=i;j<N;j+=i){
		if(mu[j/i]==-1)ps[j]=(ll)ps[j]*inv[i]%p;
		if(mu[j/i]==1)ps[j]=(ll)ps[j]*f[i]%p;
	}
	for(int i=1;i<N;i++)
		ps[i]=(ll)ps[i]*ps[i-1]%p;
}
#define min(a,b) ((a)<(b)?(a):(b))
int main(){
	freopen("product.in","r",stdin);
	freopen("product.out","w",stdout);
	int i,j,k;
	
	for(i=0;i<N;i++)f[i]=(i<2?i:(f[i-1]+f[i-2])%p);
	for(i=0;i<N;i++)inv[i]=fpow(f[i],p-2);
	prework();
	
	for(scanf("%d",&T);T--;){
		scanf("%d%d",&n,&m);
		/*for(i=1,k=1;i<=n;i++)
			for(j=1;j<=n;j++)
				k=(ll)k*f[__gcd(i,j)]%p;*/
		for(i=1,k=1;i<=min(n,m);i=j+1){
			j=min(n/(n/i),m/(m/i));
			k=(ll)k*fpow((ll)ps[j]*fpow(ps[i-1],p-2)%p,(ll)(n/i)*(m/i)%(p-1))%p;	
		} 
		printf("%d\n",k);
	}
}	
