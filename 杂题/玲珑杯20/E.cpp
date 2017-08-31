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

const int MaxN = 401234;
const int MaxM = 30001234;

int pc, s[MaxM], rot[MaxN], ls[MaxM], rs[MaxM];
int n, a[MaxN];

void insert(int x, int &y, int l, int r, int d) {
	y = ++pc;
	s[y] = s[x] + 1;
	ls[y] = ls[x]; rs[y] = rs[x];
	
	if(l == r) return;
	
	if(d <= (l + r >> 1))
		insert(ls[x], ls[y], l, l + r >> 1, d);
	else
		insert(rs[x], rs[y], (l + r >> 1) + 1, r, d);
}

int query(int p, int q, int l, int r, int k) {
	if(l == r) return r;
	int o = s[ls[q]] - s[ls[p]];
	
	if(o < k)
		return query(rs[p], rs[q], (l + r >> 1) + 1, r, k - o);
	else 	
		return query(ls[p], ls[q], l, l + r >> 1, k);
}

int qrank(int p, int q, int l, int r, int k) {
	if(l == r) {
		return s[q] - s[p];
	}
	
	if(k <= (l + r >> 1))
		return qrank(ls[p], ls[q], l, l + r >> 1, k);
	else 
		return s[ls[q]] - s[ls[p]] + qrank(rs[p], rs[q], (l + r >> 1) + 1, r, k);
}

int q, b[MaxN];
int main() {
	int i;
	n = inp(); q = inp();
	int ub = 1e9; ub++;
	for(i = 1; i <= n; i++) {
		a[i] = inp();
		insert(rot[i - 1], rot[i], 1, ub, a[i]);
	}
	
	for(i = 1; i <= q; i++) {
		int l, r, x, a, b;
		l = inp(); r = inp(); x = inp(); a = inp(); b = inp();
		int ans1 = -1, ans2 = -1;
		int rk = qrank(rot[l - 1], rot[r], 1, ub, x);
		
		if(rk >= a) ans1 = query(rot[l - 1], rot[r], 1, ub, a); 
		else ans1 = -1;
		
		b += rk;
		ans2 = query(rot[l - 1], rot[r], 1, ub, b);
		if(ans2 == ub) ans2 = -1;
		printf("%d %d\n", ans1, ans2);
	}
	return 0;
}



