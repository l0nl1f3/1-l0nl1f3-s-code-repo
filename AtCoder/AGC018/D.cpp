#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;
typedef long long LL;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int inp() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 101234, MaxM = 201234;

struct edge{
	int to, nxt, v;
}e[MaxM]; int cnt, lst[MaxN];
void ins(int a, int b, int c){
	e[++cnt] = (edge){b, lst[a], c}; lst[a] = cnt;
}
void lnk(int a, int b, int c){
	ins(a, b, c);
	ins(b, a, c);
}

LL ans;
int n, siz[MaxN], f[MaxN], hug[MaxN], c1, c2, G;
void dfs(int x, int fa){
	siz[x] = 1;
	for(int i = lst[x], b; b = e[i].to, i; i = e[i].nxt){
		if(b == fa) continue;
		dfs(b, x);
		siz[x] += siz[b];
		ans += ((LL) e[i].v * min(siz[b], n - siz[b])) << 1;
		cmax(hug[x], siz[b]);	
	}
	cmax(hug[x], n - siz[x]);
	cmin(G, hug[x]);
} 
int main() {
	int i; 
	n = G = inp();
	for(i = 1; i < n; i++){
		int u = inp(), v = inp(), w = inp();
		lnk(u, v, w);
	}
	
	dfs(1, 0);
	for(i = 1; i <= n; i++)
		if(hug[i] == G)
			if(c1) c2 = i; else c1 = i;
	if(c2){
		for(i = lst[c1]; i; i = e[i].nxt) if(e[i].to == c2)
			ans -= e[i].v;
	}
	else{
		int mn = ~0U >> 1;
		for(i = lst[c1]; i; i = e[i].nxt) cmin(mn, e[i].v);
		ans -= mn;
	}
	cout << ans;
	return 0;
}



