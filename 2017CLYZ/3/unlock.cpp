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
#define N 333
int T,n,k,p[N];
int a[N],b[N],cnt;
int P,q;
void unlock(int q){for(int x=q;!b[x];x=p[x])b[x]=1;}
void orz(){
	//for(int i=1;i<=k;i++)printf("%d ",a[i]);
	memset(b,0,sizeof(b));cnt=0;
	for(int i=1;i<=k;i++)unlock(a[i]);
	for(int i=1;i<=n;i++)cnt+=b[i]==1;
	/*if(cnt==n)puts("YES"); 
	else puts("");*/
	P+=(cnt==n);
}
void dfs(int p){
	if(p>k){
		++q;orz();return;
	}
	for(int i=a[p-1]+1;i<=n;i++){
		a[p]=i;
		dfs(p+1);
	}
}
int t,siz[N];double c[N][N],f[N][N];
void dfs1(int x){
	b[x]=1;siz[t]++;
	if(b[p[x]])return;
	dfs1(p[x]);
}
int main(){
	FO(unlock);	
	T=gi;
	c[0][0]=1;
	for(int i=1;i<=300;i++){
		c[i][0]=1;		
		for(int j=0;j<=300;j++)
			c[i][j]=c[i-1][j]+c[i-1][j-1];
	}
	while(T--){
		n=gi;k=gi;t=0;
		memset(b,0,sizeof(b));
		memset(f,0,sizeof(f));
		memset(siz,0,sizeof(siz));
		for(int i=1;i<=n;i++)p[i]=gi;
		for(int i=1;i<=n;i++)if(!b[i])++t,dfs1(i);
		f[0][0]=1;
		for(int i=1,m=0;i<=t;i++){
			m+=siz[i];
			for(int j=1;j<=m;j++){
				for(int l=1;l<=min(j,siz[i]);l++){
					f[i][j]=f[i][j]+f[i-1][j-l]*c[siz[i]][l];
				}
//				cout<<i<<','<<f[i][j]<<endl;
			}
		}	
		cout<<f[t][k]/c[n][k]<<endl;
	} 
	return 0;
}

