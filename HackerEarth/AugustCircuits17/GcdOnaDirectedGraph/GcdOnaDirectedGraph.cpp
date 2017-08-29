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

const int MaxN = 101234;

int n, m, c[MaxN];

vector <int> e[MaxN];
int dfn[MaxN], low[MaxN], ins[MaxN], s[MaxN], bel[MaxN], sn, dn, scc; 

void clear() {
	for(int i = 0; i < MaxN; i++) e[i].clear();
	memset(low, 0, sizeof(low));
	memset(dfn, 0, sizeof(dfn)); 
	memset(ins, 0, sizeof(ins));
	scc = sn = 0;
}

void dfs(int x) {
	dfn[x] = low[x] = ++dn;
	ins[s[++sn] = x] = 1;
	for(int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if(!dfn[y]) {
			dfs(y); cmin(low[x], low[y]);
		}else if(ins[y])
			cmin(low[x], dfn[y]);
	} 
	int z = -1;
	if(dfn[x] == low[x]) {
		++scc;
		while(z != x && sn) {
			ins[z = s[sn--]] = 0;
			bel[z] = scc;
		}
	}
}

vector<pair<int, int> > vp;
int g[MaxN]; vector<int> t[MaxN], a;
int deg[MaxN], ord[MaxN], pc, siz[MaxN];

typedef unsigned long long uLL;

uLL F[MaxN], f[MaxN];
uLL get(int d) {
	int i;
	a.clear();
	for(i = d; i < MaxN; i += d)
		for(auto x : t[i]) 
			a.emplace_back(x);

	sort(a.begin(), a.end());
	
	for(auto x : a) F[x] = 1;
	uLL ans = 0;
	for(i = a.size() - 1; ~i; i--) {
		int x = a[i];
		ans += F[x];
		for(auto y : e[x])
			if(g[y] % d == 0)
				F[y] += F[x];
	}
	
	return ans;
} 
int main() {
	int i, j;
	scanf("%d %d", &n, &m);
	for(i = 1; i <= n; i++) scanf("%d", c + i);
	for(i = 1; i <= m; i++) {
		int u, v; 
		scanf("%d %d", &u, &v);
		e[u].emplace_back(v);
	}
	for(i = 1; i <= n; i++) if(!dfn[i]) dfs(i);
	for(i = 1; i <= n; i++) {
		int p = bel[i];
		siz[p] ++;
		g[p] = g[p] ? __gcd(g[p], c[i]) : c[i];
		for(auto j : e[i])
			if(bel[j] != p) vp.emplace_back(p, bel[j]);
	}
	
	n = scc;
	for(i = 1; i <= n; i++) t[g[i]].emplace_back(i);
	for(i = 1; i <= n; i++) e[i].clear(); 
	for(auto i : vp) {
		int u = i.fir, v = i.sec;
		e[u].emplace_back(v);
	}
	for(i = 1; i < MaxN; i++) f[i] = get(i);
	for(i = MaxN - 1; i; i--)
		for(j = i + i; j < MaxN; j += i) 
			f[i] -= f[j];
	for(i = 1; i < MaxN; i++) if(f[i]) return printf("%d ", i), 0;
	return 0;
}



