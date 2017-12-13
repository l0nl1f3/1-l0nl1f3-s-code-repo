---
title: 2017-2018 Northeastern European Regional Contest (NEERC 17) Solutions
date: 2017-12-11 20:49:03
tags:
---

# A

## 题意

$q$ 次 ( $q \leq 2 * 10^5$ ) 操作

1. 插入一个圆心在(x, y)，半径为y的圆

2. 查询点(x, y)是否严格在圆内，若是则删除对应圆

保证圆圆不相交、不包含  

## 题解

容易发现，若在每个 $x$ 作垂直于 $x$ 的直线，则每条直线最多穿过 $\log_2 y$ 个圆

将每次操作1暴力操作到线段树上 $[x - r, x + r]$ 区间内，询问就把叶子到根路径上的圆全取出来暴力比较

复杂度 $O(q\log n)$
```C++
const int MaxN = 201234, MaxNode = MaxN * 40, U = 2e9;

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
					insert(rot, -U, U, x[p] - y[p], x[p] + y[p], p, 0);
					break;
				}
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
```
# B
 
## 题意

一个 $w\times h$ 的网格纸, 问是否能切出一块拼成 $a \times b \times c$ 的空心立方体

## 题解

对于切割仅存在两种情况, 即 $2a + 2b \leq h \& b + 2c \leq w$ 或 $a + c \leq h \& 3b + a + c \leq w$ 

```C++
bool chk(int a, int b, int c, int w, int h) {
	return (2 * a + 2 * b <= h && b * 2 + c <= w) || (a + c <= h && 3 * b + a + c <= w);
}

int main() {
	int a, b, c, w, h;
	cin >> a >> b >> c >> w >> h; 
	bool ans = chk(a, b, c, w, h) ||
	chk(a, c, b, w, h) ||
	chk(c, b, a, w, h) ||
	chk(c, a, b, w, h) ||
	chk(b, a, c, w, h) ||
	chk(b, c, a, w, h) ||
	chk(a, b, c, h, w) ||
	chk(a, c, b, h, w) ||
	chk(c, b, a, h, w) ||
	chk(c, a, b, h, w) ||
	chk(b, a, c, h, w) ||
	chk(b, c, a, h, w);
	if(ans) puts("Yes"); else puts("No");
	return 0;
}


```
# C

## 题意

给定一个联通有向图， 求一个保留 $2n$ 条边的方案, 满足仍然强联通

$4 < n \leq 10^5, m > 2n$

## 题解

任取一点 $x$， 求一个 $x$ 为根的 dfs 树，反图做一个同样的图，这样新图中任意点对 $(a, b)$ 均可通过以下路径互达 $a \to x \to b$ 

并起来即可，最大边数 $2(n - 1)$ 
```C++
const int MaxN = 101234;

int T, n, m, vis[MaxN], d[MaxN], u[MaxN], v[MaxN];
vector<pair<int, int> > f[MaxN], g[MaxN];

void dfs1(int x) {
	vis[x] = 1;
	for(auto y : f[x]) 
		if(!vis[y.fir]) {
			d[y.sec] = 1;
			dfs1(y.fir);
		}
}

void dfs2(int x) {
	vis[x] = 1;
	for(auto y : g[x]) 
		if(!vis[y.fir]) {
			d[y.sec] = 1;
			dfs2(y.fir);
		}
}

int main() {
	int i;
	T = read();
	while(T--) {
		n = read(); m = read();
		for(i = 1; i <= m; i++) {
			u[i]= read(); v[i] = read();
			f[u[i]].push_back(MP(v[i], i));
			g[v[i]].push_back(MP(u[i], i));
		}
		memset(d, 0, sizeof(d));
		memset(vis, 0, sizeof(vis));
		dfs1(1);
		memset(vis, 0, sizeof(vis));
		dfs2(1);
		int cnt = 0;
		for(i = 1; i <= m; i++) 
			if(!d[i]) printf("%d %d\n", u[i], v[i]), ++cnt >= m - 2 * n ? i = m : 0;
		for(i = 1; i <= n; i++) f[i].clear(), g[i].clear(); 
	}
	return 0;
}
```
# D

## 题意

给定你堆的积木在 $Oxy, Oxz, Oyz$ 三平面上的投影面积

构造原积木

## 题解 

在 $Oxy$ 上堆个平面图形 。。 。

```C++
pair<int, int> s[3]; int a, b, c;
vector<tuple<int, int, int> > v;	

void build1(int a, int b, int c) {
	for(int i = 0; i < a; i++) c--, v.emplace_back(0, i, 0);
	for(int i = 1; i < b; i++) c--, v.emplace_back(i, 0, 0);
	for(int i = 1; i < a && c; i++)
		for(int j = 1; j < b && c; j++)
			c--, v.emplace_back(j, i, 0);
}

void build2(int a, int b, int c) {
	for(int i = c; i < a; i++) v.emplace_back(0, i, 0);
	for(int i = c; i < b; i++) v.emplace_back(i, 0, 0);
	for(int i = 1; i < c; i++) v.emplace_back(i, c - i, 0);
}

int main() {
	cin >> s[0].fir >> s[1].fir >> s[2].fir;
	s[0].sec = 0; s[1].sec = 1; s[2].sec = 2;
	sort(s, s + 3);
	a = s[0].fir; b = s[1].fir, c = s[2].fir;
	if(c > a * b) return puts("-1"), 0;
	if(c >= a + b - 1)
		build1(a, b, c);
	else 
		build2(a, b, a + b - 1 - c);
	printf("%d\n", v.size());
	int p[3];
	for(auto i : v) {
		int x[3];
		tie(x[0], x[1], x[2]) = i;
		int ans[3];
		for(int i = 0; i < 3; i++) ans[s[i].sec] = x[i];
		printf("%d %d %d\n", ans[2], ans[1], ans[0]);
	}
	return 0;
}
```
# E

签到题
```C++
int n, a[1234], ans[1234];
map<int, int> s;
vector<int> v;
int main() {
	int i;
	n = read(); 
	for(i = 1; i <= n; i++) {
		a[i] = read();
		if(a[i] > 0)
			s[a[i]]++;
		if(a[i] < 0){
			if(s[-a[i]]) --s[-a[i]];
			else {
				if(v.size()) 
					ans[v.back()] = -a[i], v.pop_back();
				else 
					return puts("No"), 0;
			}
		}
		if(!a[i])
			v.push_back(i);
	}
	puts("Yes");
	for(i = 1; i <= n; i++) if(!a[i]) printf("%d ", max(ans[i], 1));
	return 0;
}

```
# F

## 题意

构造用最少的长度为 $n$ 的 $L$ 型通道使 $(0, 0)$ 和 $(a, b)$ 联通

## 题解

瞎贪心 。。  
```C++
#define Pii pair<int, int> 
#define P4 pair<Pii, Pii>
#define x1 fir.fir
#define y1 fir.sec
#define x2 sec.fir
#define y2 sec.sec
#define MP(x, y, z, w) make_pair(make_pair(x, y), make_pair(z, w))

int a, b, n, sga, sgb;
vector<P4> ans;

void solve() {
	sga = a > 0; if(!sga) sga = -1, a = -a;
	sgb = b > 0; if(!sgb) sgb = -1, b = -b;
	ans.clear();
	int x, y, rev; x = y = rev = 0;
	while(1) {
		if(a >= x + n && b >= y + n) {
			ans.emplace_back(MP(x + n - 1, y + n - 1, x, y));
			x += n - 1; y += n - 1;
			if(a > x + n - 1 && a - x > b - y) 
				++x, rev = 1;
			else
				++y, rev = 0;
			continue; 
		}
		if(a >= x + n) {
			ans.emplace_back(MP(x + n - 1, y + n - 1, x, y));
			x +=  n; rev = 1; continue;
		}
		if(b >= y + n) {
			ans.emplace_back(MP(x, y, x + n - 1, y + n - 1));
			y += n; rev = 0; continue;
		}
		if(!rev) 
			ans.emplace_back(MP(a, y + n - 1, a - n + 1, y));
		else
			ans.emplace_back(MP(x, b - n + 1, x + n -1, b));
		break;	
	}
	printf("%d\n", ans.size());
	for(auto x : ans) 
		printf("%d %d %d %d\n", x.x1 * sga, x.y1 * sgb, x.x2 * sga, x.y2 * sgb);
}
int main() {
	int T;
	cin >> T;
	while(T--) {
		cin >> a >> b >> n;
		solve();
	}
	return 0;
}

```
# G

## 题意

给定 $a_{1\ldots n}, b_{1\ldots n}, c_{1\ldots n}, r$, 两个可相交区间 $[x, x + r), [y, y + r)$ 的价值为

若一个数不在任何一个区间内，贡献为 $a_i$, 在一个为 $b_i$, 在两个为 $c_i$

求价值第 $K$ 小的区间对的价值 
 
## 题解 

二分答案 $s$ 求 $val \leq s$ 的方案有多少种

然后 $b_i -= a_i, c_i -= a_i$ 方便描述
 
区间不相交情况下，自右到左枚举 $y$，在前缀中查询有多少个 $x + r \leq y$ 且 $\sum_{i = x} ^ {x + r - 1} b_i \leq s - \sum_{i = y} ^ {y + r - 1} b_i$ 的 $x$ 即可

考虑存在区间相交的情况，我们这样定义区间对 $(x, y)$ 的价值

设 $f_x = \sum_{i = 1} ^ {x - 1} c_i - 2b_i + \sum_{i = x} ^ {x + r - 1} c_i - b_i$, 以及 $g_x = \sum_{i = 1} ^ {x - 1} 2b_i - c_i + \sum_{i = y}{y + r - 1} b_i$

这样 $f_y + g_x$ 该消的消掉。。 贡献也是对的，按上面那样枚举一个即可

复杂度 $O(nlog^2)$
 ```C++
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
```
# J

## 题意
 
带权无向图，求路径上前 $K$ 大边权和最短路

$n \leq 3000, m \leq 3000$

## 题解 

枚举第K大的边的边权 $W$，将原图中的长度为 $l_e$ 的边，边权修改为 $max(l_e - W, 0)$, 那么可以证明 $dis(1, n) + K * W$ 一定可以取到，取不到不会变优，复杂度 $O(m^2\log m)$

```C++
const int MaxN = 3123; 
int n, m, K, u[MaxN], v[MaxN], w[MaxN], p[MaxN];
vector<pair<int, int> > e[MaxN];

LL dis[MaxN];
priority_queue<pair<LL, int>, vector<pair<LL, int> >, greater<pair<LL, int>> > q;

int W;
LL dijk() {
	int i;
	for(i = 1; i <= n; i++) dis[i] = 1e16;
	dis[1] = 0; q.push(MP(0, 1));
	while(!q.empty()) {
		pair<LL, int> c = q.top(); q.pop();
		if(dis[c.second] < c.first) continue;
		for(auto y : e[c.second]) {
			int b = y.to;
			if(cmin(dis[b], dis[c.second] + max(y.v - W, 0)))
				q.push(MP(dis[b], b)); 
		}
	}
	return dis[n];
}
int main() {
	int i;
	n = read(); m = read(); K = read();
	for(i = 1; i <= m; i++) {
		int u = read(), v = read(), w = read();
		e[u].emplace_back(MP(v, w));
		e[v].emplace_back(MP(u, w));
		::u[i] = u; :: v[i] = v; :: w[i] = w; :: p[i] = i;
	}
	sort(p + 1, p + m + 1, [&] (int x, int y) {return w[x] < w[y]; });
	LL ans = dijk();
	for(i = 1; i <= m; i++) {
		int _ = p[i]; W = w[_];
		cmin(ans, dijk() + (LL) K * W);
	}
	cout << ans;
	return 0;
}

```
# L

## 题意

树上给定若干条链，问是否满足任意一对链，要么不相交，要么一个包含另一个
$n, m \leq 10^5$

## 题解

提取覆盖边后一定是若干条链，每条链上处理就变成区间问题，排序+bit或单调栈即可

```C++
const int MaxN = 101234, MaxL = 17;

int n, m, dep[MaxN], u[MaxN], v[MaxN], a[MaxN], b[MaxN], f[MaxN][MaxL], cnt[MaxN], c[MaxN], sig[MaxN];
vector<int> e[MaxN], g[MaxN], h[MaxN]; map<int, int> vis;

int in[MaxN], dn;
void dfs(int x, int fa = 0) {
	f[x][0] = fa; in[x] = ++dn;
	for(int i = 1; i < MaxL; i++) f[x][i] = f[f[x][i - 1]][i - 1];
	for(auto y : e[x]) {
		if(y == fa) continue;
		dep[y] = dep[x] + 1;
		dfs(y, x);
	}
} 

int deg[MaxN];
void addEdge(int x, int y) {
	++deg[x]; ++deg[y];
	g[x].emplace_back(y);
	g[y].emplace_back(x);
}

void dfs2(int x, int fa = 0) {
	for(auto y : e[x]) {
		if(y != fa) {
			dfs2(y, x);
			cnt[x] += cnt[y]; 
		}
	}
}

int lca(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = MaxL - 1, K = dep[x] - dep[y]; ~i; i--)
		if(K >> i & 1) x = f[x][i];
	if(x == y) 
		return y;
	for(int i = MaxL - 1; ~i; i--)
		if(f[x][i] != f[y][i])
			x = f[x][i], y = f[y][i];
	return f[x][0];
}

int clk, cn, L[MaxN], R[MaxN];
bool chk(int x, int fa = 0) {
	c[x] = 1; ++clk;
	for(auto z : h[x]) {
		if(!vis[z]) {
			vis[z] = ++cn;
			L[cn] = clk;
		}
		else 
			R[vis[z]] = clk;
	}
	for(auto y : g[x]) {
		if(y == fa) continue;
		chk(y, x);
	} 
}

int s[MaxN];

struct bit{
	int bit[MaxN], t[MaxN], T;
	
	void clr() {
		++T;
	}
	
	int query(int p) {
		int ans = 0;
		for(; p; p -= p & -p) {
			if(t[p] != T) t[p] = T, bit[p] = 0;
			ans += bit[p];
		}
		return ans;
	}
	
	void add(int p) {
		for(; p < MaxN; p += p & -p) {
			if(t[p] != T) t[p] = T, bit[p] = 0;
			bit[p]++;
		}
	}
}T;
bool check() {
	int i, j, k;
	T.clr();
	for(i = 1; i <= cn; i = j) {
		for(j = i; j <= cn && L[i] == L[j]; j++)
			if(T.query(R[j] - 1) - T.query(L[j] - 1) > 0)
				return 0;
		for(j = i; j <= cn && L[i] == L[j]; j++) T.add(R[j]);
	}
	return 1;
}
int main() {
	int i, j;
	n = read(); m = read();
	for(i = 1; i < n; i++) {
		a[i] = read(); b[i] = read();
		e[a[i]].push_back(b[i]);
		e[b[i]].push_back(a[i]); 
	}
	dfs(1);
	for(i = 1; i <= m; i++) {
		u[i] = read(); v[i] = read();
		int w = lca(u[i], v[i]);
		h[u[i]].emplace_back(i);
		h[v[i]].emplace_back(i);
		cnt[w] -= 2; cnt[u[i]]++; cnt[v[i]]++;
	}
	dfs2(1);
	for(i = 1; i <= n; i++) if(f[i][0] && cnt[i]) addEdge(f[i][0], i);
	for(i = 1; i <= n; i++) if(deg[i] > 2) return puts("No"), 0;
	
	for(i = 1; i <= n; i++) 
		if(!c[i] && deg[i] == 1) {
			clk = cn = 0;
			vis.clear();
			chk(i);
			if(!check()) return puts("No"), 0;
		}
	puts("Yes");
	return 0;
}

```
# 总结

H, I, K坑着

 