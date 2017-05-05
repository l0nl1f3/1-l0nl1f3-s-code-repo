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
inline ld ga(ld a,ld b,ld c,ld x1,ld y1,ld x2,ld y2)
{
    ld minn=1e18;
    {
    ld dy=fabs(y1-y2);
    ld dx=x1+x2+c;
    minn=min(minn,dx*dx+dy*dy);
    }
    {
    ld dy=fabs(y1-y2);
    ld dx=a-x1+a-x2+c;
    minn=min(minn,dx*dx+dy*dy);
    }
    {
    ld dy=fabs(x1-x2);
    ld dx=y1+y2+c;
    minn=min(minn,dx*dx+dy*dy);
    }
    {
    ld dy=fabs(x1-x2);
    ld dx=b-y1+b-y2+c;
    minn=min(minn,dx*dx+dy*dy);
    }
    minn=sqrt(minn);
    return minn;
}
ld sol(ld a,ld b,ld c)
{
    ld ans=0,lans=0;
    for(int i=1;i<=15000;i++)
    {
    ld x1=rand()/ld(RAND_MAX)*a;
    ld y1=rand()/ld(RAND_MAX)*b;
    ld x2=rand()/ld(RAND_MAX)*a;
    ld y2=rand()/ld(RAND_MAX)*b;
    ld g=min(a,b);
    ld eps=1e-8;
    while(g>1e-10)
    {
    g*=0.96; 
    ld g1=x1+eps,h1=y1+eps;
    ld g2=x2+eps,h2=y2+eps;
    ld ra=ga(a,b,c,x1,y1,x2,y2);
    ld d1=ga(a,b,c,g1,y1,x2,y2)-ga(a,b,c,x1,y1,x2,y2);
    ld d2=ga(a,b,c,x1,h1,x2,y2)-ga(a,b,c,x1,y1,x2,y2);
    ld d3=ga(a,b,c,x1,y1,g2,y2)-ga(a,b,c,x1,y1,x2,y2);
    ld d4=ga(a,b,c,x1,y1,x2,h2)-ga(a,b,c,x1,y1,x2,y2);
    ld tl=sqrt(d1*d1+d2*d2);
    ld rl=sqrt(d3*d3+d4*d4);
    d1=d1/tl*g; d2=d2/tl*g; d3=d3/rl*g; d4=d4/rl*g;
    x1+=d1; y1+=d2; x2+=d3; y2+=d4;
    if(x1<0) x1=0; if(x1>a) x1=a;
    if(x2<0) x2=0; if(x2>a) x2=a;
    if(y1<0) y1=0; if(y1>b) y1=b;
    if(y2<0) y2=0; if(y2>b) y2=b;
    }
    lans=ans;
    ans=max(ans,ga(a,b,c,x1,y1,x2,y2));
    }
    return ans;
}
int main()
{
    srand(19260817);
    ld a,b,c;
    cin>>a>>b>>c;
    ld len=sqrt(a*(ld)a+b*(ld)b+c*(ld)c);
    a/=len; b/=len; c/=len;
    printf("%.10lf\n",len*double(max(sol(a,b,c),
    max(sol(a,c,b),sol(b,c,a)))));
}
