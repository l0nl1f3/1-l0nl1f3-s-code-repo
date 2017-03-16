#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <bitset>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <sstream>
#include <stack>
#include <iomanip>
using namespace std;
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
typedef long long ll;
typedef double ld;
typedef vector<int> vi;
#define fi first
#define se second
#define fe first
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
#define Edg int M=0,fst[SZ],vb[SZ],nxt[SZ];void ad_de(int a,int b){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;}void adde(int a,int b){ad_de(a,b);ad_de(b,a);}
#define Edgc int M=0,fst[SZ],vb[SZ],nxt[SZ],vc[SZ];void ad_de(int a,int b,int c){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;vc[M]=c;}void adde(int a,int b,int c){ad_de(a,b,c);ad_de(b,a,c);}
#define es(x,e) (int e=fst[x];e;e=nxt[e])
#define esb(x,e,b) (int e=fst[x],b=vb[e];e;e=nxt[e],b=vb[e])
#define VIZ {printf("digraph G{\n"); for(int i=1;i<=n;i++) for es(i,e) printf("%d->%d;\n",i,vb[e]); puts("}");}
#define VIZ2 {printf("graph G{\n"); for(int i=1;i<=n;i++) for es(i,e) if(vb[e]>=i)printf("%d--%d;\n",i,vb[e]); puts("}");}
#define SZ 666666
int sol(int x,int y)
{
	if(x<0) x*=-1;
	if(y<0) y*=-1;
	if(x==0&&y==0) return 0;
	if(x>y) swap(x,y);
	if(y==0) throw "wtf";
	//x<=y,x>=0,y>0
	if(x+y==1) return 3;
	if(x*2<=y) //case1
	{
		const int bg[]={1,2,3,2},kk[]={1,-1,-1,1};
		int pr=(y-1)/4,zq=(y-1)%4;
		int yy=bg[zq]+pr*2;
		if(x%2==1) yy+=kk[zq];
		return yy;
	}
	else
	{
		const int cn[]={0,3,2,1,4},dt[]={3,2,3,4,3,4};
		int xy=x+y;
		if(xy<=4) return cn[xy];
		int pr=(xy-5)/6,zq=(xy-5)%6;
		return pr*2+dt[zq];
	}
}
int main()
{
	FO(jump)
	int T,x,y;
	cin>>T;
	while(T--)
	{
		cin>>x>>y;
		cout<<sol(x,y)<<"\n";
	}
}

