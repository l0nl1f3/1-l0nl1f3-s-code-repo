#include<bits/stdc++.h>
#define p 1000000007
#define ll long long
using namespace std;
int n,m,c[2333][2333],f[2333];
int fpow(int a,int n){
	int res=1;
	for(;n;n>>=1,a=(ll)a*a%p)
		if(n&1)res=(ll)res*a%p;
	return res;
}
int main(){
	int i,j,k,l;
	for(scanf("%d%d",&n,&m),c[0][0]=1,i=1;i<=m;i++){
		c[i][0]=c[i][i]=1;
		for(j=1;j<i;j++){
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%p;
		}
	}
	if(m==1)return printf("%d",(ll)n*(n+1)/2%p),0;
	for(k=fpow(m-1,p-2),f[0]=(((ll)fpow(m,n+1)-1)*k-1+p)%p,
		i=1;i<=m;i++){
		for(j=l=0;j<i;j++){
			int sg=((i^j)&1)?p-1:1;
			l=(l+(ll)sg*c[i][j]%p*f[j])%p;
		}
		f[i]=(l+(ll)fpow(n,i)*fpow(m,n+1))%p;
		f[i]=(ll)f[i]*k%p;
	}
	printf("%d",f[m]);
}
