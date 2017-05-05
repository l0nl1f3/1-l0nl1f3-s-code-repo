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
int T,n,s;
int E=0;
typedef pair<int,pii> edg;
edg es[1000009];
int ff[1000009];
int gf(int x)
{
    return ff[x]?ff[x]=gf(ff[x]):x;
}
ll fa(int n)
{
    for(int i=1;i<=n;i++) ff[i]=0;
    int x=s; E=0;
    for(int i = 2; i <= n; i++){
    x = x * 907 % 2333333;
    int T = x;
    for(int j = max(1, i-5); j <= i-1; j++){
    x = x * 907 % 2333333;
    int w = T ^ x;
    es[++E]=edg(w,pii(i,j));
    }
    }
    sort(es+1,es+1+E); ll ans=0;
    for(int i=1;i<=E;i++)
    {
        int ga=gf(es[i].se.fi),gb=gf(es[i].se.se);
        if(ga^gb) ff[ga]=gb, ans+=es[i].fi;
    }
    return ans;
}
ll qwq[SZ];
void sol()
{
    map<int,int> app;
    scanf("%d%d",&n,&s);
    if(n<=100)
    {
        printf("%lld\n",fa(n));
        return;
    }
    for(int i=1;i<=300;i++)
        qwq[i]=fa(i);
    int l;
    for(int i=1;i<=100;i++)
    {
        bool gg=1; ll k=qwq[100+i]-qwq[100];
        for(int j=100;j+i<=300;j++)
            if(qwq[j+i]-qwq[j]!=k) gg=0;
        if(gg)
        {
            l=i; break;
        }
    }
    int p=n%l+l;
    while(p<=30) p+=l;
    int t=(n-p)/l;
    ll fb=fa(p+l)-fa(p); fb*=t;
    fb+=fa(p); printf("%lld\n",fb);
}
int main()
{
    scanf("%d",&T);
    while(T--) sol();
}
