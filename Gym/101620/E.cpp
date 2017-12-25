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

const int MaxN = 301234, P = 1e9 + 7;

int n, m, f[MaxN][4][4], d[MaxN], fat[MaxN];

vector<int> e[MaxN], dfn; pair<int, int> fork[MaxN];
 
void dfs(int x, int fa = -1) {
	dfn.PB(x); fat[x] = fa;
	for(auto y : e[x]) {
		if(y == fa) continue;
		dfs(y, x);
		if(d[x] == 2) 
			fork[x] = MP(fork[y].fir, fork[y].sec + 1);
	}
	if(x && d[x] != 2) fork[x] = MP(x, 0);
}

inline bool neig(int x, int y, int z, int & ans) {
	bool chk = 0;
	ans = -1;
	for(int i = 0; i + 1 < e[x].size(); i++) {
		int b = e[x][i];
		if(b != n + 1 && b != y && b != z) {
			if(chk) return 0; 
			chk = 1; ans = b;
		}
	}
	return 1;
}

inline void up(int &x, int y) {
	(x += y) %= P;
}

int ans;
void single_child(int x, int val) {
	up(f[x][d[x]][0], val);
	pair<int, int> z = fork[x];
	for(int i = 0; i + 1 < e[x].size(); i++)
		if(e[x][i] != fat[x]) up(f[x][i][d[e[x][i]]], val);
	if(d[z.fir] == 1) {
		if(z.sec >= 3 && (z.sec & 1)) 
			up(ans, val);
	}
	else 
		for(int t = 0, p = z.fir; t < 2; t++, p = fat[p]) 
			for(int i = 0; i + 1 < e[p].size(); i++) {
				int q = e[p][i]; if(q == fat[p]) continue;
				for(int j = 0; j + 1 < e[q].size(); j++) {
					int r = e[q][j]; if(r == fat[q]) continue;
					if(d[fork[r].fir] == 1 && fork[x].sec - fork[r].sec - 1 == t)
						up(f[p][i][j], val);
				}
			}
}

void trans(int x, int y, int z, int val) {
	int u, v; 
	if(!neig(x, fat[x], y, u) || !neig(y, x, z, v)) return;
	if(u != -1 && v != -1) {
		while(d[u] == 2 && d[v] == 2) 
			neig(u, fat[u], -1, u), neig(v, fat[v], -1, v);
		if(!neig(u, fat[u], -1, u) || !neig(v, fat[v], -1, v)) return;
	}
	if(u == -1 && v == -1) 	return up(ans, val);
	return single_child(max(u, v), val);
}

int main() {
	int i, j, k, T;
	n = read();
	fat[0] = -1; e[0].PB(1); e[1].PB(0); d[0]++; d[1]++; 
	for(i = 1; i < n; i++) {
		int u = read(), v = read();
		e[u].PB(v); e[v].PB(u); d[u]++; d[v]++; 
		if(d[u] > 3 || d[v] > 3) return puts("0"), 0;
	}
	dfs(0); f[0][1][0] = 1; 
	for(i = 0; i <= n + 1; i ++) e[i].PB(n + 1);
	for(auto x : dfn) 
		for(i = 0; i < e[x].size(); i++) 
			for(j = 0; j < e[e[x][i]].size(); j++) 
				trans(x, e[x][i], e[e[x][i]][j], f[x][i][j]);
	cout << ans << endl;
	return 0;
}

