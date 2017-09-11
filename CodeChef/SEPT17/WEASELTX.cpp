#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;
typedef long long LL;
typedef unsigned long long u64;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int inp() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 301234;

int n, q; LL x0[MaxN], x1[MaxN];
vector<int> e[MaxN];

void dfs(int x, int dep = 0, int fa = -1) {
	if(dep)
		x1[dep] ^= x0[x];
	for(auto y : e[x]) 
		if(y != fa)
			dfs(y, dep + 1, x); 
}

const int bit = 18, P = 9, pN = (1 << 9);
LL sum[pN << 1][pN << 1], half[MaxN];

int main() {                
	int i, j;
	n = inp(); q = inp();
	for(i = 1; i < n; i++) {
		int u = inp(), v = inp();
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	for(i = 0; i < n; i++) scanf("%lld", x0 + i);
	
	dfs(0);
	
	for(i = 0; i < (1 << bit); i++) {
		int s = (i & (pN - 1)); 
		for(s ^= (pN - 1), j = s; ; j = j - 1 & s) {
			sum[i >> P][j] ^= x1[i]; if(!j) break;
		}
	}
	
	for(i = 0; i < (1 << bit); i++) {
		int s = (i >> P); 
		for(s ^= (pN - 1), j = s; ; j = j - 1 & s) {
			half[i] ^= sum[j][i & (pN - 1)];
			if(!j) break;
		}
	}
	
	while(q--) {
		LL d; scanf("%lld", &d);
		printf("%lld\n", d ? (x0[0] ^ half[d - 1 & ((1 << bit) - 1)]) : x0[0]);
	}
	return 0;
}



