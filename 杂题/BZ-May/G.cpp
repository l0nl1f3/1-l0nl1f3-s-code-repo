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
int n,u[SZ],d[SZ];
ll f[SZ][2];
int main()
{
    memset(f,127/3,sizeof(f)); f[1][1]=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",u+i);
    for(int i=1;i<=n;i++) scanf("%d",d+i);
    for(int i=1;i<=n;i++)
    {
        if(i>1&&(d[i-1]>=u[i]||u[i-1]<=d[i]));else
        {
        if(i>1&&u[i-1]<=u[i]) f[i][0]=min(f[i][0],f[i-1][0]);
        if(i>1&&d[i-1]>=d[i]) f[i][1]=min(f[i][1],f[i-1][1]);
        }
        f[i][0]=min(f[i][0],f[i][1]+u[i]-d[i]);
        f[i][1]=min(f[i][1],f[i][0]+u[i]-d[i]);
        f[i][0]=min(f[i][0],f[i][1]+u[i]-d[i]);
        if(i>1&&(d[i-1]>=u[i]||u[i-1]<=d[i]));else
        {
        if(i>1&&u[i-1]<=u[i]) f[i][0]=min(f[i][0],f[i-1][0]);
        if(i>1&&d[i-1]>=d[i]) f[i][1]=min(f[i][1],f[i-1][1]);
        }
        f[i][0]=min(f[i][0],f[i][1]+u[i]-d[i]);
        f[i][1]=min(f[i][1],f[i][0]+u[i]-d[i]);
        f[i][0]=min(f[i][0],f[i][1]+u[i]-d[i]);
    }
    ll ans=f[n][1];
    if(ans>=1e16) puts("-1");
    else printf("%lld\n",ans);
}
