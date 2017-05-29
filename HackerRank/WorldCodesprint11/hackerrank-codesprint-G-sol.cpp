#include<bits/stdc++.h> 
#define N 201234 
#define ll long long
using namespace std;
int n,q,sn;ll st[N],f[N][20],h[N][20],dp[N][20],s[N],sum[N],d[N],g[N],p[N],nxt[N];
int main(){
	int i,j,k;
	scanf("%d%d",&n,&q);
	for(i=2;i<=n;i++)scanf("%lld",d+i),d[i]+=d[i-1];
	for(i=1;i<=n;i++)scanf("%lld%lld",g+i,p+i);
	p[n]=0;d[n+1]=1e12;
	for(nxt[i=n]=n,i--;i;i--){
		nxt[i]=i;
		for(j=i,k=0;d[nxt[j]+1]-d[j]<=g[j]+k;p[i]=min(p[i],p[j]),k+=g[j]-(d[nxt[j]+1]-d[j]),j=nxt[j]+1);
		nxt[i]=nxt[j];
		g[i]=k+g[j]+d[j]-d[i];
		p[i]=min(p[i],p[j]);
	}
	for(h[n][0]=i=n,i--;i;i--){
		j=min(nxt[i]+1,(ll)n);
		h[i][0]=j;
		sum[i]=sum[j]+max(d[j]-d[i]-g[i],0ll);
	}
	for(i=1;i<=n;i++){
		while(sn){
			if(p[j=s[sn]]>p[i])
				f[j][0]=i,
				dp[j][0]=p[j]*(sum[j]-sum[i]),--sn;
			else break;
		}s[++sn]=i;
	}
	while(sn)f[i=s[sn--]][0]=n,dp[i][0]=0;
	
	for(j=0;j<19;j++)
		for(i=1;i<=n;i++){
			f[i][j+1]=f[f[i][j]][j];
			h[i][j+1]=h[h[i][j]][j];
			dp[i][j+1]=dp[f[i][j]][j]+dp[i][j];
		}
	while(q--){
		int l,r;ll ans=0;
		scanf("%d%d",&l,&r);
		for(j=19;~j;j--){
			if(f[l][j]<=r){
				ans+=dp[l][j];
				l=f[l][j];
				if(f[l][0]>r)break;
			}
		}
		ll o=0,k;
		for(j=19,i=r,k=p[l];~j;j--){
			if(nxt[h[l][j]]>=r)i=min((ll)r,h[l][j]);
			else{
				o+=(sum[l]-sum[h[l][j]]);
				l=h[l][j];	
			}
		}
		ans+=max((o+sum[l]-sum[i]),0ll)*k;
		printf("%lld\n",ans);
	}
	return 0;
}
