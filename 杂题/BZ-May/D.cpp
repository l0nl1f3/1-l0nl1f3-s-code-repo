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
int n,p[SZ];
ll bs[SZ],MOD=998244353,f[SZ];
int tg[SZ];
int ns=0;
ll sum(int x)
{
    ll ans=0;
    for(;x>=1;x-=x&-x)
    {
        if(tg[x]!=ns) bs[x]=0;
        ans=(ans+bs[x])%MOD;
    }
    return ans;
}
void edt(int x,ll y)
{
    for(;x<=n;x+=x&-x)
    {
        if(tg[x]!=ns) bs[x]=0;
        bs[x]=(bs[x]+y)%MOD;
        tg[x]=ns;
    }
}
int tf[SZ];
ll& gf(int x)
{
    if(tf[x]!=ns) f[x]=0;
    tf[x]=ns; return f[x];
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",p+i); p[0]=1;
    f[0]=1; edt(p[0],1);
    for(int i=2;i<=n;i++)
    {
        ll qwq=sum(p[i]);
        if(p[i-1]>p[i]) ns=i;
        ll&p=gf(i-1);
        p=(p+qwq)%MOD;
        edt(::p[i-1],qwq);
    }
    ll ans=sum(n)*2;
    ans=(ans%MOD+MOD)%MOD;
    printf("%d\n",int(ans));
}
