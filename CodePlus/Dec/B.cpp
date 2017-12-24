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

const int MaxN = 101234;

int n, m, s[MaxN];

priority_queue<int, vector<int>, greater<int> > q[MaxN];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > a;

int seg[MaxN << 2], pos[MaxN];

#define lc(p) (p << 1) 
#define rc(p) (p << 1 | 1)
#define mid (l + r >> 1) 

void build(int p, int l, int r) {
	seg[p] = 0;
	if(l == r) {
		pos[r] = p;
		return;
	}	
	build(lc(p), l, mid);
	build(rc(p), mid + 1, r);
}

int sum(int p, int l, int r, int a, int b) {
	if(a > r || b < l) return 0;
	if(a <= l && r <= b) return seg[p];
	return sum(lc(p), l, mid, a, b) + sum(rc(p), mid + 1, r, a, b); 
}

int sum(int l, int r) {
	int ans = 0;
	return sum(1, 1, n, l, r);	
}

void done(int i, int d = 1) {
	i = pos[i]; 
	for(seg[i] += d, i >>= 1; i; i >>= 1)
		seg[i] = seg[lc(i)] + seg[rc(i)];
}

int small(int p, int l, int r) {
	if(l == r) return r;
	int c = seg[lc(p)];
	if(c) return small(lc(p), l, mid);
	else return small(rc(p), mid + 1, r);
}
int small() {
	if(!seg[1]) return n + 1;
	return small(1, 1, n);
}

int get(int id) {
	return seg[pos[id]];
}

int main() {
	int i;
	int T = read();
	while(T--) {
		n = read();
		for(i = 1; i <= n; i++) s[i] = read();
		m = read();
		build(1, 1, n);
		while(m--) {
			int t = read(), op = read();
			
			while(!a.empty() && a.top().first <= t) done(a.top().second), a.pop();
			
			if(op == 0) {
				int id = read();
				a.push(MP(t + s[id], id));
				q[id].push(t + s[id]);
			}
			
			if(op == 1) {
				int z = small();
				if(z != n + 1)
					printf("%d\n", z), done(z, -1);
				else 
					puts("Yazid is angry.");
			}
			
			if(op == 2) {
				int id = read();
				if(!get(id)) {
					while(!q[id].empty() && q[id].top() < t) q[id].pop();
					if(q[id].empty())
						puts("YJQQQAQ is angry.");
					else 
						printf("%d\n", q[id].top() - t);
				}else {
					puts("Succeeded!");
					done(id, -1);
				}
			}
			
			if(op == 3) {
				int l = read(), r = read();
				printf("%d\n", sum(l, r));
			} 
		}
		
		while(!a.empty()) a.pop();
		for(i = 1; i <= n; i++) while(!q[i].empty()) q[i].pop();
	}
	return 0;
}

