#include<bits/stdc++.h>
using namespace std;
int n,a[233333],f[1<<20];
#define p 1000000007
int main(){
	int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%d",a+i);
	for(i=1;i<=n;i++){
		int s=a[n-i+1];
		f[s]=1;
		for(j=s-1&s;j;j=j-1&s)
			f[s]=(f[s]+f[j])%p;
	}
	for(i=1,j=0;i<=n;i++)j=(j+f[a[i]])%p;
	cout<<(p+j-n)%p;
}
