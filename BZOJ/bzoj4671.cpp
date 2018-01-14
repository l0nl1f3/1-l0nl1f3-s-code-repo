#include <bits/stdc++.h>

#define fir first
#define sec second
#define MP make_pair
#define PB push_back

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

const int MaxN = 67;

int s, n, g[MaxN][MaxN][MaxN], c[MaxN]; 

LL b[MaxN], bn, ans, fac[MaxN];
void eval(int x) {
	bn = 0;
	for(int i = 1; i <= n; i++)
		for(int j = i + 1; j <= n; j++) {
			if(c[i] ^ c[j]) {
				LL u = 0;
				for(int k = 0; k < s; k++)
					if(g[k][i][j]) u |= 1ll << k;
				for(int k = 1; k <= bn; k++)
					if((u ^ b[k]) < u) u ^= b[k];
				if(u) b[++bn] = u;
			}
		}
	ans += (fac[x - 1] << s - bn);
}

void dfs(int x, int u) {
	if(x > n) eval(u);
	else {
		for(int i = 1; i <= u; i++) c[x] = i, dfs(x + 1, u);
		dfs(x + 1, c[x] = u + 1);
	}
} 
int main() {
	int i, j, k;
	s = read(); //read();
	for(i = 0; i < s; i++) {
		char a[233]; int t = 0;
		scanf("%s", a);
		int m = strlen(a);
		for(n = 1; n * (n - 1) / 2 != m; n++);
		for(j = 1; j <= n; j++)
			for(k = j + 1; k <= n; k++)
				g[i][j][k] = a[t++] - '0';
	}
	fac[0] = 1;
	for(i = 1; i <= n; i++) fac[i] = -fac[i - 1] * i;
	dfs(1, 0);
	cout << ans << endl;
	return 0;
}



