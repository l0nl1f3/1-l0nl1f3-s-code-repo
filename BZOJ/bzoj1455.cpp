#include<set>
#include<map>
#include<stack>
#include<queue>
#include<cstdio>
#include<string>
#include<bitset>
#include<vector>
#include<cstring>
#include<complex>
#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;
#define fi first
#define se second
#define il inline
#define mp make_pair
#define pb push_back
#define ll long long
#define gc getchar()
#define inf 1001001001
#define Ri register int
#define Pii pair<int,int>
#define gmax(a,b) (a)=max((a),(b))
#define gmin(a,b) (a)=min((a),(b))
#define infll 1001001001001001001LL
#define dbg(vari) cerr<<#vari<<" = "<<(vari)<<endl
#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
il int read(){bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;}
#define gi read()
#define N 101234
int n,a[N],rk[N],kr[N],q[N];ll ans,m,f[N],b[N];multiset<ll>ms;
bool cmp(int x,int y){return b[x]<b[y];}
bool chk(ll x){
	ms.clear();
	ll s=0;
	for(int i=1,t=-1,h=0,T=1;i<=n;i++){
		for(s+=b[i];s>x;s-=b[T++]);
		if(T>i)return 0;
		for(;h<=t&&a[i]>=a[q[t]];h<t?ms.erase(f[q[t-1]]+a[q[t--]]),0:t--);
		if(q[++t]=i,h<t)ms.insert(f[q[t-1]]+a[q[t]]);
		for(;h<=t&&q[h]<T;h<t?ms.erase(f[q[h]]+a[q[++h]]),0:++h);
		f[i]=a[q[h]]+f[T-1];
		if(h<t)gmin(f[i],*ms.begin());	
	}return f[n]<=m;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)a[rk[i]=kr[i]=i]=gi,b[i]=gi;
	sort(rk+1,rk+n+1,cmp);
	int fn=n;n=1;for(int i=fn;i;i--)while(n<=fn&&a[i]>=b[rk[n]])kr[rk[n++]]=i;
	for(int i=n=1,r;i<=fn;n++)for(a[n]=a[i],b[n]=b[i++],r=max(kr[i-1],i-1);i<=r;i++)gmax(a[n],a[i]),b[n]+=b[i],gmax(r,kr[i]); 
	n--;ll l=0,r=infll,o=0;
	for(;l<=r;chk(o=(l+r)/2)?ans=o,r=o-1:l=o+1);
	cout<<ans;
	return 0;
}


