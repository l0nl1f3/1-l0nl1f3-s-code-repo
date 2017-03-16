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
#define Pii pair<int,ll>
#define max(a,b) ((a)>(b)?(a):(b))
#define gmax(a,b) (a)=max((a),(b))
#define gmin(a,b) (a)=min((a),(b))
#define infll 1001001001001001001LL
#define dbg(vari) cerr<<#vari<<" = "<<(vari)<<endl
#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
il int read(){bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;}
#define gi read()
#define N 1001234 
int n,k,eq,c[N],v[N];ll f[N];
void _01(){
	for(int i=1;i<=n;i++)for(int j=k;j>=c[i];j--)f[j]=max(f[j],f[j-c[i]]+v[i]);
	for(int i=1;i<=k;i++)printf("%lld ",f[i]=max(f[i],f[i-1]));
}
Pii p[N];int cnt,d[N],cc[N],vv[N]; 
void gdy(){
	for(int i=1;i<=n;i++)p[i]=mp(c[i],v[i]);
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++){
		if(p[i].fi!=p[i-1].se){
			++cnt;
			c[cnt]=p[i].fi;
			v[cnt]=1;
		}else v[cnt]++;
	} 
	n=cnt;cnt=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=v[i];j<<=1){
			v[i]-=j;
			cc[++cnt]=j*c[i];
			vv[cnt]=j*c[i];
		} 
		if(v[i]){
			cc[++cnt]=c[i]*v[i];
			vv[cnt]=c[i]*v[i];
		}
	} 
	n=cnt;
	for(int i=1;i<=n;i++)for(int j=k;j>=cc[i];j--)f[j]=max(f[j],f[j-cc[i]]+vv[i]);
	for(int i=1;i<=k;i++)printf("%lld ",f[i]=max(f[i],f[i-1]));
}
int main(){
	FO(jewelry);
	n=gi;k=gi;
	for(int i=1;i<=n;i++)c[i]=gi,v[i]=gi,eq=eq&&(c[i]==v[i]);
	if((ll)n*k<=1e8+28){
		_01();
	}else if(eq){
		gdy();
	}else puts("NanA");
	return 0;
}

