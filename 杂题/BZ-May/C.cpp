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
int n,x[SZ],y[SZ],mi=1e9,ma=-1;
ld w1,w2;
pair<ld,int> ps[SZ];
vector<ld> v1,v2;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",x+i,y+i);
	{
	//>=how many?
	int bu=0,bd=0;
	for(int i=2;i<=n;i++)
	{
		if(y[i]>y[1]) ++bu;
		if(y[i]>=y[1]) ++bd;
	}
	mi=min(mi,bu); ma=max(ma,bd);
	}
	{
	//>=how many?
	int bu=0,bd=0;
	for(int i=2;i<=n;i++)
	{
		if(x[i]>x[1]) ++bu;
		if(x[i]>=x[1]) ++bd;
	}
	mi=min(mi,bu); ma=max(ma,bd);
	}
	int du=0,dd=0;
	for(int i=2;i<=n;i++)
	{
		if(x[1]==x[i])
		{
			if(y[i]>y[1]) ++du;
			if(y[i]>=y[1]) ++dd;
		}
		else
			if(x[1]>x[i]) v1.pb((y[1]-y[i])/ld(x[1]-x[i]));
			else v2.pb((y[1]-y[i])/ld(x[1]-x[i]));
	}
	//<=x >=x
	sort(v1.begin(),v1.end());
	sort(v2.begin(),v2.end());
	for(int i=0;i<v1.size();i++)
	{
		if(v1[i]>0) continue;
		int cnt=i+1+v2.end()-lower_bound(v2.begin(),v2.end(),v1[i]);
		ma=max(ma,dd+cnt);
	}
	for(int i=0;i<v1.size();i++)
	{
		if(v1[i]>0) continue;
		int cnt=i+v2.end()-upper_bound(v2.begin(),v2.end(),v1[i]);
		mi=min(mi,du+cnt);
	}
	printf("%d %d\n",mi+1,ma+1);
}

