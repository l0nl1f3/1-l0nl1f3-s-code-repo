#include<bits/stdc++.h>
using namespace std;
#define N 123
int n,d,a[N];
int cmp(int i,int j){
	return d?a[i]>a[j]:a[i]<a[j];
}
int main(){
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",a+i);
	for(i=2,j=k=0;i<n;i++){
		k+=(a[i]>a[i-1]&&a[i+1]>a[i]);
		k+=(a[i]<a[i-1]&&a[i+1]<a[i]);
	}
	printf("%d",k);
	return 0;
}
