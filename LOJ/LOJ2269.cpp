#include <bits/stdc++.h>

#define fi first
#define se second
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

const int MaxM = 128, MaxN = 31234, P = 1e4 + 7, i2 = 5004;

int n, m, k, q, a[MaxN], w[MaxN][MaxM], siz[MaxN], son[MaxN], up[MaxN], but[MaxN], dfn, ord[MaxN], pos[MaxN], fa[MaxN];

vector <int> e[MaxN];

int exp(int a, int n) {
	int res = 1;
	for (; n; n >>= 1) {
		if(n & 1)
			res = res * a % P;
		a = a * a % P; 
	} 
	return res;
}
void fwt(int f[], int op = 0) {
	for (int i = 1; i <= m; i <<= 1)
		for (int j = 0; j < m; j++) if(j & i) {
			int l = f[j ^ i], r = f[j];
			f[j ^ i] = (l + r) % P;
			f[j] = (l - r + P) % P;
			if(op) {
				f[j ^ i] = f[j ^ i] * i2 % P;
				f[j] = f[j] * i2 % P;
			}
		} 
} 

void dfs(int x, int fa = 0) {
	siz[x] = 1;
	for (auto y : e[x]) {
		if(y != fa) {
			:: fa[y] = x;
			dfs(y, x);
			siz[x] += siz[y];
			if(siz[y] > siz[son[x]]) 
				son[x] = y;
		}
	}
}

int cnt[MaxN][MaxM], f[MaxN][MaxM], g[MaxN][MaxM]; pair<int, int> h[MaxN][MaxM];

int ans[MaxM], inv[P];

void dfs2(int x, int t) {
	up[x] = t; pos[ord[x] = ++dfn] = x; but[t] = x;
	if(son[x]) dfs2(son[x], t);
	for (int i = 0; i < m; i++) h[x][i].fi = 1;
	for (auto y : e[x])
		if(y != son[x] && y != fa[x]) {
			dfs2(y, y);
			for (int i = 0; i < m; i++) {
				if(f[y][i] + 1 < P)
					h[x][i].fi = h[x][i].fi * (f[y][i] + 1) % P;
				else 
					h[x][i].se++;
			}
		} 
	for (int i = 0; i < m; i++) {
		if(h[x][i].se)
			f[x][i] = 0;
		else 
			f[x][i] = w[x][i] * h[x][i].fi % P * (f[son[x]][i] + 1) % P;
		ans[i] = (ans[i] + f[x][i]) % P; 
	}
}

#define lson p << 1, l, l + r >> 1
#define rson p << 1 | 1, (l + r >> 1) + 1, r
 
struct info {
	int s[MaxM], l[MaxM], r[MaxM], mul[MaxM]; 	
	void init(int x) {
		x = pos[x];
		for (int i = 0; i < m; i++) 
			if(h[x][i].se)
				s[i] = l[i] = r[i] = mul[i] = 0;
			else
				s[i] = l[i] = r[i] = mul[i] = w[x][i] * h[x][i].fi % P;
	}
} seg[MaxN << 2];

info operator + (info x, info y) {
	info c; 
	for (int i = 0; i < m; i++) {
		c.s[i] = (x.s[i] + y.s[i] + x.r[i] * y.l[i]) % P;
		c.l[i] = (x.l[i] + x.mul[i] * y.l[i]) % P;
		c.r[i] = (y.r[i] + y.mul[i] * x.r[i]) % P;
		c.mul[i] = x.mul[i] * y.mul[i] % P; 
	}	
	return c;
}

void build(int p, int l, int r) {
	if(l == r) 
		seg[p].init(r);
	else {
		build(lson), build(rson); 
		seg[p] = seg[p << 1] + seg[p << 1 | 1];
	}             
}

void modify(int p, int l, int r, int x) {
	if(l == r) 
		seg[p].init(r);
	 else {
	 	if(x <= (l + r >> 1))
	 		modify(lson, x);
	 	else
	 		modify(rson, x);
	 	seg[p] = seg[p << 1] + seg[p << 1 | 1];
	 }
}

info tmp;

void query(int p, int l, int r, int a, int b) {
	if(b < l || a > r) return;
	if(a <= l && r <= b) {
		if(l == a)
			tmp = seg[p];
		else 
			tmp = tmp + seg[p];
		return;
	}
	query(lson, a, b);
	query(rson, a, b);
}

void cut(int t, int o) {
	query(1, 1, n, ord[t], ord[but[t]]);
	for (int i = 0; i < m; i++) 
		ans[i] = (ans[i] + o * tmp.s[i] + P) % P;
	if(fa[t])
		for (int i = 0; i < m; i++) {
			int p = tmp.l[i] + 1;
			if(p < P) 
				h[fa[t]][i].fi = h[fa[t]][i].fi * (o > 0 ? p : inv[p]) % P;
			else 
				h[fa[t]][i].se += o;
		}
		
}

void modify(int x) {
	while(x) {
		cut(up[x], -1);
		modify(1, 1, n, ord[x]);
		cut(up[x], 1);
		x = fa[up[x]];
	}
}

int main() {
	n = read(); m = read();
	k = 0; while ((1 << k) < m) ++k; m = 1 << k;
	for (int i = 1; i <= n; i++) {
		w[i][read()] = 1; fwt(w[i]);
	}
	for (int i = 1; i < n; i++) {
		int u = read(), v = read();
		e[u].pb(v); e[v].pb(u);
	}
	dfs(1); dfs2(1, 1); build(1, 1, n);
	
	inv[0] = 1;
	for (int i = 1; i < P; i++) 
		inv[i] = exp(i, P - 2);
		
	q = read();
	while(q--) {
		char s[7]; scanf("%s", s);
		if(*s == 'Q') {
			int k = read(), t[MaxM];
			for (int i = 0; i < m; i++) 
				t[i] = ans[i];
			fwt(t, 1);
			printf("%d\n", t[k]);
		} else {
			int x = read(), y = read();
			memset(w[x], 0, sizeof(w[x]));
			w[x][y] = 1; fwt(w[x]); modify(x); 
		}
	}
	return 0;
}
