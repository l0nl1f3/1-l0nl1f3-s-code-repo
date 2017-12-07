#include <cstdio>
#include <iostream>
#include <algorithm>

#define fir first
#define sec second
using namespace std;
typedef long long LL;
typedef unsigned long long u64;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}

const int MaxNode = 8000000, MaxN = 200010;

int qL, qR, rot[MaxN], segn;
struct Node {
	u64 lc : 23, rc : 23, u : 18;
}seg[MaxNode]; 
pair<int, int> a[MaxN]; 

#define L(p) (l == mid ? (int) seg[p].lc : (int) seg[seg[p].lc].u)
#define R(p) (r == mid + 1 ? (int) seg[p].rc : (int) seg[seg[p].rc].u)
 
int modify(int p, int l, int r) {
	if(l == r) return p + 1;
	int o = ++segn; seg[o] = seg[p];
	if(qL <= l && r <= qR) {
		++seg[o].u; return o;
	}
	int mid = l + r >> 1;
	int tag = seg[o].u - max(L(o), R(o));
	if(qL <= mid) seg[o].lc = modify(seg[p].lc, l, mid);
	if(qR > mid) seg[o].rc = modify(seg[p].rc, mid + 1, r);
	seg[o].u = max(L(o), R(o)) + tag; return o;
}

int query(int p, int l, int r) {
	if(l == r) return p;
	if(qL <= l && r <= qR) 
		return seg[p].u;
	int mid = l + r >> 1;
	int ans = 0, tag = seg[p].u - max(L(p), R(p));
	if(qL <= mid) cmax(ans, query(seg[p].lc, l, mid));
	if(qR > mid) cmax(ans, query(seg[p].rc, mid + 1, r));
	return ans + tag;
}

int n, m, q;
int main() {
	int i;
	ios :: sync_with_stdio(0);
	cin >> n >> m;	
	for(i = 1; i <= n; i++) {
		int t; cin >> t;
		a[i] = make_pair(-t, i);
	}
	
	sort(a + 1, a + n + 1);
	for(i = 1; i <= n; i++) {
		qL = max(1, a[i].sec - m + 1);
		qR = min(n - m + 1, a[i].sec);
		rot[i] = modify(rot[i - 1], 1, n - m + 1);
	}
	cin >> q;
	int last = 0;
	while(q--) {
		int K;
		cin >> qL >> qR >> K; K ^= last; 
		int p = upper_bound(a + 1, a + n + 1, make_pair(-K, n + 1)) - a - 1;
		printf("%d\n", last = m - query(rot[p], 1, n - m + 1));
	}
	return 0;
}

