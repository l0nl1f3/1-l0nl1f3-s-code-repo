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

const int MaxN = 555, MaxM = 4123, MaxV = 555, MaxE = 8888;
struct edge{ 
	int to, nxt;
}e[MaxE]; int cnt, lst[MaxV];

void ins(int a, int b){
	e[++cnt] = (edge){b, lst[a]}; lst[a] = cnt;
}
void lnk(int a, int b){
	ins(a, b);
	ins(b, a);
}

int n, m, w[MaxN], c[MaxN], d[MaxN];
int siz[MaxN], mark[MaxN], hug[MaxN], del[MaxE], rot, N;
int f[MaxN][MaxM], ans = 0;	

void dfs1(int x, int fa = 0){
	siz[x] = 1; hug[x] = 0;
	for(int i = lst[x], b; b = e[i].to, i; i = e[i].nxt)
		if(b != fa && !del[i]){
			dfs1(b, x);
			siz[x] += siz[b];
			cmax(hug[x], siz[b]);
		}
	cmax(hug[x], N - siz[x]);
	if(hug[x] < hug[rot]) rot = x;
}

void solve(int x, int fa, int m){
	int i, j, k, V, W;
	for(i = 0, k = d[x]; k; i++){
		if((1 << i) <= k){
			V = w[x] << i; W = c[x] << i;
			k -= (1 << i);
		}else
			V = w[x] * k, W = c[x] * k, k = 0;
		for(j = m; j >= W; j--) cmax(f[x][j], f[x][j - W] + V);
	} 
	for(i = lst[x]; k = e[i].to, i; i = e[i].nxt){
		if(!del[i] && k != fa){
			for(j = 0; j <= m - c[k]; j++) f[k][j] = f[x][j] + w[k];
			if(m > c[k]) solve(k, x, m - c[k]);
			for(j = c[k]; j <= m; j++)
				cmax(f[x][j], f[k][j - c[k]]);
		}
	}
}
void decomp(int x){
	for(int i = 0; i <= m - c[x]; i++) f[x][i] = w[x];  
	if(m > c[x]) solve(x, 0, m - c[x]);
	for(int i = 0; i <= m - c[x]; i++) cmax(ans, f[x][i]);
	for(int i = lst[x], b; b = e[i].to, i; i = e[i].nxt){
		if(!del[i]){
			del[i ^ 1] = 1;
			hug[0] = N = siz[b]; rot = 0;
			dfs1(b, 0); 
			decomp(rot);
		}
	}
}
int main() {
	int i;
	int T = inp();
	while(T--){
		cnt = 1; memset(lst, 0, sizeof(lst)); 
		n = inp(); m = inp();
		for(i = 1; i <= n; i++) w[i] = inp();
		for(i = 1; i <= n; i++) c[i] = inp();
		for(i = 1; i <= n; i++) d[i] = inp() - 1;
		
		for(i = 1; i < n; i++){
			int u = inp(), v = inp();
			lnk(u, v);
		}
		N = hug[0] = n; rot = 0;
		dfs1(1, 0); 
		decomp(1);
		printf("%d\n", ans), ans = 0;
		memset(del, 0, sizeof(del)); 
	} 
	return 0;
}



