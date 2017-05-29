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
int n,k,a[SZ],b[SZ];
ll f[2203][2203];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++)
		scanf("%d",a+i);
	for(int i=0;i<n;i++)
		scanf("%d",b+i);
	memset(f,127/3,sizeof f);
	f[0][0]=0;
	for(int i=0;i<n;i++)
	{
		for(int j=n;j>=0;--j)
		{
			for(int k=n-j;k>=0;--k)
			{
				#define gmin(a,b) ((a)>(b))?((a)=(b)):0
				gmin(f[j+1][k],f[j][k+1]+b[i]);
				gmin(f[j+1][k],f[j][k]+a[i]+b[i]);
				gmin(f[j][k+1],f[j][k]+a[i]);
			}
		}
	}
	printf("%lld\n",f[k][0]);
}
