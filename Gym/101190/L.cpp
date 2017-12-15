#include <bits/stdc++.h>

#define fir first
#define sec second
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

const int MaxN = 7700, MaxM = 1234, MaxL = 11234;

int size(int x) {
	int ans = 2;
	while(x) ans++, x /= 10;
	return ans;
}

LL f[MaxM][MaxL], g[MaxM][MaxL];
int pr[MaxN], np[MaxN], pn, T; 

void dfs(int p, int t, LL S) {
	if(S > R) return;
	if(S + f[p + 1][t] + g[p + 1][t] * (2 + T) < L) return;
	if(!t) {
		
	}
}
int main() {
	int i, j;
	freopen("list.in", "r", stdin);
	freopen("list.out", "w", stdout);

	for(i = 2; i < MaxN; i++) 
		if(!np[i]) 
			for(j = 1; j < MaxN; j += i)
				np[j] = 1;
	for(i = 2; i < MaxN; i++) if(!np[i]) pr[++pn] = i;
	int n = pn, m; 
	for(i = 1; i <= 60; i++) m += pr[i];
	for(i = n; i; i--)
		for(j = 0; j < m; j++) {
			f[i][j] = f[i + 1][j] + (j >= pr[i] ? f[i + 1][j - pr[i]] + g[i + 1][j - pr[i]] * size(pr[i]) : 0);
			g[i][j] = g[i + 1][j] + (j >= pr[i] ? g[i + 1][j - pr[i]] : 0);
		}	
	LL l, r, p = 0;
	cin >> l >> r;
	for(i = 2; ; i++) 
		dfs(0, i, p), p += f[1][i] + 2 * g[1][i];
		
	return 0;
}

