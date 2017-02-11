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
#define CHANGE 0
#define QUERY 1
#define N 123456
int n,q,f[N];ll a[N];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
struct bit{
	ll b[N];
	void add(int r,ll d){for(;r<N;r+=r&-r)b[r]+=d;} 
	ll query(int r){ll ans=0;for(;r;r-=r&-r)ans+=b[r];return ans;}
	ll query(int l,int r){return query(r)-query(l-1);} 
}T;
void change(int i,int r){
	for(;i&&i<=r;i=find(i+1)){
		ll t=sqrt(a[i]);
		T.add(i,t-a[i]);a[i]=t;
		if(a[i]<=1)f[i]=find(i+1);
	}	
}
int main(){
	n=gi;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		f[i]=i+(a[i]<=1);
		T.add(i,a[i]);
	}
	q=gi;
	for(int i=1,o,l,r;i<=q;i++){
		o=gi;l=gi;r=gi;if(l>r)swap(l,r);
		if(o==CHANGE)change(l,r);
		else printf("%lld\n",T.query(l,r));
	}
	return 0;
}

