#include<bits/stdc++.h>
#define N 10001
#define M 501
using namespace std;
int n,m,f[N][M];
//f[i][j] 
//前i天疲劳值为j的最大跑步距离
//f[i-1][j-1]+d[i]
//f[i][0] max(f[i-k][k]) 
int main(){
	int i,j,k;
	for(scanf("%d%d",&n,&m),i=1;i<=n;i++){
		scanf("%d",&k); 
		for(j=1;j<=m;j++)f[i][j]=f[i-1][j-1]+k;
		for(f[i][0]=f[i-1][0],j=1;j<i;j++)f[i][0]=max(f[i][0],f[i-j][j]);
	}return printf("%d",f[n][0]),0;
}
