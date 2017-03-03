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
int main(){
	FO(unlock);	
	T=gi;
	while(T--){
		n=gi;k=gi;
		for(int i=1;i<=n;i++)p[i]=gi;
		P=q=0;dfs(1);
		printf("%.10lf\n",1.0*P/q);
	}

	return 0;
}

