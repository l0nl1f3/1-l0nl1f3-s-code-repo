#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;
typedef long long LL;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int inp() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}
const int MaxN = 101234;

int n, m;
int mark[MaxN], deg[MaxN], lst[MaxN];
vector<int> e[MaxN], a, g[MaxN]; 
priority_queue<int, vector<int>, greater<int> > pq;

void solve() {
	int i, j; 
	memset(deg, 0, sizeof(deg));
	for(i = 0; i <= n; i++) g[i].clear();

	for(i = 1; i <= n; i++) {
		a.clear();
		int chk = 1;
		for(auto p : e[i]) {
			if(p == i - 1) chk = 0;
			a.push_back(p);
		}
		if(chk) {
			puts("-1");
			return;
		}
		sort(a.begin(), a.end());
		int u = a[0], v = a[a.size() - 1];
		
		if(v != i - 1) {
			puts("-1");
			return;
		}
		if(v - u + 1 != a.size()) {
			puts("-1");
			return;
		}  
		lst[i] = u;
	}

	int bd = 0;
	for(i = 1; i <= n; i++) 
		if(lst[i])	
			deg[i] = deg[lst[i]];
		else 
			deg[i] = ++bd;

	for(i = 1; i <= n; i++) {
		int L = lst[i];
		for(j = L + 1; j < i; j++)
			if(deg[j] == deg[i]) {
				puts("-1");
				return;
			}
	}
	for(i = 1; i <= n; i++) printf("%d ", deg[i]); puts("");
}
int main() {
	int i, T = inp();
	while(T--) {
		n = inp(); m = inp();
		for(i = 0; i <= n; i++) e[i].clear();
		for(i = 1; i <= m; i++) {
			int u = inp(), v = inp();
			e[v].push_back(u);
		}
		solve();
	}
	return 0;
}



