#include<set>
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
#define M 801234
double sqr(double x){return x*x;}
struct circle{int x,y,r,w;}c[M];
struct edge{int to,nxt;}e[M];int cnt,lst[M],f[M],lb;
void ins(int a,int b){e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;}
int dfs(int v,int f=0){for(int i=lst[v];i;i=e[i].nxt)f+=dfs(e[i].to);return max(f,c[v].w);}
struct half{int n,d,x;half(){}half(bool d,int n):n(n),d(d),x(c[n].x+(d?-1:1)*c[n].r){}}a[M];
bool cmp(half a,half b){return a.x<b.x||(a.x==b.x&&a.d<b.d);}
struct line{
	int n,d;line(){}line(int n,bool d):n(n),d(d){}
	double y(){return c[n].y+(d?1:-1)*sqrt(sqr(c[n].r)-sqr(c[n].x-lb));}
	friend bool operator<(line a,line b){return a.y()<b.y();}
};
multiset<line>ms;
int main(){
	int n=gi;
	for(int i=1;i<=n;i++)c[i].x=gi,c[i].y=gi,c[i].r=gi,c[f[i]=i].w=gi;	
	for(int i=1;i<=n;i++)a[i]=half(1,i),a[i+n]=half(0,i);sort(a+1,a+n*2+1,cmp);
	for(int i=1;i<=n*2;i++){
		lb=a[i].x;
		if(a[i].d){
			set<line>::iterator it=ms.upper_bound(line(a[i].n,0));
			if (it!=ms.begin()) --it,f[a[i].n]=(*it).d?f[it->n]==it->n?a[i].n:f[it->n]:it->n;
            else f[a[i].n]=a[i].n;
            ms.insert(line(a[i].n,0));ms.insert(line(a[i].n,1)); 
		}else ms.erase(line(a[i].n,0)),ms.erase(line(a[i].n,1));
	}
	for(int i=1;i<=n;i++)if(f[i]!=i)ins(f[i],i);
	int ans=0;
	for(int i=1;i<=n;i++)if(f[i]==i)ans+=dfs(i);
	cout<<ans<<endl; 
	return 0;
}

