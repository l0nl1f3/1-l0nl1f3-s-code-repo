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
#define N 201234
int n,bit[N],a[N];
int sum(int r,int ans=0){for(;r;r-=r&-r)ans+=bit[r];return ans;}
int add(int r){for(;r<N;r+=r&-r)bit[r]++;}
int main(){
	FO(counter);
	n=gi;
	for(int i=1;i<=n;i++)a[i]=gi;
	ll ans=0;
	for(int i=1,x,y,z,u,v;i<=n;i++){
		x=sum(a[i]);y=i-x-1;z=a[i]-x-1;u=n-z-i;
		ans+=(ll)x*u*2+(ll)z*(z-1)/2+(ll)x*z-(ll)y*z-(ll)u*(u-1)/2;
		add(a[i]);
	}
	cout<<ans;
	return 0;
}

