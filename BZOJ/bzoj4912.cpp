#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;

typedef long long LL;

template <typename T> inline bool cmin(T & a, const T &b) { return a > b ? a = b, 1 : 0; }
template <typename T> inline bool cmax(T & a, const T &b) { return a < b ? a = b, 1 : 0; }

int getint() {
	int x = 0, f = 1; char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 101234;
const int MaxNode = 10001234, MaxLog = 20;

const LL LLinf = (1ll << 60);
 
int n, m, K;

struct edge{
	int to, nxt, w;
};
	
struct Shortest_Path {
	int n, cnt, lst[MaxN];
	edge e[MaxN]; 
	void ins(int a, int b, int c){
		e[++cnt] = (edge){b, lst[a], c}; lst[a] = cnt; 
	}
	
	struct vertex {
		int a; LL l;
		bool operator < (const vertex & b) const {
			return l > b.l;		
		}
		vertex() {}
		vertex(int x, LL l) : a(x), l(l) {}
	};
	
	LL dis[MaxN]; bool vis[MaxN];
	priority_queue<vertex> q;
	void dijk(int s) {
		int i;
		for(i = 1; i <= n; i++) vis[i] = 0, dis[i] = LLinf;
		q.push(vertex(s, 0)); dis[s] = 0; 
		while(!q.empty()) {
			int c = q.top().a; q.pop();
			if(vis[c]) continue; vis[c] = 1;
			for(i = lst[c]; i; i = e[i].nxt) {
				int b = e[i].to;
				if(cmin(dis[b], dis[c] + e[i].w))
					q.push(vertex(b, dis[b]));
			}
		}	
	}
}sp;

int u[MaxN], v[MaxN], w[MaxN], x[MaxN];
 
edge e[MaxN]; int lst[MaxN], cnt, f[MaxN][MaxLog], dep[MaxN], L[MaxN], R[MaxN], dn;

void ins(int a, int b) {
	e[++cnt] = (edge){b, lst[a], 0}; lst[a] = cnt;
}

void dfs(int x) {
	int i;
	L[x] = ++dn;
	for(i = 1; i < MaxLog; i++) f[x][i] = f[f[x][i - 1]][i - 1];
	for(i = lst[x]; i; i = e[i].nxt) {
		int b = e[i].to;
		f[b][0] = x;
		dep[b] = dep[x] + 1;
		dfs(b);
	}
	R[x] = dn;
}

int lca(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = MaxLog - 1; ~i; i--)
		if(dep[x] - dep[y] >= (1 << i)) x = f[x][i];
	if(x ==  y) return x;
	for(int i = MaxLog - 1; ~i; i--)
		if(f[x][i] != f[y][i])
			x = f[x][i], y = f[y][i];
	return f[x][0];	
}

bool cmp(int x, int y) {
	return L[x] < L[y];
}


struct Vtree {
	edge e[MaxN]; int cnt, lst[MaxN];
	void ins(int a, int b) {
		e[++cnt] = (edge){b, lst[a], 0}; lst[a] = cnt;
	}
	
	int sn, s[MaxN];
	void build(int x[], int n) {
		int i; sn = 0;
		for(i = 1; i <= n; i++) 
			if(i == 1 || x[i] != x[i - 1]) {
				while(sn && (L[x[i]] < L[s[sn]] || L[x[i]] > R[s[sn]])) sn--;
			} 
	}
}T;
int head[MaxN], nxt[MaxN], ecnt;
int t[MaxN], tn; 
void get_answer(int p) {
	int i; tn = 0;
	for(i = head[p]; i; i = nxt[i]) t[++tn] = x[i];
	if(p == 1) t[++tn] = x[0];
	if(!tn) return;
	sort(t + 1, t + tn + 1, cmp);
	for(i = 1; i < tn; i++)
		t[i + tn] = lca(t[i], t[i + 1]);
	sort(t + 1, t + tn * 2, cmp);
	T.build(t, tn * 2 - 1);
}
void solve() {
	int i;
	n = getint(); m = getint(); K = getint();
	v[0] = x[0] = 1;
	for(i = 1; i <= m; i++) {
		int a = getint(), b = getint(), c = getint(), d = getint();
		u[i] = v[i + m] = a;
		v[i] = u[i + m] = b;
		w[i] = w[i + m] = c;
		x[i] = x[i + m] = d;
		
		nxt[i] = head[u[i]];
		head[u[i]] = i;
		nxt[i + m] = head[v[i]];
		head[v[i]] = i + m;
	}
	
	for(i = 1; i < K; i++) {
		int u = getint(), v = getint(); getint();
		ins(u, v);
	}
	
	dfs(1);
	
	for(i = 1; i <= m; i++) 
		sp.ins(i, i + 1 + m, w[i - 1]);

	for(int p = 1; p <= n; p++) get_answer(p);
}
int main(){
	int T = getint();
	while(T--) 
		solve();
	return 0;
}





