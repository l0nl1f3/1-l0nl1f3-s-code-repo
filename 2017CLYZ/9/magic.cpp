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
int n,p,pn,phi=1,a[N],pr[N],b[N];
int pow(int a,int n,int p){int ans=1;for(;n;n>>=1,a=((ll)a*a)%p)if(n&1)ans=(ll)ans*a%p;return ans;}
int insert(int x,int d=1){for(int i=1;i<=pn;i++)while(x%pr[i]==0&&x){b[i]+=d,x/=pr[i];}

return x;}
int main(){
	n=gi;p=gi;for(int i=1;i<=n;i++)a[i]=gi;
	int qaq=p;
	for(int i=2;i*i<=qaq;i++){
		if(qaq%i==0){
			qaq/=(pr[++pn]=i);phi*=(i-1);
			while(qaq%i==0)phi*=i,qaq/=i;
		}
	}
	if(qaq>1)phi*=((pr[++pn]=qaq)-1);
	int ans=0,C=1;
	for(int i=1;i<=n;i++){
		int t=C;
		for(int j=1;j<=pn;j++)t=t*(ll)pow(pr[j],b[j],p)%p;
		ans=(ans+a[i]*(ll)t)%p;
		C=C*(ll)insert(n-i)%p*pow(insert(i,-1),phi-1,p)%p;
	}
	cout<<ans;
	return 0;
}

