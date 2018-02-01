#include <bits/stdc++.h>

#define fi first
#define se second
#define mp make_pair
#define pb push_back

using namespace std;
typedef long long LL;
typedef unsigned long long u64;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int read() {
	int x = 0, f = 1;char ch;
	for (ch = getchar(); !isdigit(ch); ch = getchar())
		if (ch == '-') f = -1;
	for (; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 101234;

int n;

struct point {
	int x, y;
	point() {}
	point(int x, int y) : x(x), y(y) {}
	point operator - (point b) {
		return point(x - b.x, y - b.y);
	} 
	LL operator * (point b) {
		return (LL) x * b.y - (LL) y * b.x;	
	}
}p[MaxN];

vector<point> seg[MaxN << 2];

void build(vector<point> & q, int l, int r) {
	for (q.clear(), q.pb(p[l++]); l <= r + 1; q.pb(p[l++])) 
		while (q.size() > 1 && (p[l] - q.back()) * (q.back() - q[q.size() - 2]) <= 0) 
			q.pop_back();
}

void build(int p, int l, int r) {
	build(seg[p], l, r);
	if (l == r) return;
	build(p << 1, l, l + r >> 1);
	build(p << 1 | 1, (l + r >> 1) + 1, r);
} 

int in(vector<point> q, point a, point b) {
	int mid, l = 0, r = q.size() - 1, w = l++;
	while(l <= r) {
		mid = l + r >> 1;
		if((q[mid] - a) * (b - q[mid]) < (q[mid - 1] - a) * (b - q[mid - 1]))
			l = mid + 1, w = mid;
		else 
			r = mid - 1;
	}
	return (q[w] - a) * (b - q[w]) < 0;
}

int query(int p, int l, int r, int i, int x) { 
	if(x <= l) {
		if(!in(seg[p], :: p[i], :: p[i + 1]))
			return 0;
		if(l == r) return l;
	}
	
	int mid = l + r >> 1;
	if(x <= mid) {
		int lcq = query(p << 1, l, mid, i, x);
		if(lcq) return lcq;
	}
	return query(p << 1 | 1, mid + 1, r, i, x);
}

int main() {
	for (int T = read(); T; T--) {
		n = read();
		for (int i = 1; i <= n; i++) p[i].x = read(), p[i].y = read();
		build(1, 1, --n);
		for (int i = 1; i < n; i++) 
			printf("%d ", query(1, 1, n, i, i + 1));
		puts("0");
	}
	return 0;
}




