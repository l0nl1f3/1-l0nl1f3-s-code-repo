#include<bits/stdc++.h>
using namespace std;
//f[i][j] i个取sum = j 的是否可行
int n,a[101],f[101][10101];
int main(){
	int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",a+i);
	f[0][0]=1;
	for(i=1;i<=n;i++){
		for(j=10100;j>=a[i];j--)
			f[i][j]=f[i-1][j]|f[i-1][j-a[i]];
		for(j=a[i]-1;~j;j--)f[i][j]=f[i-1][j];
	}
	for(j=10100;~j;j--){
		if(f[n][j]&&j%10!=0){
			cout<<j;return 0;
		}
	}cout<<0;
			 
} 
