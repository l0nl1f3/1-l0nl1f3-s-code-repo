#include<ctime>
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
#define M 501234
#define N 101234
struct edge{int to,nxt,v;}e[M];int cnt=1,lst[N];
void ins(int a,int b,int c){e[++cnt]=(edge){b,lst[a],c};lst[a]=cnt;}
void lnk(int a,int b,int c){ins(a,b,c);ins(b,a,c);}
int n,m,k,tag[M],inq[M],vis[M];
int a[M],b[M],c[M],pre[M],prv[M],dis[N];
int main(){
	FO(shortest8);
	n=gi;m=gi;k=gi;
	for(int i=1;i<=m;i++){
		a[i]=gi;b[i]=gi;c[i]=gi;
	}
	for(int i=1;i<=m;i++)if(b[i]-a[i]!=1)cout<<i<<endl; 
}

