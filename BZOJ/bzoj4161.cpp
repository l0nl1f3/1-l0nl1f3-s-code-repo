#include<bits/stdc++.h>
#define N 4001
#define p 1000000007
#define ll long long
int n,k,h[N],a[N],b[N],c[N],M[N],res[N];
int mul(int *a,int *b,int *q){
	int i,j;memset(c,0,sizeof(c));
	for(i=0;i<k;i++)
		for(j=0;j<k;j++)
			c[i+j]=(c[i+j]+(ll)a[i]*b[j])%p; 
	for(i=k+k-1;i>k;i--){
		for(j=0;j<k;j++)
			c[i-j]=(c[i-j]+(ll)c[i-1]*q[j])%p;
		c[i-1]=0;
	}
	for(i=0;i<k;i++)a[i]=c[i];
}
int main(){
	int i,j;
	for(scanf("%d%d",&n,&k),i=0;i<k;i++)scanf("%d",a+i),M[i]=(a[i]<0?a[i]+p:a[i]);
	for(i=0;i<k;i++)scanf("%d",h+i),h[i]<0?h[i]+=p:0;
	for(b[1]=res[0]=1;n;n>>=1,mul(b,b,M))
		if(n&1)mul(res,b,M);
	for(i=j=0;i<k;i++)j=(j+(ll)h[i]*res[i])%p;
	return printf("%d",j),0;
} 
