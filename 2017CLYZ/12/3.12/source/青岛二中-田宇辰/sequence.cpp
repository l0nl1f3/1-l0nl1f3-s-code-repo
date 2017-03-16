#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<ctime>
#define rep(i,a,b) for(i=a;i<=b;i++)
#define lid node<<1
#define rid node<<1|1
#define lch lid,l,mid
#define rch rid,mid+1,r
using namespace std;
typedef long long ll;
const ll INF=100000000000000000ll;
const int N=200010;
int left[N],rr[N],right[N];
int n;ll m;
ll sum[N];
ll a[N],b[N];ll hwc[N];
map<ll,int> mp;
ll ans;
struct fenwick{
	int c[N];int n;
	int lowbit(int x){
		return x&(-x);
	}
	int query(int x){
		int ret=0;
		for(;x;x-=lowbit(x))	ret=max(ret,c[x]);
		return ret;
	}
	void add(int x,int w){
		for(;x<=n;x+=lowbit(x))	c[x]=max(c[x],w);
	}
	void clear(){
		memset(c,0,sizeof(c));
	}
};fenwick fen;

ll min(ll aa,ll bb){
	return aa<bb?aa:bb;
}

ll max(ll aa,ll bb){
	return aa>bb?aa:bb;
}

ll cmp(ll aa,ll bb){
	return aa>bb;
}

struct segment_tree{
	ll seg[N<<2],lazy[N<<2];	
	void update(int node){
		seg[node]=min(seg[lid],seg[rid]);
	}
	void pushdown(int node){
		if(lazy[node]!=INF){
			seg[lid]=min(seg[lid],lazy[node]);seg[rid]=min(seg[rid],lazy[node]);
			lazy[lid]=min(lazy[lid],lazy[node]);lazy[rid]=min(lazy[rid],lazy[node]);
			lazy[node]=INF;
		}
	}
	void build(int node,int l,int r){
		int mid=l+r>>1;
		seg[node]=INF;lazy[node]=INF;
		if(l==r)	return;
		build(lch);build(rch);
	}
	void modify(int node,int l,int r,int fl,int fr,ll w){
		int mid=l+r>>1;
		if(r<fl||l>fr)	return;
		if(fl<=l&&r<=fr){
			seg[node]=min(seg[node],w);lazy[node]=min(lazy[node],w);return;
		}
		pushdown(node);
		modify(lch,fl,fr,w);modify(rch,fl,fr,w);
		update(node);
	}
	ll query(int node,int l,int r,int fl,int fr){
		int mid=l+r>>1;
		if(fl<=l&&r<=fr)	return seg[node];
		pushdown(node);
		if(mid>=fr)	return query(lch,fl,fr);
		else if(mid+1<=fl)	return query(rch,fl,fr);
		else return min(query(lch,fl,fr),query(rch,fl,fr));
	}
};segment_tree s;

inline ll read(){
	ll x=0;char ch=getchar();
	while(ch<'0'||ch>'9')	ch=getchar();
	while(ch>='0'&&ch<='9')	x=x*10+ch-'0',ch=getchar();
	return x;
}

int binary(ll kk,int k){
	int mid,r=n+1,l=k+1;int ret;
	while(l<r){
		mid=l+r>>1;
		if(sum[mid]-sum[k]<=kk)	ret=mid,l=mid+1;
		else r=mid;
	}
	return ret;
}

bool check(ll kk){
	int i,j,k;
	s.build(1,0,n);s.modify(1,0,n,0,0,0);
	int lp=1,rp;int x,y;ll tmp;
	rep(i,1,n)	rr[i]=binary(kk,i-1);
	rep(i,1,n){
		for(;lp<=i;lp++){
			x=rr[lp];y=right[i];
			if(x>=y){
				tmp=s.query(1,0,n,lp-1,i-1);
				s.modify(1,0,n,i,y-1,tmp+a[i]);
				rep(k,i+1,y-1){
					tmp=s.query(1,0,n,left[k],k-1);
					s.modify(1,0,n,k,right[k]-1,tmp+a[k]);
				}
				i=y-1;break;
			}
			else{
				tmp=s.query(1,0,n,lp-1,i-1);
				s.modify(1,0,n,i,x,tmp+a[i]);
			}
		}
	}
	//rep(i,1,n)	printf("dp[%d]=%lld\n",i,s.query(1,0,n,i,i));
	if(s.query(1,0,n,n,n)<=m)	return true;
	else return false;
}
int cc=0;
int main(){
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	int i,j;//int xx=clock();
	scanf("%d%lld",&n,&m);
	rep(i,1,n)	a[i]=read(),b[i]=read();
	rep(i,1,n)	hwc[++cc]=a[i],hwc[++cc]=b[i];
	sort(hwc+1,hwc+1+cc,cmp);
	mp[hwc[1]]=1;int cm=1;
	rep(i,2,cc)	mp[hwc[i]]=hwc[i]==hwc[i-1]?cm:++cm;
	//rep(i,1,n)	printf("%d %d\n",mp[a[i]],mp[b[i]]);
	fen.n=cm;
	for(i=n;i>=1;i--){
		right[i]=fen.query(mp[b[i]]-1);if(right[i]==0)	right[i]=i;
		fen.add(mp[a[i]],i);
	}
	int tot=0;
	int tmp=0;ll tmp1=0,tmp2=0;
	rep(i,1,n){
		tmp1=max(tmp1,a[i]);tmp2+=b[i];tmp=max(tmp,right[i]);
		if(tmp==i){
			a[++tot]=tmp1,b[tot]=tmp2;tmp1=0;tmp2=0;
		}			
	}
	n=tot;
	rep(i,1,n)	sum[i]=sum[i-1]+b[i];
	fen.clear();
	rep(i,1,n){
		left[i]=fen.query(mp[a[i]]-1);fen.add(mp[a[i]],i);
	}
	fen.clear();
	for(i=n;i>=1;i--){
		right[i]=n+1-fen.query(mp[a[i]]-1);fen.add(mp[a[i]],n+1-i);
	}
	ll l=0,r,mid;r=INF;
	//r=2500000000ll;
	rep(i,1,n)	l=max(l,b[i]);
	//mid=2335732269ll;
	//check(mid);
	while(l<r){
		mid=(l+r)/2;
		if(check(mid))	ans=mid,r=mid;
		else l=mid+1;
	}
	printf("%lld",ans);
	return 0;
}





































