#include <bits/stdc++.h>

#define fir first
#define sec second
#define PB emplace_back
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

const int MaxN = 301234;

int n, m;
vector<int> e[MaxN]; 
double f[MaxN], fs[MaxN];  int vis[MaxN], cnt[MaxN]; 

struct cmp {
	bool operator () (const int & x, const int & y) {
		return f[x] < f[y] || (f[x] == f[y] && x < y);
	}
};  set<int, cmp> s;
int main() {
	int i;
	n = read(); m = read();
	for(i = 1; i <= m; i++) {
		int u = read(), v = read();
		e[u].PB(v);
		e[v].PB(u);
	}
	for(i = 1; i <= n; i++) f[i] = 1;
	f[n] = 0; s.insert(n);
	while(s.size()) {
		int c = *s.begin(); s.erase(s.begin()); vis[c] = 1;

		for(auto y : e[c]) {
			if(!vis[y]) {
				s.erase(y); 
				fs[y] += f[c]; cnt[y]++;
				f[y] = (fs[y] + (int)e[y].size()) / cnt[y];
				s.insert(y);
			}
		}
	}
	printf("%.10lf\n", f[1]);
	return 0;
}

