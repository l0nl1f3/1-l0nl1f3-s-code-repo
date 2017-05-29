#include<bits/stdc++.h>
using namespace std;
#define p 1000000007
#define N 3001
int T,n,k;long long f[N][N];
int main(){
	int i,j;
	f[1][1]=1;
	for(i=1;i<N;i++)for(j=1;j<N;j++){
		if(i>1||j>1){
			f[i][j]=(f[i-1][j]*2*j%p+f[i-1][j-1]*(i-2*j+2)%p)%p;
		}
	}
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		int ans=0;
		for(i=1;i<=n-k;i++)ans=(ans+f[n][i])%p;
		printf("%d\n",ans);
	} 
} 
