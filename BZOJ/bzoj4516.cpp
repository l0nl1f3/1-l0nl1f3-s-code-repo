#include<bits/stdc++.h>
using namespace std;
#define N 101234
int n,a[N];vector<int>ls[N];
bool cmp(int i,int j){return a[i]<a[j];}
struct SuffixArray{
	int rk[N],h[N],height[N],sa[N],w[N],buc[N],fir[N],sec[N];
	#define M 262144
	int T[M+M][20],tg[M+M],lg[N];
	void init(int *a){
		int i,j,k;
		for(i=1;i<=n;i++)sa[i]=i;
		sort(sa+1,sa+n+1,cmp);
		for(i=1,k=0;i<=n;i++)
			for(rk[sa[i]]=++k;i<n&&a[sa[i]]==a[sa[i+1]];rk[sa[++i]]=k);
		for(j=1;k<n;j<<=1){
			for(i=1;i<=n;i++)buc[rk[i+j]]++;
			for(i=1;i<=k;i++)buc[i]+=buc[i-1];
			for(i=1;i<=n;i++)sec[buc[rk[i+j]]--]=i;
			for(i=0;i<=k;i++)buc[i]=0;
			for(i=1;i<=n;i++)buc[rk[i]]++;
			for(i=1;i<=k;i++)buc[i]+=buc[i-1];
			for(i=n;i;i--)sa[buc[rk[sec[i]]]--]=sec[i];
			for(i=0;i<=k;i++)buc[i]=0;
			for(i=1,k=0;i<=n;i++)
				for(sec[sa[i]]=++k;
				i<n&&rk[sa[i]]==rk[sa[i+1]]&&rk[sa[i]+j]==rk[sa[i+1]+j];
				sec[sa[++i]]=k);
			for(i=1;i<=n;i++)rk[i]=sec[i]; 	
		}
		for(i=1;i<=n;i++){
			if(rk[i]==1)continue;
			for(h[i]=max(0,h[i-1]-1);a[i+h[i]]==a[sa[rk[i]-1]+h[i]];h[i]++); 
		}
		for(i=1;i<=n;i++)T[rk[i]][0]=height[rk[i]]=h[i];
		for(j=1;(1<<j)<=n;j++)
        	for(i=1;i+(1<<j)-1<=n;i++)
            	T[i][j]=min(T[i][j-1],T[i+(1<<j-1)][j-1]);
    	for(i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	}
	void modify(int x){for(x+=M;x;tg[x]=1,x>>=1);}
	int pre(int x,int y=1){
		for(x+=M;x&&y;((x&1)&&tg[x^1])?y=0:x>>=1);
		for(x^=1;x<M;(x<<=1),x|=tg[x|1]);
		return x-M;
	}
	int suf(int x,int y=1){
		for(x+=M;x&&y;((~x&1)&&tg[x^1])?y=0:x>>=1);
		for(x^=1;x<M;(x<<=1),x|=!tg[x]);
		return x-M;
	}
	int lcp(int l,int r){
		if(l>r)swap(l,r);
		int x=lg[r-l];
		return min(T[l+1][x],T[r-(1<<x)+1][x]);
	}
	void solve(){
		long long ans=0;modify(0);modify(n+1);
		for(int i=n;i;i--){
			ans+=n-i+1;
			int p=rk[i],l=pre(p),r=suf(p);
			modify(p);
			if(1<=l&&r<=n)ans+=lcp(l,r);
			if(1<=l)ans-=lcp(l,p);
			if(r<=n)ans-=lcp(p,r); 
			printf("%lld\n",ans);
		}
	}
}SA;
char s[N];
int main(){
	freopen("qaq.in","r",stdin);
	freopen("qaq.out","w",stdout);
	int i,j,k;
	for(scanf("%d",&n),i=n;i;i--)scanf("%d",&a[i]);
	SA.init(a);
	SA.solve();
}
