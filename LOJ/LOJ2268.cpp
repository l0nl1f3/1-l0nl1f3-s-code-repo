#include <bits/stdc++.h>

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SZ(x) (x).size()
#define ALL(x) x.begin(), x.end()

using namespace std;
typedef long long LL;
typedef unsigned long long u64;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int read() {
	int x = 0, f = 1;char ch;
	for (ch = getchar(); !isdigit(ch); ch = getchar())
		if (ch == '-') f = -1;
	for (; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 21234, MaxK = 501234, MaxNK = 30001234;

int n, K, a[MaxN], v[MaxN], dfn;  
vector <int> e[MaxN];

int F[MaxNK], G[MaxNK];

#define f(n, k) F[(n) * (K + 1) + k]
#define g(n, k) G[(n) * (K + 1) + k]

void put(int p, int a, int v, int *F) {
	for (int i = 1; a; i <<= 1) {
		int x = min(i, a), y = v * x; a -= x;
		for (int j = K; j >= x; j--)
			cmax(f(p, j), f(p, j - x) + y);
	}	
}

int ans;

void dfs(int x) {
	put(x, a[x], v[x], F);
	for (auto y : e[x]) {
		for (int i = 0; i <= K; i++)
			f(y, i) = f(x, i);
		dfs(y);
		for (int i = 1; i <= K; i++)
			cmax(f(x, i), f(y, i - 1) + v[y]);
	}
}

void dfs2(int x, int d = 0) {
	for (auto y : e[x]) {
		for (int i = 0; i <= K; i++)
			g(y, i) = g(x, i);
		dfs2(y, d + v[x]);
		for (int i = 1; i <= K; i++)
			cmax(g(x, i), g(y, i - 1) + v[y]);
	}
	
	if(!e[x].size()) {
		for (int i = 1; i <= K; i++)
			cmax(f(x, i), f(x, i - 1));
		for (int i = 0; i <= K; i++)
			cmax(ans, f(x, K - i) + g(x, i) + d + v[x]);
	}
	put(x, a[x], v[x], G);
}

int main() {
	for (int T = read(); T--; ) {
		n = read(); K = read();
		for (int i = 1; i <= n; i++) e[i].clear();
		for (int i = 1; i <= n; i++) {
			int j = read(); a[i] = min(read() - 1, K); v[i] = read();
			if(j) e[j].pb(i); 
		}
		for (int i = 0; i <= K; i++) f(1, i) = g(1, i) = 0;
		dfs(1);
		for (int i = 1; i <= n; i++) reverse(ALL(e[i]));
		ans = 0;
		dfs2(1);
		printf("%d\n", ans);
	}
	return 0;
}
