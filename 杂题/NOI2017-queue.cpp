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

const int MaxN = 201234, K = 50, MaxK = 51, P = 998244353;

int n, m, q, a[MaxN], pre[MaxN], nxt[MaxN], cnt[MaxN];

int f[MaxK << 1]; u64 g[MaxK << 1], p[MaxK];

const int HF = (1 << 24) - 1; 
struct HASH{
	struct edge {
		u64 x; int cnt; edge *nxt;
	} *lst[HF + 1], pool[20001000], *cur = pool, *t;
	void append(u64 x, int d = 1) {
		int u = (x & HF);
		for(t = lst[u]; t; t = t -> nxt)
			if(t -> x == x) {
				t -> cnt += d;
				return;
			}
		t = cur++; t -> x = x; t -> cnt = d; t -> nxt = lst[u]; lst[u] = t;
	}
	int query(u64 x) {
		int u = (x & HF);
		for(t = lst[u]; t; t = t -> nxt) 
			if(t -> x == x) 
				return t -> cnt;
		return 0;
	}
}H;

void merge() {
	int x = read(), y = read();
	memset(f, 0, sizeof(f));
	
	int L = MaxK, R = L - 1;
	for(int i = x; i && L > 1; i = pre[i]) f[--L] = a[i];
	for(int i = y; i && R + 1 < MaxK * 2; i = nxt[i]) f[++R] = a[i];
	for(int i = 1; i <= R; i++) 
		g[i] = g[i - 1] * 233 + f[i];
	
	for(int i = L; i < MaxK; i++)
		for(int j = MaxK; j <= min(R, i + K - 1); j++)
			H.append(g[j] - g[i - 1] * p[j - i + 1]);

	nxt[x] = y; pre[y] = x;
}

void split() {
	int x = read(), y = nxt[x];
	memset(f, 0, sizeof(f));
	
	int L = MaxK, R = L - 1;
	for(int i = x; i && L > 1; i = pre[i]) f[--L] = a[i];
	for(int i = y; i && R + 1 < MaxK * 2; i = nxt[i]) f[++R] = a[i];
	for(int i = 1; i <= R; i++) 
		g[i] = g[i - 1] * 233 + f[i];
	
	for(int i = L; i < MaxK; i++)
		for(int j = MaxK; j <= min(R, i + K - 1); j++)
			H.append(g[j] - g[i - 1] * p[j - i + 1], -1);

	nxt[x] = pre[y] = 0;
}

char s[10001000];
int query() {
	scanf("%s", s + 1); int k = read();
	u64 val = 0; int ans = 1, n = strlen(s + 1);
	if(k == 1) {
		for(int i = 1; i <= n; i++)
			ans = (LL) ans * cnt[s[i]] % P;
	}else {
		for(int i = 1; i <= n; i++) {
			val = val * 233 + s[i];
			if(i > k) val -= p[k] * s[i - k];
			if(i >= k) ans = (LL) ans * H.query(val) % P;
		}
	}
	return ans;
} 
int main() {
	int i;
	n = read(); q = read();
	p[0] = 1;
	for(i = 1; i < MaxK; i++) p[i] = p[i - 1] * 233;
	for(i = 1; i <= n; i++) cnt[a[i] = read() + '0']++;
	while(q--) {
		int op = read();
		if(op == 1) merge();
		if(op == 2) split();
		if(op == 3) printf("%d\n", query());
	}
	return 0;
}

