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
const int MaxN = 201234, MaxM = MaxN << 2;
const int P = 1000000007;

struct Segment_Tree {
	int seg[MaxM], tag[MaxM];
	
	void modify(int p, int d) {
		for(; p < MaxN; p += p & -p) 
			(seg[p] += d) %= P;
	}
	
	void modify(int l, int r, int d) {
		modify(l, d);
		modify(r + 1, P - d);
	}
	
	int query(int p) {
		int ans = 0;
		for(; p; p -= p & -p) 
			(ans += seg[p]) %= P;
		return ans; 
	}
	
	void clear() {
		memset(tag, 0, sizeof(tag));
		memset(seg, 0, sizeof(seg));
	}
	
}Ta, Top;

int n, m, l[MaxN], r[MaxN], op[MaxN];

void solve() {
	int i;
	Ta.clear(); Top.clear();
	n = inp(); m = inp();
	for(i = 1; i <= m; i++) op[i] = inp(), l[i] = inp(), r[i] = inp();
	for(i = m; i; i--) {
		int cnt = Top.query(i) + 1;
		if(op[i] == 2) 
			Top.modify(l[i], r[i], cnt);
		else
			Ta.modify(l[i], r[i], cnt);
	}
	for(i = 1; i <= n; i++) printf("%d ", Ta.query(i)); puts("");
}

int main() {
	int i, T = inp();
	while(T--)	solve();
	return 0;
}



