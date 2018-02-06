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

vector <int> g;

int m[3][3];

void dfs(int x, int y, int p = 0) {
	g.pb(p);
	if(x + 1 < 3) {
		int q = p;
		for (int i = 0; i <= 3; i++) {
			dfs(x + 1, y, q);
			q = q * 10 + m[x + 1][y];
		}
	}
	 
	if(y + 1 < 3) {
		int q = p;
		for (int i = 0; i <= 3; i++) {
			dfs(x, y + 1, q);
			q = q * 10 + m[x][y + 1];
		}
	}
}

void gao() {
	int t = 0;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++) 
			m[i][j] = ++t;
	dfs(0, 0, 1); dfs(0, 1, 2); dfs(0, 2, 2);
	dfs(0, 0, 0); dfs(0, 1, 0); dfs(0, 2, 0);
	
	for (auto x : g) 
		if(x % 10 == 8)
			g.pb(x * 10), g.pb(x * 100);
	sort(g.begin(), g.end()); g.erase(unique(g.begin(), g.end()), g.end());
}

int main() {
	gao();
	
	for (int T = read(), n; T--; ) {
		n = read(); int d = INT_MAX, ans = 0;
		for (auto x : g) {
			if(cmin(d, abs(n - x))) 
				ans = x;
			if(x > 200) break;
		}
		printf("%d\n", ans);
	}
	
	return 0;
}




