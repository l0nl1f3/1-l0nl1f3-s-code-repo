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
#define N 401234 
int n,m,bit[N];
Pii p[N];
int add(int r,int d=1){for(;r<N;r+=r&-r)bit[r]+=d;}
int sum(int r){
	int res=0;
	for(;r;r-=r&-r)res+=bit[r];
	return res;
}
int main(){
	n=gi;m=gi;
	for(int i=n;i;i--)p[i].fi=-gi;
	for(int i=1;i<=m;i++)p[i+n].fi=-gi;
	for(int i=1;i<=n+m;i++)add(p[i].se=i);
	int ans=0,zzq=0;
	sort(p+1,p+(zzq=n)+m+1);
	for(int i=1;i<=n+m;i++){
		if(p[i].se>zzq)ans=ans+sum(p[i].se-1)-sum(zzq);
		else ans=ans+sum(zzq)-sum(p[i].se);
		add(p[i].se,-1);
		zzq=p[i].se;
	}
	cout<<ans;
	return 0;
}

