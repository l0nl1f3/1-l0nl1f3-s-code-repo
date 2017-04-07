#include<bits/stdc++.h>
#define N 4000
#define ll long long
#define p 1000000007
long long inv[N],f[N],i,j,n,a[N],h[N],b[N],c[N];
inline ll fpow(ll a,int n){
	ll res=1;
	for(;n;n>>=1,a=a*a%p)
		if(n&1)res=res*a%p;
	return res;
}
inline int get()
{
	char c;
	while ((c = getchar()) < 48 || c > 57);
	int res = c - 48;
	while ((c = getchar()) >= 48 && c <= 57)
		res = res * 10 + c - 48;
	return res;
}
int main(){
	register int i;long long k=0,l,j;;
	for(n=get(),i=0;i<n;i++)c[i]=get();
	for(i=0;i<=n;i++){
		l=1;
		for(j=0;j<n;j++){
			k=(k+c[j]*l)%p;
			l=l*i%p;
		}
		f[i]=k;
	}
	for(i=1;i<=n;i++){
	    for(j=n;j-12>=i;j-=13){
			f[j]=f[j]<f[j-1]?f[j]-f[j-1]+p:f[j]-f[j-1];
			f[j-1]=f[j-1]<f[j-2]?f[j-1]-f[j-2]+p:f[j-1]-f[j-2];
			f[j-2]=f[j-2]<f[j-3]?f[j-2]-f[j-3]+p:f[j-2]-f[j-3];
			f[j-3]=f[j-3]<f[j-4]?f[j-3]-f[j-4]+p:f[j-3]-f[j-4];
			f[j-4]=f[j-4]<f[j-5]?f[j-4]-f[j-5]+p:f[j-4]-f[j-5];
			f[j-5]=f[j-5]<f[j-6]?f[j-5]-f[j-6]+p:f[j-5]-f[j-6];
			f[j-6]=f[j-6]<f[j-7]?f[j-6]-f[j-7]+p:f[j-6]-f[j-7];
			f[j-7]=f[j-7]<f[j-8]?f[j-7]-f[j-8]+p:f[j-7]-f[j-8];
			f[j-8]=f[j-8]<f[j-9]?f[j-8]-f[j-9]+p:f[j-8]-f[j-9];
			f[j-9]=f[j-9]<f[j-10]?f[j-9]-f[j-10]+p:f[j-9]-f[j-10];
			f[j-10]=f[j-10]<f[j-11]?f[j-10]-f[j-11]+p:f[j-10]-f[j-11];
			f[j-11]=f[j-11]<f[j-12]?f[j-11]-f[j-12]+p:f[j-11]-f[j-12];
			f[j-12]=f[j-12]<f[j-13]?f[j-12]-f[j-13]+p:f[j-12]-f[j-13];
    }
    for(;j>=i;j--)f[j]=f[j]<f[j-1]?f[j]-f[j-1]+p:f[j]-f[j-1];
  }
  for(i=1,j=1;i<=n;i++)j=j*i%p;
  for(inv[i=n]=fpow(j,p-2);i>=1;i--)inv[i-1]=inv[i]*i%p;
	for(b[0]=f[0],i=a[0]=1;i<=n;i++){
		for(j=i;j;j--){
			a[j]=(a[j-1]-a[j]*(i-1))%p;
			a[j]<0?a[j]+=p:0;
		}
		for(f[i]=f[i]*inv[i]%p,a[0]=j++;j<=i;j++){
			b[j]=(b[j]+a[j]*f[i])%p;
		} 
	}	
	for(i=0;i<=n;i++)printf("%lld ",b[i]);
}

