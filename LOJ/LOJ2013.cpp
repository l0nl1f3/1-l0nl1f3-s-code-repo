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

struct Base {
	LL b[64]; int pc; 
	Base() {
		pc = 0;
		for(int i = 0; i <= 60; i++) b[i] = 0;
	}
	
	void append(LL x) {
		for(int i = 60; ~ i; i--)
			if(x >> i & 1)
				if(!b[i]) {
					b[i] = x; ++pc;
					break;
				}
				else {
					x ^= b[i];
					if(!x) break;
				}
	}
	
	LL eval() {
		LL ans = 0;
		for(int i = 60; ~ i; i--)
			if((ans ^ b[i]) > ans)
				ans ^= b[i];
		return ans;
	}
};

Base merge(Base x, Base y) {
	for(int i = 0; i <= 60; i++)
		if(x.b[i])
			y.append(x.b[i]);
	return y;
}

const int MaxN = 21234, MaxL = 16;

vector <int> e[MaxN];

Base c[MaxN][MaxL]; int f[MaxN][MaxL], dep[MaxN]; LL g[MaxN];

void dfs(int x, int fa = 0) {
	c[x][0].append(g[x]);
	f[x][0] = fa;
	
	for(int i = 1; i < MaxL; i++) {
		f[x][i] = f[f[x][i - 1]][i - 1];
		c[x][i] = merge(c[x][i - 1], c[f[x][i - 1]][i - 1]);
	}
	
	for(auto b : e[x]) 
		if(b != fa) {
			dep[b] = dep[x] + 1;
			dfs(b, x);
		}
} 

LL query(int x, int y) {
	Base ans;
	if(dep[x] < dep[y]) swap(x, y);
	
	int k = dep[x] - dep[y];
	for(int i = MaxL - 1; ~ i; i--) 
		if(k >> i & 1) {
			ans = merge(ans, c[x][i]);
			x = f[x][i];
		}
		
	if(x != y) { 
		for(int i = MaxL - 1; ~ i; i--) 
			if(f[x][i] != f[y][i]) {
				ans = merge(ans, c[x][i]);
				ans = merge(ans, c[y][i]);
				x = f[x][i]; y = f[y][i];
			}
			
		ans.append(g[x]);
		ans.append(g[y]);
		x = f[x][0];
	}

	ans.append(g[x]);
	return ans.eval();
}

int n, q; 

int main() {
	int i;
	n = inp(); q = inp();
	for(i = 1; i <= n; i++) scanf("%lld", g + i);
	for(i = 1; i < n; i++) {
		int u = inp(), v = inp();
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}

	dfs(1, 0);

	for(i = 1; i <= q; i++) {
		int u = inp(), v = inp();
		printf("%lld\n", query(u, v));
	}
	
	return 0;
}



