//‘≤»¶”Œœ∑£¨…®√Ëœﬂ£¨multiset 
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
#define N 201234
int n,lb;
struct Circle{int x_r,y_r,r,w;}c[N];
struct ScanLine{
	int n,d;
	int x(){return c[n].x_r+(d?-1:1)*c[n].r;}
	int y(){return c[n].y_r+(d?1:-1)*sqrt(c[n].r*c[n].r-(c[n].x_r-lb)*(c[n].x_r-lb));}
	ScanLine operator <(ScanLine b){
		
	}
}L[N],H[N];
multiset<ScanLine>s;
typedef multiset<ScanLine>::iterator Mi;
bool cmp_r(Circle a,Circle b){return a.r<b.r;}
bool cmp_x(ScanLine a,ScanLine b){return a.x()<b.x()||(a.x()==b.x()&&a.d<b.d);}
bool cmp_y(ScanLine a,ScanLine b){return a.y()<b.y();}
struct edge{int to,nxt;}e[N*2];int cnt,lst[N];
void ins(int a,int b){
	//cout<<a<<" -> "<<b<<endl;
	e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;
}
int dfs(int x){
	int sum=0;
	for(int i=lst[x],b;b=e[i].to,i;i=e[i].nxt)sum+=dfs(b);
	return max(c[x].w,sum);
}
int f[N];
int getans(){
	int ans=0;
	for(int i=1;i<=n;i++)if(f[i]==i)ans+=dfs(i);
	return ans; 
}
void bruteforce(){
	sort(c+1,c+n+1,cmp_r); 
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			int d=(c[j].x_r-c[i].x_r)*(c[j].x_r-c[i].x_r)+(c[j].y_r-c[i].y_r)*(c[j].y_r-c[i].y_r);
			if(d>(c[j].r-c[i].r)*(c[j].r-c[i].r))continue;
			if(f[i]==i||c[f[i]].r>c[j].r)f[i]=j;
		} 
	int rt;
	for(int i=1;i<=n;i++)if(f[i]!=i)ins(f[i],i);else rt=i;
	cout<<getans();
}
int main(){
	FO(circle);
	n=gi;
	for(int i=1;i<=n;i++){
		c[i].x_r=gi;c[i].y_r=gi;c[i].r=gi;c[i].w=gi;
		L[i]=(ScanLine){i,0};		 
		L[i+n]=(ScanLine){i,1};
	}
	sort(L+1,L+n*2+1,cmp);
	if(n<=5000){
		bruteforce();
	}else SaoMiaoXian();
	return 0;		
}

