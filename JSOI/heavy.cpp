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
const int N=3e4+10;
int n,m,fa[N],L[N],R[N],pre[N],ch[N][2],w[N],s[N];
bool rev[N];
int gd(int o) {return ch[pre[o]][1]==o;}
void lk(int x,int y,int d) {
    if (x) pre[x]=y;
    if (y) ch[y][d]=x;
}
bool rt(int o) {return ch[pre[o]][gd(o)]!=o;}
void mkr(int o) {if (o) std::swap(ch[o][1], ch[o][0]), rev[o] ^= 1;}
void down(int o) {
	//if (rev[o]) mkr(ch[o][0]), mkr(ch[o][1]), rev[o] = 0;
	
}

inline void rot(int o) {
	
    int x=pre[o],d=gd(o);
    pre[o]=pre[x];
    if (!rt(x)) ch[pre[x]][gd(x)]=o;
    lk(ch[o][d^1],x,d);
    lk(x,o,d^1);
    up(x),up(o);
}
void clear(int o) {
    if(!rt(o)) 
		clear(pre[o]);
    down(o);
}
inline void splay(int o) {
    for(clear(o);!rt(o);rot(o))
        if (!rt(pre[o])) rot(gd(o)==gd(pre[o])?pre[o]:o);
}
inline void access(int o) {
    for (int x = 0; o; o = pre[x = o])
        splay(o), ch[o][1] = x, up(o);
}
int main(){


	return 0;
}

