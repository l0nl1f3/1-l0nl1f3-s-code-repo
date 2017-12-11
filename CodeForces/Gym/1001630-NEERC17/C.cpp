#include <bits/stdc++.h>

#define fir first
#define sec second
#define MP make_pair

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

const int MaxN = 101234;

int T, n, m, vis[MaxN], d[MaxN], u[MaxN], v[MaxN];
vector<pair<int, int> > f[MaxN], g[MaxN];

void dfs1(int x) {
	vis[x] = 1;
	for(auto y : f[x]) 
		if(!vis[y.fir]) {
			d[y.sec] = 1;
			dfs1(y.fir);
		}
}

void dfs2(int x) {
	vis[x] = 1;
	for(auto y : g[x]) 
		if(!vis[y.fir]) {
			d[y.sec] = 1;
			dfs2(y.fir);
		}
}

int main() {
	int i;
	T = read();
	while(T--) {
		n = read(); m = read();
		for(i = 1; i <= m; i++) {
			u[i]= read(); v[i] = read();
			f[u[i]].push_back(MP(v[i], i));
			g[v[i]].push_back(MP(u[i], i));
		}
		memset(d, 0, sizeof(d));
		memset(vis, 0, sizeof(vis));
		dfs1(1);
		memset(vis, 0, sizeof(vis));
		dfs2(1);
		int cnt = 0;
		for(i = 1; i <= m; i++) 
			if(!d[i]) printf("%d %d\n", u[i], v[i]), ++cnt >= m - 2 * n ? i = m : 0;
		for(i = 1; i <= n; i++) f[i].clear(), g[i].clear(); 
	}
	return 0;
}



