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
#define N 301
#define M N*N
int n,m,cnt,lst[N],f[N][N],g[N][N];
struct edge{int to,nxt,v;}e[M]; 
void ins(int a,int b,int c){e[++cnt]=(edge){b,lst[a],c};lst[a]=cnt;} 
int main(){
	memset(f,0x3f,sizeof(f));
	n=gi;m=gi;
	for(int i=1,a,b;i<=m;i++)a=gi,b=gi,ins(a,b,gi);
	for(int i=1;i<=n;i++)f[i][i]=0;
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)g[i][j]=f[i][j];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				for(int t=lst[j],b;b=e[t].to,t;t=e[t].nxt)gmin(g[i][b],f[i][j]+e[t].v);
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)f[i][j]=g[i][j];
		for(int i=1;i<=n;i++)if(f[i][i]<0)return printf("%d",k),0;
	}
	return puts("0"),0;
}

