#include <bits/stdc++.h>

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define SZ(x) (x).size()
#define pii pair<int, int> 
#define ALL(x) x.begin(), x.end()

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

const int MaxN = 1001234, Logn = 15;

int n, m, K, val[MaxN];

vector <pii> e[MaxN], in[MaxN], out[MaxN];

vector <int> g[MaxN]; 

void insert(int a, int b, int c = 0) {
//	cout << a << " " << b << " " << c << endl;
	e[a].pb(mp(b, c));
}

int fa[MaxN / 10][Logn], dep[MaxN], ord[MaxN], dfn;

void dfs(int x) {
	ord[x] = ++dfn;
	for (int i = 1; i < Logn; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (auto y : g[x]) {
		dep[y] = dep[x] + 1; fa[y][0] = x; dfs(y);
	} 
}

int lca(int x, int y) {
	if(dep[x] < dep[y])
		swap(x, y);
	int K = dep[x] - dep[y];
	for (int i = Logn - 1; ~i; i--)
		if(K >> i & 1)
			x = fa[x][i];
	if(x == y) return dep[x];
	for (int i = Logn - 1; ~i; i--) 
		if(fa[x][i] != fa[y][i])
			x = fa[x][i], y = fa[y][i];
	return dep[fa[x][0]]; 
}

pii l[MaxN], r[MaxN]; int dis[MaxN], vis[MaxN], d[MaxN];

priority_queue<pii, vector<pii>, greater<pii> > q;
 
int main() {
	int T = read();
	while(T--) {
		n = read(); int nn = m = read(); K = read();
		for (int i = 1; i <= n; i++) in[i].clear(), out[i].clear();
		for (int i = 1; i <= K; i++) g[i].clear();
		for (int i = 1; i <= m; i++) {
			int a = read(), b = read(), c = read(); d[i] = read();
			out[a].pb(mp(i, d[i])); in[b].pb(mp(i, d[i])); val[i] = c;
			if(a == 1) {
				q.push(mp(0, i));
				dis[i] = val[i];
			}
		}
		
		for (int i = 1; i < K; i++) {
			int a = read(), b = read(), c = read();
			g[a].pb(b); 
		}
		dfs(1); 
		for (int i = 1; i <= n; i++) {
			vector <pii> v;
			if(!SZ(in[i]) || !SZ(out[i]))
				continue;
			for (auto x : in[i])
				v.pb(mp(x.fi, 0));
			for (auto x : out[i])
				v.pb(mp(x.fi, 1));
			sort(ALL(v), [&] (pii x, pii y) {return ord[d[x.fi]] < ord[d[y.fi]]; });
			for (int j = 0; j < SZ(v); j++) {
				l[j].fi = ++nn; l[j].se = ++nn;
				r[j].fi = ++nn; r[j].se = ++nn;
				if(j) {
					insert(l[j - 1].fi, l[j].fi);
					insert(r[j - 1].fi, r[j].fi);
					insert(l[j].se, l[j - 1].se);
					insert(r[j].se, r[j - 1].se);
				}
				if(v[j].se)
					insert(r[j].fi, v[j].fi), insert(r[j].se, v[j].fi);
				else
					insert(v[j].fi, l[j].fi), insert(v[j].fi, l[j].se);  
			}
			for (int j = 0; j + 1 < SZ(v); j++) {
				int p = lca(d[v[j].fi], d[v[j + 1].fi]);
				insert(l[j].fi, r[j + 1].fi, p);
				insert(l[j + 1].se, r[j].se, p);
			}
		}
		for (int i = 1; i <= nn; i++) 
			if(!dis[i])
				dis[i] = 1e9;
				
		while(!q.empty()) {
			int c = q.top().se; q.pop(); 
			if(vis[c]) continue; vis[c] = 1;
			for (auto x : e[c]) {
				int b = x.fi;
				if(cmin(dis[b], dis[c] + x.se + val[b]))
					q.push(mp(dis[b], b));
			}
		}
		for (int i = 2; i <= n; i++) {
			int ans =	 1e9;
			for (auto x : in[i]) 
				cmin(ans, dis[x.fi]);
			printf("%d\n", ans);
		}
		for (int i = 1; i <= nn; i++) e[i].clear(), dis[i] = vis[i] = 0;
	}
	return 0;
}




