#include<bits/stdc++.h>
#define N 100000
using namespace std;
int n,m,d,l,a[N];
int main(){
	int i,j,k;
	for(scanf("%d%d%d%d",&n,&m,&d,&l),i=1;i<=n;i++)scanf("%d",a+i);
	for(sort(a+1,a+n+1),i=1,j=0;i<=n;k=j/m,j+=((a[i++]-k*d)>=l));
	return printf("%d",j),0;
}
