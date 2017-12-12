#include <bits/stdc++.h>

#define to first
#define v second
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

const int MaxN = 3123; 
int n, m, K, u[MaxN], v[MaxN], w[MaxN], p[MaxN];
vector<pair<int, int> > e[MaxN];

LL dis[MaxN];
priority_queue<pair<LL, int>, vector<pair<LL, int> >, greater<pair<LL, int>> > q;

int W;
LL dijk() {
	int i;
	for(i = 1; i <= n; i++) dis[i] = 1e16;
	dis[1] = 0; q.push(MP(0, 1));
	while(!q.empty()) {
		pair<LL, int> c = q.top(); q.pop();
		if(dis[c.second] < c.first) continue;
		for(auto y : e[c.second]) {
			int b = y.to;
			if(cmin(dis[b], dis[c.second] + max(y.v - W, 0)))
				q.push(MP(dis[b], b)); 
		}
	}
	return dis[n];
}
int main() {
	int i;
	n = read(); m = read(); K = read();
	for(i = 1; i <= m; i++) {
		int u = read(), v = read(), w = read();
		e[u].emplace_back(MP(v, w));
		e[v].emplace_back(MP(u, w));
		::u[i] = u; :: v[i] = v; :: w[i] = w; :: p[i] = i;
	}
	sort(p + 1, p + m + 1, [&] (int x, int y) {return w[x] < w[y]; });
	LL ans = dijk();
	for(i = 1; i <= m; i++) {
		int _ = p[i]; W = w[_];
		cmin(ans, dijk() + (LL) K * W);
	}
	cout << ans;
	return 0;
}

