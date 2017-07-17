#include<bits/stdc++.h>

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
const int MaxN = 123, MaxV = MaxN * MaxN, MaxE = MaxN * MaxN * 10;
namespace dinic{
	struct edge{
		int to, nxt, cap;
	}e[MaxE]; int cnt = 1, lst[MaxV];
	void ins(int a, int b, int c){ e[++cnt] = (edge){b, lst[a], c}; lst[a] = cnt;}
	void lnk(int a, int b, int c){ ins(a, b, c); ins(b, a, 0);}
	int h[MaxV]; queue<int>q;
	bool bfs(int s, int t){
		memset(h, -1, sizeof(h));
		h[s] = 0; q.push(s);
		while(!q.empty()){
			int c = q.front(); q.pop();
			for(int i=lst[c], b; b = e[i].to, i; i = e[i].nxt){
				if(!~h[b] && e[i].cap > 0){
					h[b] = h[c] + 1;
					q.push(b);
				}
			}
		}
		return ~h[t];
	}
	int dfs(int v, int t, int f){
		if(v == t) return f;
		int used = 0, w;
		for(int i = lst[v], b; b = e[i].to, i; i = e[i].nxt)
			if(h[b] > h[v] && e[i].cap > 0){
				w = dfs(b, t, min(f - used, e[i].cap));
				e[i].cap -= w; e[i ^ 1].cap += w;
				if((used += w) == f) return f; 
			}
		if(!used) h[v] = -1;
		return used;
	}
	int max_flow(int s, int t){
		int ans = 0;
		while(bfs(s, t))
			ans += dfs(s, t, ~0U>>1);
		return ans;	
	} 
}
using dinic::lnk;
using dinic::max_flow;
#define D(i, j) ((i - 1) * (m + 1) + j)
int f[MaxN][MaxN], n, m, K;
int main() {
	int i, j;
	n = inp(); m = inp(); K = inp();
	for(i = 1; i <= n; i++) for(j = 1; j <= m; j++) f[i][j] = inp();
	for(i = 1; i <= n; i++) {
		lnk(0, D(i, 0), ~0U >> 1);
		for(j = 1; j <= m; j++) 
			lnk(D(i, j - 1), D(i, j), ~f[i][j] ? 100 - f[i][j] : ~0U >> 1);
		lnk(D(i, m), n * (m + 1) + 1, ~0U >> 1);
	}
	for(i = 1; i <= K; i++){
		int a = inp(), b = inp();
		for(j = 0; j < m; j++) lnk(D(a, j), D(b, j + 1), ~0U >> 1);
	}
	printf("%.2lf", (100 * n - max_flow(0, n * (m + 1) + 1)) / (double)n);
	return 0;
}



