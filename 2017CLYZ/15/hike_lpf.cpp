#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN = 300005;
int lc[MAXN], rc[MAXN], root[MAXN], fa[MAXN], size[MAXN], cnt[MAXN];
int fat[MAXN], sizet[MAXN], a[MAXN][3], T, ty, x, y;
int first[MAXN], next[MAXN << 1], go[MAXN << 1], t, top[MAXN], len;
int n, m, i, j, k, ans;
inline int get()
{
	char c;
	while ((c = getchar()) < 48 || c > 57);
	int res = c - 48;
	while ((c = getchar()) >= 48 && c <= 57)
		res = res * 10 + c - 48;
	return res;
}
inline void add(int x, int y)
{
	next[++t] = first[x]; first[x] = t; go[t] = y;
}
inline bool isroot(int x)
{
	return (lc[fa[x]] == x || rc[fa[x]] == x);
}
inline void rev(int x)
{
	swap(lc[x], rc[x]);
	cnt[x] ^= 1;
}
inline void putdown(int x)
{
	if (cnt[x])
	{
		if (lc[x]) rev(lc[x]);
		if (rc[x]) rev(rc[x]);
		cnt[x] = 0;
	}
}
inline void updata(int x)
{
	size[x] = size[lc[x]] + size[rc[x]] + 1;
}
inline void turn(int x)
{
	int y = fa[x], z = fa[y], b = 0;
	putdown(y); putdown(x);
	if (lc[y] == x) b = rc[x];
	else b = lc[x];
	if (b) fa[b] = y;
	fa[x] = z; fa[y] = x;
	if (z)
		if (lc[z] == y) lc[z] = x;
		else if (rc[z] == y) rc[z] = x;
	if (lc[y] == x) rc[x] = y, lc[y] = b;
	else lc[x] = y, rc[y] = b;
	updata(y);
}
inline void splay(int x)
{
	putdown(x);
	while (isroot(x))
	{
		if (isroot(fa[x]))
			if ((lc[fa[x]] == x) == (lc[fa[fa[x]]] == fa[x])) turn(fa[x]);
			else turn(x);
		turn(x);
	}
	updata(x);
}
inline void access(int x)
{
	int sb = 0;
	while (x)
	{
		splay(x);
		rc[x] = sb;
		sb = x;
		x = fa[x];
	}
}
inline void makeroot(int x)
{
	access(x);
	splay(x);
	rev(x);
}
inline void link(int x, int y)
{
	makeroot(x);
	fa[x] = y;
}
inline int query(int x, int y)
{
	makeroot(x);
	access(y);
	splay(y);
	return size[y] - 1;
}
inline int find(int x)
{
	if (x != fat[x]) fat[x] = find(fat[x]);
	return fat[x];
}
inline void dfs(int now, int jj)
{
	top[++len] = now;
	for(int i = first[now]; i; i = next[i])
		if (go[i] != jj) dfs(go[i], now);
}
int main()
{
	freopen("hike.in","r",stdin),freopen("hike.out","w",stdout);
	cin >> T;
	cin >> n >> m;
	for(i = 1; i <= n; i ++)
		fat[i] = i, a[i][0] = a[i][1] = i, sizet[i] = 1;
	ans = 0;
	while (m --)
	{
		ty = get();
		if (ty == 1)
		{
			x = get(); y = get();
			if (T) x ^= ans, y ^= ans;
			int xx = find(x), yy = find(y);
			if (xx == yy) continue;
			if (sizet[xx] > sizet[yy]) swap(xx, yy), swap(x, y);
			fat[xx] = yy; sizet[yy] += sizet[xx];
			len = 0; dfs(x, 0); link(x, y);
			for(i = 1; i <= len; i ++)
			{
				int v = top[i];
				int dis1 = query(v, a[yy][0]);
				int dis2 = query(v, a[yy][1]);
				if (dis1 >= dis2 && dis1 >= a[yy][2])
					a[yy][1] = v, a[yy][2] = dis1;
				else if (dis2 >= dis1 && dis2 >= a[yy][2])
					a[yy][0] = v, a[yy][2] = dis2;
			}
			add(x, y);
			add(y, x);
		}
		else
		{
			x = get();
			if (T) x ^= ans;
			int xx = find(x);
			ans = max(query(x, a[xx][0]), query(x, a[xx][1]));
			printf("%d\n", ans);
		}
	}
}

