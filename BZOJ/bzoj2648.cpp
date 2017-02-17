//这题卡常，假装过了。 
//然后其实过了bzoj2716 
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
/*
char B[1<<25],*S=B;int F(){for(;*S<'-';S++);register int x=*S++-'0';for(;*S>='0';x=(x<<3)+(x<<1)+*S++-'0');return x;}
char U[1<<25],*O=U,stk[20];
#define PuT(b) register int i=0;for(;b;stk[++i]=x%10+'0',x/=10);for(;i;*O++=stk[i--]);
void pri(register int x){if(!x)*O++='0';else{PuT(x)};}
void pr9(register int x){PuT(i<9);}
#define MoD 1000000000
#define pr(x,c) (x<0?*O++='-',x=-x:1,x>=MoD?pri(x/MoD),pr9(x%MoD):pri(x),*O++=c)*/
il int read(){bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;}
#define gi read()
#define K 2
#define N 1001234
int D;
struct KDnode{int d[K],s[K],x[K],y[K];};
struct Point {int d[K];bool operator<(const Point &a)const{return d[D]<a.d[D];}}a[N];
struct KDtree{
	#define NE nth_element
	#define ls t[o].s[0]
	#define rs t[o].s[1]
	KDnode t[N];int rt,cnt;
	void MT(int f,int x){//maintain node x by node x
		gmin(t[f].x[0],t[x].x[0]),gmax(t[f].x[1],t[x].x[1]);
		gmin(t[f].y[0],t[x].y[0]),gmax(t[f].y[1],t[x].y[1]);
	}
	int BT(int l,int r,int d){//in range [l,r],cut by d-th dimension
		D=d;int o=(l+r)/2;
		NE(a+l,a+o,a+r+1);
		t[o].d[0]=t[o].x[0]=t[o].x[1]=a[o].d[0];
		t[o].d[1]=t[o].y[0]=t[o].y[1]=a[o].d[1];
		if(l<o)ls=BT(l,o-1,d^1),MT(o,ls);
		if(o<r)rs=BT(o+1,r,d^1),MT(o,rs);
		return o;
	}
	void build(int n){rt=BT(1,n,0);} 
	inline void insert(int x,int y){
		++cnt;
		t[cnt].d[0]=t[cnt].x[0]=t[cnt].x[1]=x;
		t[cnt].d[1]=t[cnt].y[0]=t[cnt].y[1]=y;
		for(int p=rt,d=0;p;d^=1){
			cout<<"p="<<p<<endl;
			MT(p,cnt);int &nxt=t[p].s[t[cnt].d[d]>=t[p].d[d]];
			if(nxt==0){nxt=cnt;return;}else p=nxt;
		}
	}
	#define getm(p) max(t[p].x[0]-x,0)+max(x-t[p].x[1],0)\
		+max(t[p].y[0]-y,0)+max(y-t[p].y[1],0)
	int ans;
	int querym(int o,int x,int y){
		int tmp=abs(t[o].d[0]-x)+abs(t[o].d[1]-y),d[2];
		if(ls)d[0]=getm(ls);else d[0]=inf;
		if(rs)d[1]=getm(rs);else d[1]=inf;
		gmin(ans,tmp);tmp=d[0]>=d[1];
		if(d[tmp]<ans)querym(t[o].s[tmp],x,y);tmp^=1;
		if(d[tmp]<ans)querym(t[o].s[tmp],x,y);
	}
	inline int querym(int x,int y){
		ans=inf;querym(rt,x,y);return ans;
	}
	#undef ls
	#undef rs
	#undef NE 
}kdt;
int n,q;
int main(){
	FO(qaq);
	n=gi;q=gi;
	for(int i=1;i<=n;i++){a[i].d[0]=gi;a[i].d[1]=gi;}
	kdt.build(n);
	for(int o,x,y;q--;){
		o=gi;x=gi;y=gi;
		if(o==1)kdt.insert(x,y);
		else{
			int t=kdt.querym(x,y);
			printf("%d\n",t);
		} 
	}
	return 0;
}
