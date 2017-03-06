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
#define pyz 1000000007
#define K 2333
#define N 201234
int n,m,k,s,a[K];
Pii p[K];
int x[K],y[K]; 
int pw(int a,int n){
	int res=1;
	for(;n;n>>=1,a=((ll)a*a)%pyz)if(n&1)res=((ll)res*a)%pyz;
	return res;
}
int f[N],r[N],g[K][K],o;
int C(int i,int j){return f[i]*(ll)r[j]%pyz*r[i-j]%pyz;}
int main(){
	FO(rover);
	n=gi;m=gi;k=gi;s=gi;
	a[0]=s;for(int i=1;s!=1;i++)a[i]=(s=(s+1)/2),o=i; 
	f[0]=r[0]=1;for(int i=1;i<=n+m;i++)f[i]=(ll)f[i-1]*i%pyz;
	r[n+m]=pw(f[n+m],pyz-2);
	for(int i=m+n-1;i;i--)r[i]=(r[i+1]*(ll)(i+1))%pyz;
	for(int i=1;i<=k;i++)p[i].fi=gi,p[i].se=gi;p[0].fi=p[0].se=1;
	sort(p,p+k+1);
	for(int i=0;i<=k;i++)x[i]=p[i].fi,y[i]=p[i].se;
	for(int i=k;~i;i--){
		for(int j=0;j<o;j++){
			g[i][j]=C(n+m-x[i]-y[i],n-x[i]);
			for(int l=k;l>i;l--){
				if(y[l]>=y[i]){
					g[i][j]=(g[i][j]-(ll)g[l][j]*C(x[l]-x[i]+y[l]-y[i],x[l]-x[i]))%pyz;
					if(g[i][j]<=0)g[i][j]+=pyz;
				}
			}
		}
		g[i][o]=C(n+m-x[i]-y[i],n-x[i]);
        for (int j=o;j>=1;j--){
			g[i][j]=(g[i][j]-g[i][j-1])%pyz;
        	if(g[i][j]<=0)g[i][j]+=pyz; 
		}
	}
	int ans=0;
	for(int i=0;i<=o;i++)ans=(ans+g[0][i]*(ll)a[i])%pyz;
	cout<<ans*(ll)pw(C(n-1+m-1,n-1),pyz-2)%pyz; 
	return 0;
}

