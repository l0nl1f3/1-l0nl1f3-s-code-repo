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

const int MaxN = 501234;
vector<pair<int, int> > e[MaxN], p[MaxN];
int n, m, q, u[MaxN], v[MaxN], w[MaxN], f[MaxN], siz[MaxN], ans[MaxN];

int find(int x) {
	return f[x] == x ? x : find(f[x]);
}

stack<int> s;
bool merge(int x, int y, bool open = 0) {
	if((x = find(x)) == (y = find(y))) return 0;
	if(siz[x] > siz[y]) swap(x, y);
	siz[y] += siz[x]; f[x] = y; if(!open) s.push(x);
	return 1;
}

int main() {
	int i, j, k, up;
	n = read(); m = read();
	for(i = 1; i <= m; i++) {
		u[i] = read(); v[i] = read();
		e[w[i] = read()].push_back(make_pair(u[i], v[i]));
		cmax(up, w[i]);
	}
	q = read();
	for(i = 1; i <= q; i++)
		for(j = read(); j--;) {
			k = read();
			p[w[k]].push_back(make_pair(i, k));
		}
	for(i = 1; i <= n; i++) f[i] = i, siz[i] = 1;
	for(i = 1; i <= up; i++) {
		for(j = 0; j < p[i].size(); j++) {
			pair<int, int> x = p[i][j];
			if(!j || (j && x.fir != p[i][j - 1].fir))
				while(!s.empty()) {
					int x = s.top(); s.pop();
					siz[f[x]] -= siz[x], f[x] = x;
				}
			if(!merge(u[x.sec], v[x.sec])) ans[x.fir] = 1;
		} 
		while(!s.empty()) {
			int x = s.top(); s.pop();
			siz[f[x]] -= siz[x], f[x] = x;
		}
		for(j = 0; j < e[i].size(); j++) merge(u[e[i][j].fir], v[e[i][j].sec], 1);
	}
	for(i = 1; i <= q; i++) puts(ans[i] ? "NO" : "YES"); 
	return 0;
}



