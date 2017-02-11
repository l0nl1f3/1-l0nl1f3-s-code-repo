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
#define N 301234 
int n,m,ans[N],L[N],R[N],v[N];
struct data{int a,b,c;}d[N];
bool cmp(data a,data b){return a.a<b.a||(a.a==b.a&&a.c<b.c);}
struct bit{
	int b[N];
	int MaX(int r,int d){for(;r<N/3;r+=r&-r)d?gmax(b[r],d):b[r]=0;}
	int mAx(int r){int ans=0;for(;r;r-=r&-r)gmax(ans,b[r]);return ans;}
}T;
void cdq(int l,int r){
	if(l==r){
		gmax(ans[l],1);
		return;	
	}
	int mid=(l+r)/2;
	cdq(l,mid);
	for(int i=l;i<=r;i++){
		d[i].a=(i<=mid?v[i]:L[i]);
		d[i].b=(i<=mid?R[i]:v[i]);
		d[i].c=i;
	}
	sort(d+l,d+r+1,cmp);
	for(int i=l,b;i<=r;i++)(b=d[i].c)<=mid?T.MaX(d[i].b,ans[b]):ans[b]=max(ans[b],T.mAx(d[i].b)+1);
	for(int i=l;i<=r;i++)if(d[i].c<=mid)T.MaX(d[i].b,0);
	cdq(mid+1,r);
}
int main(){
	n=gi;m=gi;
	for(int i=1;i<=n;i++)v[i]=L[i]=R[i]=gi;
	for(int i=1,a,b;i<=m;i++){
		a=gi;b=gi;
		gmax(R[a],b);gmax(L[a],b);
	}
	cdq(1,n);
	printf("%d",*max_element(ans+1,ans+n+1));
	return 0;
}

