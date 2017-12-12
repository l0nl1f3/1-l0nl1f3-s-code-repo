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

int n, m, dep[MaxN], u[MaxN], v[MaxN], a[MaxN], b[MaxN], f[MaxN][MaxL], cnt[MaxN], c[MaxN], sig[MaxN];
vector<int> e[MaxN], g[MaxN], h[MaxN]; map<int, int> vis;

int in[MaxN], dn;
void dfs(int x, int fa = 0) {
	f[x][0] = fa; in[x] = ++dn;
	for(int i = 1; i < MaxL; i++) f[x][i] = f[f[x][i - 1]][i - 1];
	for(auto y : e[x]) {
		if(y == fa) continue;
		dep[y] = dep[x] + 1;
		dfs(y, x);
	}
} 

int deg[MaxN];
void addEdge(int x, int y) {
	++deg[x]; ++deg[y];
	g[x].emplace_back(y);
	g[y].emplace_back(x);
}

void dfs2(int x, int fa = 0) {
	for(auto y : e[x]) {
		if(y != fa) {
			dfs2(y, x);
			cnt[x] += cnt[y]; 
		}
	}
}

int lca(int x, int y) {
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

int clk, cn, L[MaxN], R[MaxN];
bool chk(int x, int fa = 0) {
	c[x] = 1; ++clk;
	for(auto z : h[x]) {
		if(!vis[z]) {
			vis[z] = ++cn;
			L[cn] = clk;
		}
		else 
			R[vis[z]] = clk;
	}
	for(auto y : g[x]) {
		if(y == fa) continue;
		chk(y, x);
	} 
}

int s[MaxN];

struct bit{
	int bit[MaxN], t[MaxN], T;
	
	void clr() {
		++T;
	}
	
	int query(int p) {
		int ans = 0;
		for(; p; p -= p & -p) {
			if(t[p] != T) t[p] = T, bit[p] = 0;
			ans += bit[p];
		}
		return ans;
	}
	
	void add(int p) {
		for(; p < MaxN; p += p & -p) {
			if(t[p] != T) t[p] = T, bit[p] = 0;
			bit[p]++;
		}
	}
}T;
bool check() {
	int i, j, k;
	T.clr();
	for(i = 1; i <= cn; i = j) {
		for(j = i; j <= cn && L[i] == L[j]; j++)
			if(T.query(R[j] - 1) - T.query(L[j] - 1) > 0)
				return 0;
		for(j = i; j <= cn && L[i] == L[j]; j++) T.add(R[j]);
	}
	return 1;
}
int main() {
	int i, j;
	n = read(); m = read();
	for(i = 1; i < n; i++) {
		a[i] = read(); b[i] = read();
		e[a[i]].push_back(b[i]);
		e[b[i]].push_back(a[i]); 
	}
	dfs(1);
	for(i = 1; i <= m; i++) {
		u[i] = read(); v[i] = read();
		int w = lca(u[i], v[i]);
		h[u[i]].emplace_back(i);
		h[v[i]].emplace_back(i);
		cnt[w] -= 2; cnt[u[i]]++; cnt[v[i]]++;
	}
	dfs2(1);
	for(i = 1; i <= n; i++) if(f[i][0] && cnt[i]) addEdge(f[i][0], i);
	for(i = 1; i <= n; i++) if(deg[i] > 2) return puts("No"), 0;
	
	for(i = 1; i <= n; i++) 
		if(!c[i] && deg[i] == 1) {
			clk = cn = 0;
			vis.clear();
			chk(i);
			if(!check()) return puts("No"), 0;
		}
	puts("Yes");
	return 0;
}

