#include<bits/stdc++.h>
using namespace std;
int n,a[101];
int main(){ 
	scanf("%d",&n);
	int i,l,r;
	for(i=1;i<=n;i++)scanf("%d",a+i);
	for(i=1,l=0;i<=n/2;i++)
		l+=a[i];
	for(i=1;i<=n/2;i++)
		l-=a[i+n/2];
	cout<<abs(l); 
	return 0;
}
