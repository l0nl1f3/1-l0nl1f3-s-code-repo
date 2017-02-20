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
#define N 54321
#define M 101234
int n,m,k,ans,f[N];
struct edge{int a,b,c,d,e;}e[M];
bool cmp(edge a,edge b){return a.c<b.c||(a.c==b.c&&a.d>b.d);}
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
int chk(int x){
	for(int i=1;f[i]=i,i<n;i++);
	for(int i=1;i<=m;i++)e[i].c=e[i].e+x*e[i].d;
	sort(e+1,e+m+1,cmp);
	int ser=0,res=0;
	for(int i=1,x,y;i<=m;i++){
		x=find(e[i].a);y=find(e[i].b);
		if(x!=y)f[x]=y,ser+=e[i].d,res+=e[i].c;
	}
	return ser>=k?ans=res-k*x,1:0;
}
int main(){
	n=gi;m=gi;k=gi;
	for(int i=1;i<=m;i++)e[i].a=gi+1,e[i].b=gi+1,e[i].e=gi,e[i].d=!gi; 
	for(int l=-123,r=123,mid;l<=r;chk(mid=(l+r)/2)?l=mid+1:r=mid-1);
	printf("%d\n",ans); 
	return 0;
}

