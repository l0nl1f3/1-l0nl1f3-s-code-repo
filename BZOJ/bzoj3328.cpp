#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n;int k,p,d[101234],t[2][2],e[2][2],res[2][2],fib[2][2],a[2][2];
int exp(int a,ll n){
	int res=1;
	for(;n;n>>=1,a=(ll)a*a%p)
		if(n&1)res=(ll)res*a%p;
	return res;
}
void mul(int a[2][2],int b[2][2]){
	int i,j;
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
			t[i][j]=0;
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
			for(k=0;k<2;k++)
				t[i][j]=(t[i][j]+(ll)a[i][k]*b[k][j]%p)%p;
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
			a[i][j]=t[i][j];
}
int ord_root(int n){
	int i,j=n-1,k;
	for(i=2,k=0;i*i<=j;i++)
		if(j%i==0){
			d[++k]=i;
			if(i!=j/i)d[++k]=j/i; 
		}
	for(i=2;i<=n;i++){
		for(j=1;j<=k;j++)
			if(exp(i,d[j])==1)break;
		if(j==k+1)break;
	}
	return i;
}
int f(int x){
	int i,j;
	a[0][0]=a[1][1]=x;
	a[0][1]=a[1][0]=0;
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
			a[i][j]+=fib[i][j];
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
			res[i][j]=e[i][j];
	for(ll n=::n;n;n>>=1,mul(a,a))
		if(n&1)mul(res,a);
	return (ll)res[0][0]*exp(exp(x,n),p-2)%p;
}
int main(){
	int i,j,k;	
	fib[0][0]=fib[0][1]=fib[1][0]=e[1][1]=e[0][0]=1;
	int T;scanf("%d",&T);
	while(T--){
		scanf("%lld%d%d",&n,&k,&p);
		int w=exp(ord_root(p),(p-1)/k);
		for(i=j=0;i<k;i++)
			j=(j+f(exp(exp(w,i),p-2)))%p;
		printf("%d\n",(ll)j*exp(k,p-2)%p);
	} 
	
	return 0;
}
