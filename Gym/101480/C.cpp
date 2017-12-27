#include <bits/stdc++.h>

#define fir first
#define sec second
#define MP make_pair
#define PB push_back

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

const int MaxN = 201234, MaxM = 1001234;

int f, n, m, fs[MaxM], ans[MaxN];

struct fence {
	int xL, xR, y, i, type;
	bool operator < (const fence & b) const {
		return y == b.y ? xL < b.xL : y > b.y;
	} 
}l[MaxN << 1];

struct cow {
	int x, y, i;
	bool operator < (const cow & b) const {
		return y > b.y;
	}
}c[MaxN], w[MaxN];

#define lc(p) (p << 1)
#define rc(p) (p << 1 | 1)
#define mid (l + r >> 1)
#define RT 1, 1, 1e6

struct info {
	int sum; bool em, rev;
}seg[MaxM << 2]; int pos[MaxN];

void push_up(int p) {
	seg[p].sum = seg[lc(p)].sum + seg[rc(p)].sum;
	seg[p].rev = seg[lc(p)].rev | seg[rc(p)].rev;
}

void push_down(int p) {
	if(seg[p].em) {
		seg[lc(p)].em = seg[p].em;
		seg[rc(p)].em = seg[p].em;
		seg[lc(p)].sum = seg[rc(p)].sum = 0;
		seg[p].em = 0;
	}
}

void modify(int p, int l, int r, int x, int d) {
	if(l == r) seg[p].sum += d;
	else {
		push_down(p);
		if(x <= mid)
			modify(lc(p), l, mid, x, d);
		else
			modify(rc(p), mid + 1, r, x, d);
		push_up(p);
	}
}

void cover(int p, int l, int r, int a, int b) {
	if(a > r || b < l) return;
	if(a <= l && r <= b) seg[p].em = 1, seg[p].sum =0;
	else {
		push_down(p);
		cover(lc(p), l, mid, a, b);
		cover(rc(p), mid + 1, r, a, b);
		push_up(p); 
	}	
}

void rever(int p, int l, int r, int x) {
	if(l == r) seg[p].rev ^= 1;
	else {
		push_down(p);
		if(x <= mid)
			rever(lc(p), l, mid, x);
		else
			rever(rc(p), mid + 1, r, x);
		push_up(p);
	}
} 

int sum(int p, int l, int r, int a, int b) {
	if(a > r || b < l) return 0;
	if(a <= l && r <= b) return seg[p].sum;
	push_down(p);
	return sum(lc(p), l, mid, a, b) + sum(rc(p), mid + 1, r, a, b);
}

int query(int p, int l, int r, int x) {
	if(l >= x) {
		if(seg[p].rev) {
			while(l != r) 
				if(seg[lc(p)].rev)
					p = lc(p), r = mid;
				else
					p = rc(p), l = mid + 1;
			return l;
		}else return 0;
	}else {
		push_down(p);
		int s = 0;
		if(x <= mid)
			if(s = query(lc(p), l, mid, x)) return s;
		return query(rc(p), mid + 1, r, x);
	}
}
int main() {
	int i;
	f = read();
	for(i = 1; i <= f; i++) {
		int x1 = read(), y1 = read(), x2 = read(), y2 = read();	
		l[i * 2] = (fence) {x1, x2, y1 - 1, i, 0};
		l[i * 2 - 1] = (fence) {x1, x2, y2, i, 1};
	}
	sort(l + 1, l + 2 * f + 1);
	m = read();
	for(i = 1; i <= m; i++) w[i].x = read(), w[i].y = read();
	sort(w + 1, w + m + 1);
	n = read();
	for(i = 1; i <= n; i++) c[i].x = read(), c[i].y = read(), c[i].i = i;
	sort(c + 1, c + n + 1); rever(RT, 1e6);
	for(int y = 1e6, N = 1, M = 1, F = 1; y; y--) {
		for(; l[F].y == y; ++F) {
			fence cur = l[F];
			if(cur.type) {
				int R = query(RT, cur.xR);
				int s = sum(RT, cur.xL, cur.xR);
				fs[cur.i] = sum(RT, cur.xR + 1, R);
				cover(RT, cur.xL, cur.xR);
				if(cur.xL > 1) {
					modify(RT, cur.xL - 1, s + fs[cur.i]);
					rever(RT, cur.xL - 1);
				}
				if(cur.xR < 1e6)
					rever(RT, cur.xR);
			}else {
				cover(RT, cur.xL, cur.xR);
				if(cur.xL != 1) {
					modify(RT, cur.xL - 1, -fs[cur.i]);
					rever(RT, cur.xL - 1);
				}
				if(cur.xR < 1e6) 
					rever(RT, cur.xR);
			}
		}
		for(; w[M].y == y; ++M) modify(RT, w[M].x, 1);
		for(; c[N].y == y; ++N) {
			int R = query(RT, c[N].x);
			ans[c[N].i] = sum(RT, c[N].x, R);
		}
	}
	for(i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}

