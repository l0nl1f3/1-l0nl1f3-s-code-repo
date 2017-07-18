#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;
typedef long long LL;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int inp() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 1234 , MaxM = 12345, MaxV = MaxM, MaxE = (MaxN * 3 + MaxM) << 1;
namespace min_cost_flow{
	struct edge{
		int to, nxt, cap, cost;
	}e[MaxE]; int cnt = 1, lst[MaxV]; queue<int>q;
	void ins(int a, int b, int c, int d){ e[++cnt] = (edge){b, lst[a], c, d}; lst[a] = cnt;}
	void lnk(int a, int b, int c, int d){ ins(a, b, c, d); ins(b, a, 0, -d);}
	int dis[MaxV], pre[MaxV], inq[MaxV];
	bool spfa(int s, int t){
		fill(dis, dis + t + 1, ~0U>>2);
		dis[s] = 0; q.push(s);inq[s] = 1;
		while(!q.empty()){
			int c = q.front();q.pop(); inq[c] = 0;  
			for(int i = lst[c], b; b = e[i].to, i; i = e[i].nxt){
				if(e[i].cap > 0 && cmin(dis[b], dis[c] + e[i].cost)){
					pre[b] = i;
					if(!inq[b]) q.push(b), inq[b] = 1;
				}
			}
		}
		return dis[t] < (~0U >> 2);
	}
	bool vis[MaxV];int cost = 0;
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
	pair<int, int> mcf(int s, int t){
		int ans = 0;
		while(spfa(s, t)) 
			ans += dfs(s, t, ~0U >> 1); 
		return make_pair(ans, cost);
	}
} 
using min_cost_flow::lnk;
using min_cost_flow::mcf;

int n, m, t, l[MaxM], r[MaxM], c[MaxM], a[MaxN];

int main() {
	int i, o;
	
	n = inp(); m = inp(); t = n + 2;
	for(i = 1; i <= n; i++) a[i] = inp();
	for(i = 1; i <= m; i++) l[i] = inp(), r[i] = inp(), c[i] = inp();
	for(i = 1; i <= m; i++)
		lnk(l[i], r[i] + 1, ~0U >> 1, c[i]);
	for(i = 1; i <= n + 1; i++) {
		o = a[i] - a[i - 1];
		if(o < 0) lnk(i, t, -o, 0);
		else lnk(0, i, o, 0);
		if(i > 1) lnk(i, i - 1, ~0U >> 1, 0);
	}
	printf("%d\n", mcf(0, t).second);
	return 0;
}

