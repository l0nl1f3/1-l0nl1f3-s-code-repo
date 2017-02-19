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
#define M 2333
int n,m,f[M];
struct edge{
	int a,b,c;double v;
	bool operator <(edge b)const{return v<b.v;}
}e[M];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
double fst(){
	for(int i=1;f[i]=i,i<n;i++);
	double ans=0;
	for(int i=1,x,y;i<=m;i++){
		x=find(e[i].a);y=find(e[i].b);
		if(x!=y)f[x]=y,ans+=e[i].v;
	}
	return ans;
}
int main(){
	n=gi;m=gi;
	for(int i=1;i<=m;i++)e[i].a=gi,e[i].b=gi,e[i].v=e[i].c=gi;
	int lb,ub;double ans=(1e233);
	sort(e+1,e+m+1);lb=fst();
	reverse(e+1,e+m+1);ub=fst();
	for(double i=lb,av;i<=ub;i++){
		av=i/(n-1);
		for(int i=1;i<=m;i++)e[i].v=(e[i].c-av)*(e[i].c-av);
		sort(e+1,e+m+1);
		gmin(ans,fst());
	}
	printf("%.4lf\n",sqrt(ans/(n-1)));
	return 0;
}

