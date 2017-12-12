#include <bits/stdc++.h>

#define fir first
#define sec second
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

const int MaxN = 101234, MaxL = 17;

int n, m, dep[MaxN], u[MaxN], v[MaxN], f[MaxN][MaxL], lp[MaxN], rp[MaxN], cnt[MaxN], c[MaxN];
vector<int> e[MaxN], p[MaxN];

int in[MaxN], out[MaxN], dn;
void dfs(int x, int fa = 0) {
	f[x][0] = fa; in[x] = ++dn;
	for(int i = 1; i < MaxL; i++) f[x][i] = f[f[x][i - 1]][i - 1];
	for(auto y : e[x]) {
		if(y == fa) continue;
		dep[y] = dep[x] + 1;
		dfs(y, x);
	}
	out[x] = dn;
} 

void dfs2(int x, int fa = 0) {
	cnt[x] += cnt[fa];
	for(auto y : e[x]) {
		if(y != fa)
			dfs2(y, x);
	}
}

int lca(int x, int y, int i) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = MaxL - 1, K = dep[x] - dep[y]; ~i; i--)
		if(K >> i & 1) x = f[x][i];
	if(x == y) 
		return y;
	for(int i = MaxL - 1; ~i; i--)
		if(f[x][i] != f[y][i])
			x = f[x][i], y = f[y][i];
	return f[x][0];
}

int main() {
	int i;
	n = read(); m = read();
	for(i = 1; i < n; i++) {
		int a = read(), b = read();
		e[a].push_back(b); 
	}
	dfs(1);
	for(i = 1; i <= m; i++) {
		u[i] = read(); v[i] = read();
		int w = lca(u[i], v[i], i); cnt[w]++;
		p[w].push_back(i);
	}
	dfs2(1);
	for(i = 1; i <= n; i++) {
		if(!p[i].size()) continue;
		sort(p[i].begin(), p[i].end(), [&] (int x, int y) {return dep[x] > dep[y];});
		for(int j = 0; j + 1 < p[i].size(); j++) {
			int x = p[i][j], y = p[i][j + 1];
			if(dep[v[x]] < dep[v[y]]) return puts("No 1"), 0;
			if(!(in[y] <= in[x] && in[x] <= out[y])) return puts("No 2"), 0; 
		}
		if(cnt[u[p[i][0]]] != cnt[f[i][0]] || cnt[v[p[i][0]]] != cnt[f[i][0]]) return puts("No 3"), 0;
	}
	puts("Yes");
	return 0;
}

