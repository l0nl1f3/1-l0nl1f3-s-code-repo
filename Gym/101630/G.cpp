#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;
typedef long long LL;
typedef unsigned long long u64;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
LL read() {
	LL x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 2001234;

int n, r;
LL a[MaxN], b[MaxN], c[MaxN], d[MaxN], e[MaxN], pb[MaxN], p[MaxN], q[MaxN], K;

void build(LL x[], LL y[]) {
	LL S = 0;
	for(int i = n - 1; ~i; i--) {
		S += y[i]; if(i + r < n) S -= y[i + r];
		x[i] = S;
	}
}

int xn, yn; LL lx[MaxN], ly[MaxN], ps[MaxN], qs[MaxN];

struct bit{
	LL bit[MaxN];
	void add(int p, int d) {
		for(; p <= n; p += p & -p)
			bit[p] += d;
	}
	
	LL sum(int p) {
		LL ans = 0;
		for(; p; p -= p & -p)
			ans += bit[p];
		return ans;
	}
	void clear() {
		memset(bit, 0, sizeof(bit));
	}
}A, B;
LL chk(LL s) {
	int i; LL ans = 0;
	A.clear(); B.clear();
	for(i = 0; i < n; i++) {
		LL S = p[i] + (i ? e[i - 1] : 0);
		LL x = lower_bound(lx + 1, lx + xn + 1, s - p[i]) - lx - 1, 
			y = lower_bound(ly + 1, ly + yn + 1, s - S) - ly - 1;
		ans += A.sum(y) + B.sum(x);
		A.add(qs[i] + 1, 1);
		if(i >= r) {
			A.add(qs[i - r] + 1, -1);
			B.add(ps[i - r] + 1, 1);
		}
	}
	return ans;
}

int main() {
	int i; LL S = 0;
	n = read(); r = read(); cin >> K;
	for(i = 0; i < n; i++) S += (a[i] = read());
	for(i = 0; i < n; i++) b[i] = read() - a[i];
	for(i = 0; i < n; i++) c[i] = read() - a[i];
	for(i = 0; i < n; i++) d[i] = c[i] - b[i];
	build(p, b);
	build(q, d);	
	n -= r - 1;
	for(i = 0; i < n; i++) e[i] = 2 * b[i] - c[i];
	for(i = 1; i < n; i++) e[i] += e[i - 1], q[i] -= e[i - 1];
	for(i = 0; i < n; i++) lx[++xn] = p[i];
	for(i = 0; i < n; i++) ly[++yn] = q[i];
	sort(lx + 1, lx + xn + 1); xn = unique(lx + 1, lx + xn + 1) - lx - 1;
	sort(ly + 1, ly + yn + 1); yn = unique(ly + 1, ly + yn + 1) - ly - 1;
	for(i = 0; i < n; i++) {
		ps[i] = lower_bound(lx + 1, lx + xn + 1, p[i]) - lx - 1;
		qs[i] = lower_bound(ly + 1, ly + yn + 1, q[i]) - ly - 1;
	}
	LL L = -1, R = 1, ans = 0;
	for(i = 0; i < n + r - 1; i++) R += c[i];
	while(L < R - 1) {
		LL mid = L + R >> 1;
		if(chk(mid) >= K)
			R = mid;
		else
			L = mid; 
	}
	cout << L + S;
	return 0;
}
