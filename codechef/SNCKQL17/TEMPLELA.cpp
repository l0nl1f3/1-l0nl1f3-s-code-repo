#include<bits/stdc++.h>
using namespace std;
int T,n,h[101],s[101];
int main(){
	int i,j;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(i=1;i<=n;i++)scanf("%d",h+i);
		if(~n&1){
			puts("no");
			continue;
		}
		memset(s,0,sizeof(s));
		int f=1;
		for(i=1;i<=n/2+1;i++)if(h[i]!=i)f=0;
		for(i=n/2+2;i<=n;i++)if(h[i]!=n-i+1)f=0;
		puts(f?"yes":"no");
	}
	return 0;
}
