#include<bits/stdc++.h>
 
#define fir first
#define sec second
using namespace std;
typedef long long LL;
 
template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int read() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}
 
const int MaxN = 25, MaxV = MaxN * MaxN, MaxE = MaxV * MaxV * 10;
 
namespace dinic{
	struct edge{
		int to, nxt, cap;
	}e[MaxE]; int cnt = 1, lst[MaxV];
	void ins(int a, int b, int c){ e[++cnt] = (edge){b, lst[a], c}; lst[a] = cnt;}
	void lnk(int a, int b, int c = 1){ ins(a, b, c); ins(b, a, 0);}
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
 
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int n, m; char a[MaxN][MaxN];
 
#define G(i, j) ((i - 1) * m + j)
 
int main() {
	int i, j;
	n = read(); m = read();
	for(i = 1; i <= n; i++) 
		for(j = 1; j <= m; j++) {
			char s[3]; scanf("%s", s);
			a[i][j] = s[0];
		}	
	int S = 0, T = n * m + 1;
	for(i = 1; i <= n; i++)
		for(j = 1; j <= m; j++) 
			if(a[i][j] == 'a')
				lnk(S, G(i, j));
	for(char c = 'a'; c < 'd'; c++)
		for(i = 1; i <= n; i++)
			for(j = 1; j <= m; j++) {
				if(a[i][j] == c)
				for(int d = 0; d < 4; d++){
					int ni = i + dx[d];
					int nj = j + dy[d];
					if(ni > 0 && ni <= n && nj > 0 && nj <= m && a[ni][nj] == a[i][j] + 1)
						lnk(G(i, j), G(ni, nj));
				}
			}
	
	for(i = 1; i <= n; i++)
		for(j = 1; j <= m; j++) 
			if(a[i][j] == 'd')
				lnk(G(i, j), T);
	printf("%d\n", max_flow(S, T));
	return 0;
} 
