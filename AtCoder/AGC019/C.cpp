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

#define y1 thisisbad
#define x1 thisisworse

const int MaxN = 401234;
int x1, y1, x2, y2, n, m;
int x[MaxN], y[MaxN], rk[MaxN];

bool cmp(int u, int v) {
	return make_pair(x[u], y[u]) < make_pair(x[v], y[v]); 
}

bool cmp1(int u, int v) {
	return y[u] < y[v]; 
}

bool cmp2(int u, int v) {
	return y[u] > y[v]; 
}

int a[MaxN], dp[MaxN];

int abs(int x) {
	return x < 0 ? -x : x;
}

int main() {
	int i;
	cin >> x1 >> y1 >> x2 >> y2;
	cin >> n;
	for(i = 1; i <= n; i++) 
		x[i] = inp(), y[i] = inp();
		
	if(x1 > x2) swap(x1, x2), swap(y1, y2);
	
	int u, d, l, r; 
	u = max(x1, x2); d = min(x1, x2); 
	l = min(y1, y2); r = max(y1, y2);
	
	for(i = 1; i <= n; i++) 
		if(x[i] > u || x[i] < d || y[i] < l || y[i] > r)
			continue;
		else
			x[++m] = x[i], y[m] = y[i];
				
	n = m;
	for(i = 1; i <= n; i++) rk[i] = i;
	sort(rk + 1, rk + n + 1, cmp);
	
	sort(rk + 1, rk + n + 1, y1 < y2 ? cmp1 : cmp2);
	
	for(i = 0; i < n; i++) a[i] = x[rk[i + 1]];
	fill(dp, dp + n, 233333333);
	for(i = 0; i < n; i++) 
		*lower_bound(dp, dp + n, a[i]) = a[i];
	
	int L = lower_bound(dp, dp + n, 233333333) - dp;
	double ans = abs(x2 - x1) + abs(y2 - y1); 
	ans *= 100;
	ans -= (20 - 5 * acos(-1)) * L;
	int lim = min(r - l + 1, u - d + 1);
	 
	if(L == lim) ans += 5 * acos(-1);	
	printf("%.20lf", ans);
	return 0;
}



