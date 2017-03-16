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
#define inf 31234
#define Ri register int
#define Pii pair<int,int>
#define gmax(a,b) (a)=max((a),(b))
#define gmin(a,b) (a)=min((a),(b))
#define infll 1001001001001001001LL
#define dbg(vari) cerr<<#vari<<" = "<<(vari)<<endl
#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
il int read(){bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;}
#define gi read()
#define N 1001234
int n,K,qn,a[N],f[N],g[N],bit[N];
ll qzh[N],qz[N],q[N];
int miz(int r,int d){for(r=qn-r+1;r<=qn;r+=r&-r)gmin(bit[r],d);}
int maz(int r,int d){for(r=qn-r+1;r<=qn;r+=r&-r)gmax(bit[r],d);}
int qmin(int r,int ans=inf){for(r=qn-r+1;r;r-=r&-r)gmin(ans,bit[r]);return ans;}
int qmax(int r,int ans=-inf){for(r=qn-r+1;r;r-=r&-r)gmax(ans,bit[r]);return ans;}
bool chk(ll x){
	memset(bit,0x3f,sizeof(bit));
	miz(q[0],0);
	for(int i=1;i<=n;i++){
		f[i]=qmin(lower_bound(qz+1,qz+qn+1,qzh[i]-x)-qz)+1;
		miz(q[i],f[i]);
	}	
	memset(bit,-0x3f,sizeof(bit));
	maz(q[0],0);
	for(int i=1;i<=n;i++){
		g[i]=qmax(lower_bound(qz+1,qz+qn+1,qzh[i]-x)-qz)+1;
		maz(q[i],g[i]);
	}	
	return f[n]<=K&&K<=g[n]; 
}
int main(){
	n=gi;K=gi;for(int i=1;i<=n;i++)qzh[i]=qzh[i-1]+(a[i]=gi);
	for(int i=0;i<=n;i++)qz[++qn]=qzh[i];
	sort(qz+1,qz+qn+1);
	for(int i=0;i<=n;i++)q[i]=lower_bound(qz+1,qz+qn+1,qzh[i])-qz;
	ll l=-1e10,r=1e10,o;
	for(;l<r;chk(o=l+((r-l)>>1))?r=o:l=o+1);
	cout<<l;
	return 0;
}

