#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>
using namespace std;
typedef long long ll;
ll r=0,m,minn;
int n,col;
int fa[100005],L[100005],R[100005],mx[100005],a[100005],b[100005];
ll rank[100005],dp[100005],sum[100005],mn[500005];
int pos[100005];
int find(int x)
{
	if (fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}
void pre()
{
	for (int i=1; i<=n; ++i) 
		fa[i]=i, L[i]=R[i]=i, mx[i]=a[i];
	for (int i=1; i<=n; ++i){
		int op=0;
		for (int j=n; j>=i+1; --j){
			if (op || b[i]<=a[j]){
				op=1;
				int fx=find(i), fy=find(j);
				fa[fy]=fx;
			}
		}
	}
	for (int i=1; i<=n; ++i)
		L[fa[i]]=min(L[fa[i]],i),
		R[fa[i]]=max(R[fa[i]],i),
		mx[fa[i]]=max(mx[fa[i]],a[i]);
}
int check(int x)
{
	for (int i=1; i<=n; ++i) dp[i]=1e13;
	dp[0]=0;
	for (int i=1; i<=n; ++i){
		if (i==R[fa[i]]){
			int maxn=mx[fa[i]];
			for (int j=L[fa[i]]-1; j>=0; --j){			
				if (sum[i]-sum[j]<=x)
					dp[i]=min(dp[j]+maxn,dp[i]);
				maxn=max(maxn,a[j]);
			}
		}
	}
	return dp[n]<=m;
}
struct ff{
	int d;
	ll v;
	
}p[100005];
inline bool cmp(const ff&a,const ff&b){
	return a.v<b.v;
}
int search(ll x)
{
	int l=1, r=col, d=col+1;
	while (l<=r){
		int mid=(l+r)/2;
		if (rank[mid]>=x) d=mid, r=mid-1;
		else l=mid+1;
	}
	return d;
}
void query(int l,int r,int d,int L)
{
	if (r<L) return;
	if (L<=l){
		minn=min(minn,mn[d]); return;
	}
	int mid=(l+r)/2;
	query(l,mid,d*2,L);
	query(mid+1,r,d*2+1,L);
}
void insert(int l,int r,int d,int x)
{
	if (l==r && l==x){
		mn[d]=min(mn[d],minn); return;
	}
	int mid=(l+r)/2;
	if (x<=mid) insert(l,mid,d*2,x);
	else insert(mid+1,r,d*2+1,x);
	mn[d]=min(mn[d*2],mn[d*2+1]);
}
int check1(ll x)
{	
	memset(mn,63,sizeof(mn));
	minn=0;
	//printf("\n%I64d\n",x);
	insert(1,col,1,pos[0]);
	for (int i=1; i<=n; ++i){
		int k=search(sum[i]-x);
		
		minn=mn[0];
		if (k<=n) query(1,col,1,k);
	//	printf("%d %I64d  ",k,minn);
		if (minn<mn[0]){
	//		printf("%d  ",pos[i]);
			minn+=a[i];
			dp[i]=minn;
			insert(1,col,1,pos[i]);
	//		printf("%d   ",pos[i]);
		}
		else dp[i]=mn[0];
	}
//	printf("%I64d %I64d\n",x,dp[n]);
	return dp[n]<=m;
}
void pre1()
{
	for (int i=1; i<=n; ++i) p[i].v=sum[i], p[i].d=i;
	p[++n].v=0; p[n].d=0;				//!!
	sort(p+1,p+1+n,cmp);
	p[0].v=-1;
	for (int i=1; i<=n; ++i){
		if (p[i].v!=p[i-1].v) ++col;
		pos[p[i].d]=col;
	//	printf("%d %d\n",p[i].d,col);
		rank[col]=p[i].v;
	}
//	for (int i=1; i<=n; ++i) printf("%I64d ",sum[i]);
//	printf("\n");
//	for (int i=1; i<=n; ++i) printf("%d ",pos[i]);
	--n;
	
}
void work1()
{
	pre1();
	//printf("get");
	ll l=0,mid,ans=0;
	while (l<=r){
		mid=(l+r)/2;
		if (check1(mid)) r=mid-1, ans=mid;
		else l=mid+1;
	}
	printf("%I64d\n",ans);
}
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	scanf("%d%I64d",&n,&m);
	int mnb=1e9+1,mxa=0;
	for (int i=1; i<=n; ++i){
		scanf("%d%d",&a[i],&b[i]);
		r+=b[i];
		sum[i]=sum[i-1]+b[i];
		mnb=min(mnb,b[i]);
		mxa=max(mxa,a[i]);
	} 
	if (mnb>mxa){
		work1(); return 0;
	}
	pre();
	ll l=0,mid,ans=0;
	while (l<=r){
		mid=(l+r)/2;
		if (check(mid)) r=mid-1, ans=mid;
		else l=mid+1;
	}
	printf("%d",ans);
}
