#include <bits/stdc++.h>

#define fir first
#define sec second
#define MP make_pair

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

const int MaxN = 201234, MaxNode = MaxN * 20, U = 2e9;

int n, segn, rot, lc[MaxNode], rc[MaxNode], x[MaxN], y[MaxN];
set<int> seg[MaxNode]; vector<int> t;

#define mid (l + (((LL)r - l) >> 1))

void insert(int &p, int l, int r, int a, int b, int id, int op = 1) {
	if(!p) p = ++segn;
	if(a > r || b < l) return;
	if(a <= l && r <= b) {
		if(op)
			seg[p].emplace(id);
		else 
			seg[p].erase(id);
		return;
	}	
	insert(lc[p], l, mid, a, b, id, op);
	insert(rc[p], mid + 1, r, a, b, id, op);
}

void extract(int p, int l, int r, int x) {
	if(!p) return;
	for(auto y : seg[p]) t.emplace_back(y);
	if(l == r) return;
	if(x <= mid)
		extract(lc[p], l, mid, x);
	else
		extract(rc[p], mid + 1, r, x);
}

int main() {
	int i;
	n = read();
	for(i = 1; i <= n; i++) {
		int op = read(); x[i] = read(); y[i] = read();
		if(op == 1) {
			insert(rot, -U, U, x[i] - y[i], x[i] + y[i], i);
		}else {
			t.clear();
			extract(rot, -U, U, x[i]);
			int ans = -1;
			for(auto p : t) {
				LL dis = (LL) (x[i] - x[p]) * (x[i] - x[p]) + (LL) (y[i] - y[p]) * (y[i] - y[p]);
				if(dis < (LL) y[p] * y[p]) {
					ans = p;
					insert(rot, -U, U, x[p] - y[p], x[p] + y[p], 0);
					break;
				}
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}



