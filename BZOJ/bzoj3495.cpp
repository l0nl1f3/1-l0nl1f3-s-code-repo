#include <bits/stdc++.h>

#define I first
#define O second
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
const int MaxN = 1001234, MaxV = 6001234, MaxE = MaxN * 24;
int q[MaxV], vis[MaxV], fa[MaxV], qt;
struct Graph{
	struct edge{
		int to, nxt;
	}e[MaxE]; int cnt, lst[MaxV];
	void ins(int a, int b){ 
		if(cnt == MaxE - 1) while(1);
		e[++cnt] = (edge){b, lst[a]};lst[a] = cnt;
	}
	void dfs(int x) {
		vis[x] = 1;
		for(int i = lst[x]; i; i = e[i].nxt) if(!vis[e[i].to]) dfs(e[i].to);
		q[++qt] = x; 
	} 
	void dfs2(int x,int y){
		vis[x] = 0;  fa[x] = y;
		for(int i = lst[x]; i; i = e[i].nxt)
			if(vis[e[i].to])
				dfs2(e[i].to, y);
	}
}G, rG; 
void ins(int a, int b){
	G.ins(a, b);
	rG.ins(b, a); 
}

int n, m, K, cnt;
pair<int, int> c[MaxN], suf[MaxN], pre[MaxN]; 
void New(int & x){ 
	x = ++cnt;
	if(cnt >= MaxV) while(1);
}
void New(pair<int, int> & pa) {
	New(pa.O); New(pa.I);
}
int main() {
	int i;
	n = inp(); m = inp(); K = inp();
	for(i = 1; i <= n; i++) New(c[i]);
	for(i = 1; i <= m; i++) {
		int x = inp(), y = inp();
		ins(c[x].O, c[y].I);
		ins(c[y].O, c[x].I);
	} 
	for(i = 1; i <= K; i++){
		int p = inp();
		for(int o = 1; o <= p; o++){
			New(pre[o]); New(suf[o]); 
			int x = inp();
			ins(c[x].I, pre[o].I); ins(c[x].I, suf[o].I);
			ins(pre[o].O, c[x].O); ins(suf[o].O, c[x].O);
		}
		for(int o = 2; o <= p; o++){
			ins(pre[o - 1].I, pre[o].I);
			ins(pre[o - 1].I, suf[o].O);
			ins(pre[o - 1].O, suf[o].I);
			ins(suf[o].I, suf[o - 1].I);
			ins(suf[o].I, pre[o - 1].O);
			ins(suf[o].O, pre[o - 1].I);
		}
	}
	for(i = 1; i <= cnt; i++) if(!vis[i]) G.dfs(i);
	for(i = cnt; i; i--) if(vis[q[i]]) rG.dfs2(q[i], q[i]);
	for(i = 1; i < n; i += 2) if(fa[i] == fa[i + 1]) return puts("NIE"),0;
	puts("TAK"); 
	return 0;
}



