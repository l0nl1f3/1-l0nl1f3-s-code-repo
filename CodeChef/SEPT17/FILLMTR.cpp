#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;
typedef long long LL;
typedef unsigned long long u64;

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
const int MaxM = 1001234;
 
int n, q, u[MaxM], v[MaxM], d[MaxM], f[MaxN]; 

int find(int x) {
	return f[x] == x ? x : f[x] = find(f[x]);
}

vector<int> e[MaxN];

void ins(int u, int v) {e[u].push_back(v); }
void lnk(int u, int v) {ins(u, v), ins(v, u);}

int col[MaxN];

bool bfs(int x) {
	queue<int> q;
	q.push(x); col[x] = 1;
	while(!q.empty()) {
		int c = q.front(); q.pop();
		for(auto y : e[c]) {
			if(!~col[y]) {
				q.push(y);
				col[y] = !col[c];
			}
			if(col[y] == col[c]) 
				return 0;
		}
	}
	return 1;
}

void solve() {
	int i;
	n = inp(); q = inp();
	for(i = 1; i <= n; i++) f[i] = i;
	
	for(i = 1; i <= q; i++) u[i] = inp(), v[i] = inp(), d[i] = inp();
	
	for(i = 1; i <= q; i++) {
		if(d[i]) continue;
		f[find(u[i])] = find(v[i]);		
	}
	for(i = 1; i <= n; i++) find(i);
	for(i = 1; i <= n; i++) e[i].clear();
	
	for(i = 1; i <= q; i++) {
		if(!d[i]) continue;
		int x = f[u[i]], y = f[v[i]];
		if(x == y) {
			puts("no"); 
			return;
		}
		lnk(x, y);
	}
	
	for(i = 1; i <= n; i++) col[i] = -1;
	for(i = 1; i <= n; i++) 
		if(!~col[i] && !bfs(i)) {
			puts("no");
			return;
		}
	puts("yes");		
}

int main() {
	int i, T = inp();
	while(T--) 
		solve();
	return 0;
}



