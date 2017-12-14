#include <bits/stdc++.h>

#define fir first
#define sec second
#define LONG_LONG_MAX (1ll << 60)
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

const int MaxN = 101234, MaxM = 201234, MaxV = MaxN, MaxE = MaxM << 1;

int E[MaxN];

namespace min_cost_flow{
	struct edge{
		int to, nxt, cap, cost;
	}e[MaxE]; int cnt = 1, lst[MaxV]; queue<int>q;
	void ins(int a, int b, int c, int d){ e[++cnt] = (edge){b, lst[a], c, d}; lst[a] = cnt;}
	int lnk(int a, int b, int c, int d){ ins(a, b, c, d); ins(b, a, 0, -d); return cnt - 1; }
	LL dis[MaxV]; int pre[MaxV], inq[MaxV];
	bool spfa(int s, int t){
		fill(dis, dis + t + 1, -(LONG_LONG_MAX / 10));
		dis[s] = 0; q.push(s);inq[s] = 1;
		while(!q.empty()){
			int c = q.front();q.pop(); inq[c] = 0;  
			for(int i = lst[c], b; b = e[i].to, i; i = e[i].nxt){
				if(e[i].cap > 0 && cmax(dis[b], dis[c] + e[i].cost)){
					pre[b] = i;
					if(!inq[b]) q.push(b), inq[b] = 1;
				}
			}
		}
		return dis[t] > -(LONG_LONG_MAX / 10);
	}
	bool vis[MaxV]; LL cost = 0;
	int dfs(int v, int t, int f){
		if(v == t) return f;
		int used = 0; vis[v] = 1;
		for(int i = lst[v], b; b = e[i].to, i; i = e[i].nxt){
			if(e[i].cap > 0 && !vis[b] && dis[b] == dis[v] + e[i].cost){
				int w = dfs(b, t, min(f - used, e[i].cap));
				e[i].cap -= w; e[i ^ 1].cap += w;
				used += w; cost += e[i].cost * w;
			}
		}
		vis[v] = 0;
		return used;
	} 
	pair<int, LL> mcf(int s, int t){
		int ans = 0;
		while(spfa(s, t)) 
			ans += dfs(s, t, ~0U >> 1); 
		return make_pair(ans, cost);
	}
} 
using min_cost_flow :: lnk;
using min_cost_flow :: mcf;

int n, K, m_e, m_s, u_e, s[MaxN], e[MaxN];
int main() {
	//freopen("delight.in", "r", stdin);
	//freopen("delight.out", "w", stdout);
	
	int i;
	n = read(); K = read(); m_s = read(); m_e = read(); m_e = K - m_e;
	for(i = 1; i <= n; i++) s[i] = read();
	for(i = 1; i <= n; i++) e[i] = read();
	int S = 0, T = n - K + 3;
	lnk(S, 1, m_e, 0);
	lnk(T - 1, T, m_e, 0); 
	for(i = 1; i <= n; i++) {
		int a = max(1, i - K + 1);
		int b = min(i + 1, n - K + 2);
		E[i] = lnk(a, b, 1, s[i] - e[i]);
	}
	for(i = 1; i <= n - K + 1; i++) 
		lnk(i, i + 1, m_e - m_s, 0);
	LL ans = mcf(S, T).sec;
	for(i = 1; i <= n; i++) ans += e[i];
	cout << ans << endl;
	for(i = 1; i <= n; i++) {
		int t = s[i] - e[i];
		if(!min_cost_flow :: e[E[i]].cap)
			putchar('S');
		else
			putchar('E');
	}
	return 0;
}

