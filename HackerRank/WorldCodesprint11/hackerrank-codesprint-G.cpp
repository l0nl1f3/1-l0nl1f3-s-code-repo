#include<bits/stdc++.h>
#define N 1001234
#define ll long long
using namespace std;
int n,q,g[N],p[N],w[N];
int main(){
	int i,j,k,x,y,z;
	scanf("%d%d",&n,&q);
	for(i=1;i<n;i++)scanf("%d",w+i);
	for(i=1;i<=n;i++)scanf("%d%d",g+i,p+i);
	for(i=1;i<=q;i++){
		scanf("%d%d",&x,&y);
		ll mn=x,gas=0,ans=0;
		for(z=x;z<=y;z++){
			if(p[z]<p[mn])mn=z;
			gas+=g[z];
			if(z<y&&gas<w[z]){
				ans=(ans+p[mn]*(ll)(w[z]-gas));
				gas=w[z];
			}
			gas-=w[z];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
