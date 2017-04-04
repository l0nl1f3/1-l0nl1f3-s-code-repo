#include<bits/stdc++.h>
#define N 17 
using namespace std;
int n,C,a[N],b[N],c[N+N],f[1<<N];
int main(){
	int i,j,k,s;
	for(scanf("%d%d",&n,&C),i=0;i<n;i++)scanf("%d%d",&a[i],&b[i]);
	for(s=1;s<(1<<n);s++){
		for(i=j=k=0;i<n;i++){
			if(s>>i&1){
				j=max(j,abs(a[i]-b[i]));
				c[k++]=a[i];c[k++]=b[i];
			}
			
		}
		if(j<=C)f[s]=0;
		else {
			for(sort(c,c+k),i=0;i<k;i+=2)
				if(c[i+1]-c[i]>C)i=233;
			if(i<233)f[s]=k/2-1;else f[s]=1e9;
		} 
	}
	for(s=0;s<(1<<n);s++)
		for(i=s;i;i=(i-1)&s)f[s]=min(f[s],f[i]+f[s^i]);
	return printf("%d",f[(1<<n)-1]>=1e9?-1:f[(1<<n)-1]),0;
}
 
