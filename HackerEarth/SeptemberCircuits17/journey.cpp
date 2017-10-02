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

const int MaxN = 666666, M = 524288;
const LL infLL = LONG_LONG_MAX >> 1;

int n, m, L[MaxN], c[MaxN], p[MaxN], nxt[MaxN];
LL s[MaxN], f[MaxN], seg[M << 1];

void modify(int p, LL d) {
	for(seg[p += M] = d, p >>= 1; p; p >>= 1) 
		seg[p] = min(seg[p << 1], seg[p << 1 | 1]);
}

LL query(int l, int r) {
	if(l > r) return infLL; 
	LL ans = infLL;
	for(l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
		if(~ l & 1) cmin(ans, seg[l ^ 1]);
		if(r & 1) cmin(ans, seg[r ^ 1]); 
	}
	return ans;
}

int main() {
	int i;
	n = inp(); m = inp();
	for(i = 1; i < n; i++) L[i] = inp();
	for(i = 1; i < n; i++) c[i] = inp();
	for(i = 1; i < n; i++) p[i] = inp();
	
	for(i = 2; i <= n; i++) s[i] = s[i - 1] + L[i - 1]; 
	for(i = 1; i < n; i++) nxt[i] = upper_bound(s + i, s + n + 1, s[i] + c[i]) - s - 1;
	
	for(i = 1; i <= n; i++) seg[i + M] = (i == n ? 0 : infLL);
	for(i = M - 1; i; i--) seg[i] = min(seg[i << 1], seg[i << 1 | 1]);
	for(i = n - 1; i; i--) {
		LL d = query(i + 1, nxt[i]);
		modify(i,  f[i] = d + p[i]);
	}
	
	for(i = 2; i <= n; i++) cmin(f[i], f[i - 1]);
	for(i = 1; i <= m; i++) {
		LL x; scanf("%lld", &x);
		int r = upper_bound(s + 1, s + n + 1, x) - s - 1;
		printf("%lld\n", (f[r] >= infLL ? -1 : f[r]));
	}
	return 0;
}



