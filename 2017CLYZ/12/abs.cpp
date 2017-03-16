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
#define N 22
#define p 998244353
int n,l[N],r[N];
int fp(int x,int n,int res=1){for(;n;n>>=1,x=(ll)x*x%p)if(n&1)res=(ll)res*x%p;return res;}
int main(){
	n=gi;for(int i=1;l[i]=gi,r[i]=gi,i<n;i++); 
	if(n==1){
		int x=l[1],y=r[1];
		if((x>=0&&y>=0)||(x<=0&&y<=0))printf("%d",abs(abs(x)-abs(y)));
		else printf("%d",
		((ll)abs(x)*abs(x)%p*fp(y-x,p-2)%p*(p+1)/2%p+(ll)abs(y)*abs(y)%p*fp(y-x,p-2)%p*(p+1)/2%p)%p);
	}
	return 0;
}

