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

const int MaxN = 1001234;

int n, m; 

struct info {
	int x, y, i, t;
	info() {
	}
	info(int x, int y, int i, int t) : x(x), y(y), i(i), t(t) {
	}
	bool operator < (info b) {
		return y > b.y || (y == b.y && t > b.t);
	} 
}a[MaxN];

set<pair<int, int> > s; int g[MaxN];
int f[MaxN], fat[MaxN], siz[MaxN], ans[MaxN];

void insert(int x, int y) {
	set<pair<int, int> > :: iterator it = s.lower_bound(MP(x, -1));
	if(it != s.end()) ++g[it -> sec];
}

void query(int x, int y, int z) {
	set<pair<int, int> > :: iterator p = s.insert(MP(x, z)).fir, q = p;
	for(q != --s.end() ? fat[z] = (++q) -> sec : 0; p != s.begin(); ){
		q = p; q--; if(q -> sec > z) s.erase(q); else break;
	}
}

int find(int x) {
	return x == f[x] ? x : f[x] = find(f[x]);
}

void merge(int x, int y) {
	x = find(x); y = find(y);
	if(x != y) 
		f[x] = y, siz[y] += siz[x]; 
}

int main() {
	int i;
	n = read();
	for(i = 1; i <= n; i++) {
		int x = read(), y = read();
		a[i] = info(x, y, i, 1);
	}
	m = read();
	for(i = 1; i <= m; i++) {
		int x = read(), y = read();
		a[i + n] = info(x, y, i, 2);
	}
	int N = n + m;
	sort(a + 1, a + N + 1);
	for(i = 1; i <= N; i++)
		if(a[i].t == 1)
			insert(a[i].x, a[i].y);
		else
			query(a[i].x, a[i].y, a[i].i);
	for(i = 1; i <= m; i++) f[i] = i;
	for(i = m; i; i--) {
		siz[find(i)] += g[i]; ans[i] = siz[find(i)];
		merge(i, fat[i]);
	}
	for(i = 1; i <= m; i++) printf("%d\n", ans[i]);
	return 0;
}

