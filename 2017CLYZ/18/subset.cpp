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
#define eps 0 
int n,a[N],a1,a2;ll s[N];double ans=-infll;
double delta(ll x,ll d){return d<0?(double)-infll:(s[x]-s[x-d-1]+s[n]-s[n-d])/(double)(2*d+1);}
int main(){
	FO(subset);n=gi;
	for(int i=1;i<=n;i++)a[i]=gi;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
	for(int i=1,l,r,o;i<=n;i++){
		for(l=0,r=min(i-1,n-i);
			o=(l+r)/2,l<=r;
			delta(i,o)-delta(i,o-1)>=eps?l=o+1:r=o-1);
		
		double t=delta(i,r)-a[i];
		if(t>ans)ans=t,a1=i,a2=r;
	}
	double ans=0;
	for(int i=a1-a2;i<=a1;i++)ans+=a[i];
	for(int i=n-a2+1;i<=n;i++)ans+=a[i];
	printf("%.5f\n",ans/(a2*2+1)-a[a1]);
	return 0;
}
	
