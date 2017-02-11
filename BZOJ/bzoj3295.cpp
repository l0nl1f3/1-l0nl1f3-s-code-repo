#include<map>
#include<stack>
#include<queue>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<complex>
#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;
#define inf 1001001001
#define infll 1001001001001001001LL
#define ll long long
#define dbg(vari) cerr<<#vari<<" = "<<(vari)<<endl
#define gmax(a,b) (a)=max((a),(b))
#define gmin(a,b) (a)=min((a),(b))
#define Ri register int
#define gc getchar()
#define il inline
il int read(){
	bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;
}
#define gi read()
#define ig read()
#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
#define N 123456
#define M 5001234
int n,m,a[N],pos[N],L[N],R[N],rt[N],sum[N];
void update(int p,int v){for(int x=p;x<=n;x+=(x&-x))sum[x]+=v;}
int query(int p){int ret=0;for(int x=p;x;x-=(x&-x))ret+=sum[x];return ret;}
int ls[M],rs[M],sz[M];
int tot;
void update(int &o,int l,int r,int p){
    if(!o) o=++tot;
    sz[o]++;
    if(l==r) return;
    int m=(l+r)/2;
    if(m>=p) update(ls[o],l,m,p);
    else update(rs[o],m+1,r,p);
}
int query(int o,int l,int r,int s,int t){
    if(!o) return 0;
    if(l>=s&&r<=t) return sz[o];
    int m=(l+r)/2;
    int ans=0;
    if(m>=s) ans+=query(ls[o],l,m,s,t);
    if(m<t) ans+=query(rs[o],m+1,r,s,t);
    return ans;
}
int A[N],B[N];
int da(int s,int t,int v){
    int ans=0;
    for(int i=v;i;i-=(i&-i)) ans-=query(rt[i],1,n,s,t);
    for(int i=n;i;i-=(i&-i)) ans+=query(rt[i],1,n,s,t);
    return ans;
}
int xiao(int s,int t,int v){
    int ans=0;
    for(int i=v;i;i-=(i&-i)) ans+=query(rt[i],1,n,s,t);
    return ans;
}
void inversion(ll &ans){
	for(int i=1;i<=n;i++){
		L[i]=query(n)-query(a[i]);
		ans+=L[i];
		update(a[i],1);
	}
    memset(sum,0,sizeof(sum));
    for(int i=n;i>=1;i--){
        R[i]=query(a[i]);
        ans=ans+R[i];
        update(a[i],1);
    }
    ans/=2;
}
int main(){
	n=gi;m=gi;
	for(int i=1;i<=n;i++)pos[a[i]=gi]=i;
	ll ans;inversion(ans=0);	
    for(int i=0,x;i<m;i++){
        printf("%lld\n",ans);
        x=gi;
        ans=ans-R[pos[x]]-L[pos[x]]+da(1,pos[x],x)+xiao(pos[x],n,x);
        for(int i=x;i<=n;i+=(i&-i))update(rt[i],1,n,pos[x]);
    }
    return 0;
}
