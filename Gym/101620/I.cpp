#include <bits/stdc++.h>

#define fir first
#define sec second
#define MP make_pair
#define PB push_back

using namespace std;
typedef long long LL;
typedef unsigned long long u64;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int read() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 1501234;

int n, q, a[MaxN];

const int M = 262144;
struct info {
	int u, d;
	info() {u = 0, d = INT_MAX; } info(int d, int u) : u(u), d(d) {}
	info operator + (info b) {
		return info(min(d, b.d), max(u, b.u));
	}
}seg[M << 1];

void clear() {
	for(int i = 1; i < M + M; i++)
		seg[i] = info();
}

void modify(int p, info v) { 
	seg[p += M] = v;
	for(p >>= 1; p; p >>= 1)
		seg[p] = seg[p << 1] + seg[p << 1 | 1]; 
}

info Max(int l, int r) {
	info ans; 
	for(l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
		if(~l & 1) ans = ans + seg[l ^ 1];
		if(r & 1) ans = ans + seg[r ^ 1];
	}
	return ans;
} 

vector<int> e[MaxN], g[MaxN];
int lc[MaxN], rc[MaxN], segn, seg_rot;

void build(int &p, int l, int r) {
	if(!p) p = ++segn;
	if(l == r) {
		e[p].PB(l);
		return;
	}
	build(lc[p], l, l + r >> 1);
	build(rc[p], (l + r >> 1) + 1, r);
	e[p].PB(lc[p]); e[p].PB(rc[p]);
}

void addEdge(int p, int l, int r, int a, int b, int c) {
	if(a > r || b < l) return;
	if(a <= l && r <= b) {
		e[c].PB(p);
		return;
	}
	addEdge(lc[p], l, l + r >> 1, a, b, c);
	addEdge(rc[p], (l + r >> 1) + 1, r, a, b, c);
}

int bL[MaxN], bR[MaxN], bel[MaxN], dfn[MaxN], low[MaxN], s[MaxN], ins[MaxN], deg[MaxN], ind, sn, scc;

void dfs(int x) {
	dfn[x] = low[x] = ++ind;
	ins[s[++sn] = x] = 1;
	for(auto y : e[x]) 
		if(!dfn[y])
		 	dfs(y), cmin(low[x], low[y]);
		else
			if(ins[y])
				cmin(low[x], dfn[y]);
	if(dfn[x] == low[x]) {
		++scc;
		int cur = -1;
		while(cur != x && sn) {
			ins[cur = s[sn--]] = 0;
			bel[cur] = scc;
		}
	}
}

queue<int> Q;

int main() {
	int i;
	n = read(); segn = n - 1;
	for(i = 1; i <= n; i++) a[i] = read(), modify(a[i], info(i, i));
	build(seg_rot, 1, n - 1);
	for(i = 1; i < n; i++) {
		int l = a[i], r = a[i + 1]; if(l > r) swap(l, r);
		info c = Max(l, r);
		addEdge(seg_rot, 1, n - 1, c.d, c.u - 1, i);
	}
	for(i = 1; i <= segn; i++) if(!dfn[i]) dfs(i);
	for(i = 1; i < n; i++) if(!bL[bel[i]]) bL[bel[i]] = i;
	for(i = n - 1; i; i--) if(!bR[bel[i]]) bR[bel[i]] = i;
	for(i = 1; i <= scc; i++) if(!bL[i]) bL[i] = n;
	for(i = 1; i <= segn; i++) 
		for(auto j : e[i])
			if(bel[i] != bel[j])
				g[bel[j]].PB(bel[i]), deg[bel[i]]++;
				
	for(i = 1; i <= scc; i++)
		if(!deg[i]) Q.push(i);
	while(!Q.empty()) {
		int x = Q.front(); Q.pop(); 
		for(auto y : g[x]) {
			cmin(bL[y], bL[x]);
			cmax(bR[y], bR[x]);
			if(!--deg[y]) 
				Q.push(y);
		}
	}
	
	clear();
	for(i = 1; i < n; i++) modify(i, info(bL[bel[i]], bR[bel[i]]));
	q = read();
	while(q--) {
		int l = read(), r = read();
		if(l == r) printf("%d %d\n", l, r);
		else {
			info c = Max(l, r - 1);
			printf("%d %d\n", c.d, c.u + 1);
		}
	}
	return 0;
}

