#include <bits/stdc++.h>

#define fi first
#define se second
#define mp make_pair
#define pb push_back

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

const int MaxN = 1234;

vector <int> e[MaxN], q[MaxN];
int n, m, g[MaxN][MaxN];

bool safe(int x, int y) {
	for (auto ex : q[x])
		for (auto ey : q[y])
			if(g[ex][ey])
				return 1;
	return 0;
}

int f[MaxN];
void dfs(int x, int fa) {
	for (auto y : e[x]) 
		if(y != fa) 
			dfs(y, x);
	vector <int> son;
	q[x].clear(); q[x].pb(x); f[x] = 0;
	for (auto y : e[x]) 
		if(y != fa){
			f[x] += f[y];
			if(safe(x, y)) 
				++f[x]; 
			else son.pb(y);
		}
	int ok[12][12];	
	int m = son.size(), u = 1 << m, r = 0, up = 0;
	for (int i = 0; i < m; i++)
		for (int j = i + 1; j < m; j++)
			ok[i][j] = ok[j][i] = safe(son[i], son[j]);
	
	int g[1 << 11];	
	for (int i = 0; i < u; i++) {
		g[i] = 0;
		for (int x = 0; x < m; x++)
			if(i >> x & 1)
				for (int y = x + 1; y < m; y++)
					if(i >> y & 1)
						if(ok[x][y])
							cmax(g[i], g[i ^ (1 << x) ^ (1 << y)] + 1);
		if(g[i] == up) r |= (u - 1) ^ i;
		if(cmax(up, g[i])) r = (u - 1) ^ i;
	}
	f[x] += up;
	for (int i = 0; i < m; i++) if(r >> i & 1){
		int y = son[i];
		for(auto z : q[y]) q[x].pb(z); 
	}
}

int main() {
	for (int T = read(); T--; ) {
		n = read();
		for (int i = 1; i < n; i++) {
			int u = read(), v = read(); --u; --v;
			e[u].pb(v); e[v].pb(u);
		}
		m = read();
		for (int i = 1; i <= m; i++) {
			int u = read(), v = read(); --u; --v;
			g[u][v] = g[v][u] = 1;
		}
		dfs(0, -1);
		cout << f[0] << endl;
		for (int i = 0; i < n; i++) {
			e[i].clear();
			for (int j = 0; j < n; j++)
				g[i][j] = 0;
		}
	}
	return 0;
}
