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

LL sqr(LL x) {
	return x * x;
}
const LL inf = 1e16;
const int MaxN = 3333;
int n, b, c, a[MaxN];
LL f[MaxN][MaxN], g[MaxN][MaxN], h[MaxN][MaxN], dp[MaxN];

int solve() {
	if(n == 1) return puts("1"), 0;	
	int i, j, k, p;
	for(i = 0; i <= b; i++)
		for(j = 1; j <= n; j++) f[i][j] = g[i][j] = inf; 
	
	for(i = 1; i <= n; i++) f[0][i] = inf;
	f[0][1] = 0;
	for(i = 1; i <= b; i++) 
		for(f[i][1] = 0, j = 2; j <= n; j++)
			for(f[i][j] = sqr(a[j] - a[1]), p = 1; p < j; p++)
				cmin(f[i][j], f[i - 1][p] + sqr(a[p] - a[j]));
				
	for(i = 1; i <= n; i++) g[0][i] = inf;
	g[0][n] = 0;
	for(i = 1; i <= b; i++) 
		for(g[i][n] = 0, j = n - 1; j; j--)
			for(g[i][j] = sqr(a[n] - a[j]), p = j + 1; p <= n; p++)
				cmin(g[i][j], g[i - 1][p] + sqr(a[p] - a[j]));
				
	for(i = 1; i <= n; i++) h[0][i] = inf;	
	h[0][c] = 0;
	for(i = 1; i <= b; i++)
		for(h[i][c] = 0, j = 1; j <= n; j++) 
			for(h[i][j] = sqr(a[c] - a[j]), p = 1; p <= n; p++)
				cmin(h[i][j], h[i - 1][p] + sqr(a[p] - a[j]));
	
	LL ans = inf;
	for(i = 1; i <= n; i++) {
		for(p = 1; p <= b; p++) {
			dp[i] = inf;
			for(j = i, k = i; j; j--) {
				for(; k <= n && abs(a[j] - a[i]) >= abs(a[i] - a[k]); k++);
				cmin(dp[i], f[p - 1][j] + g[p - 1][k - 1] + sqr(a[i] - a[j]));
			}
			for(j = k = i; k <= n; k++) {
				for(; j && abs(a[k] - a[i]) >= abs(a[i] - a[j]); j--);
				cmin(dp[i], f[p - 1][j + 1] + g[p - 1][k] + sqr(a[i] -  a[k])); 
			}
			cmin(ans, h[b - p][i] + dp[i]);
		}
	}
	cout << ans << endl; 
}
int main() {
	int i, T = inp();
	while(T--) {
		n = inp(); b = inp(); c = inp();
		for(i = 1; i <= n; i++) a[i] = inp();
		solve();
	}
	return 0;
}



