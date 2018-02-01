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

const int MaxN = 2333;
int n, x[MaxN], y[MaxN], r[MaxN], v[MaxN], d[MaxN]; 
vector <int> e[MaxN]; pair<int, int> ve[MaxN];

void dfs(int x) {
	v[x] = 1;
	for(auto y : e[x]) {
		if(!v[y]) {
			d[y] = d[x] ^ 1;
			ve[y] = mp(ve[x].fi * r[x], ve[x].se * r[y]);
			int g = __gcd(ve[y].fi, ve[y].se);
			ve[y].fi /= g; ve[y].se /= g;
			dfs(y);
		}
	} 
} 
int main() {
	for (int T = read(); T--; ) {
		n = read(); 
		for (int i = 1; i <= n; i++) e[i].clear(), v[i] = d[i] = 0;
		for (int i = 1; i <= n; i++) x[i] = read(), y[i] = read(), r[i] = read();
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++) {
				LL d = (LL) (y[j] - y[i]) * (y[j] - y[i]) + (LL) (x[j] - x[i]) * (x[j] - x[i]);
				if(d == (LL) (r[i] + r[j]) * (r[i] + r[j]))
					e[i].pb(j), e[j].pb(i);
			}
		ve[1] = mp(1, 1);
		dfs(1);
		for (int i = 1; i <= n; i++) {
			if(!v[i]) puts("not moving");
			else {
				if(ve[i].se == 1) 
					printf("%d ", ve[i].fi);
				else 
					printf("%d/%d ", ve[i].fi, ve[i].se);
				puts(d[i] ? "counterclockwise" : "clockwise");
			} 
		}
	}
	return 0;
}




