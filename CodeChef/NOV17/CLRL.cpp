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
 
const int MaxN = 1001234;
int T, n, K, a[MaxN];
int rot, seg[MaxN << 5], lc[MaxN << 5], rc[MaxN << 5], segn;
 
void insert(int & p, int l, int r, int x) {
	if(!p) seg[p = ++segn] = lc[p] = rc[p] = 0;
	if(l == r) {
		seg[p]++;
		return;
	}
	if(x <= l + r >> 1)
		insert(lc[p], l, l + r >> 1, x);
	else
		insert(rc[p], (l + r >> 1) + 1, r, x);
	seg[p] = seg[lc[p]] + seg[rc[p]];
}
 
int sum(int p, int l, int r, int a, int b) {
	if(!p || b < l || a > r)
		return 0;
	if(a <= l && r <= b)
		return seg[p];
	return sum(lc[p], l, l + r >> 1, a, b) + sum(rc[p], (l + r >> 1) + 1, r, a, b);
}
 
void solve() {
	rot = segn = 0; int i;
	for(i = 1; i < n; i++) 
		if((a[i] < a[i + 1]) ^ (a[i] < K)) {
			puts("NO");
			return;
		}	
	for(i = 1; i < n; i++) {
		if(sum(rot, 1, 1e9, min(a[i], a[i + 1]), max(a[i], a[i + 1])) > 0) {
			puts("NO");
			return;
		}
		insert(rot, 1, 1e9, a[i]);
	}
	puts("YES");
}
 
int main() {
	int i;
	T = read();
	while(T--) {
		n = read(); K = read();
		for(i = 1; i <= n; i++) a[i] = read();
		solve();
	}
	return 0;
}
