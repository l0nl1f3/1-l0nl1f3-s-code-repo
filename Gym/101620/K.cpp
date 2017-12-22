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

const int MaxN = 520;

int n, x[MaxN][7], b[MaxN], c[7];

int fix(int x) {
	return (x % 7 + 7) % 7;
}

int f[MaxN][MaxN][7], g[MaxN][MaxN][7];

int main() {
	int i, j, k, l;
	n = read();
	for(i = 1; i <= n; i++) {
		for(x[i][0] = read(), j = 1; j < 7; j++) 
			x[i][j] = x[i][j - 1] / 10 + x[i][j - 1] % 10 * 1000000;
		if(x[i][0] == x[i][1]) i--, n--;
	}
	for(i = 1; i <= n; i++) b[i] = max_element(x[i], x[i] + 7) - x[i];
	for(i = 1; i <= n + 1; i++) c[fix(b[i] - b[i - 1])]++;
	int ans = n + 1 - c[0];
	for(i = 1; i < 4; i++) {
		int u = min(c[i], c[7 - i]);
		c[i] -= u; c[7 - i] -= u; ans -= u;
	}
	int x = c[1] ? 1 : 6;
	int y = c[2] ? 2 : 5;
	int z = c[3] ? 3 : 4;
	memset(f, -1, sizeof(f)); f[0][0][0] = 0;
	for(l = 0; l <= c[x]; l++) {
		for(i = 0; i <= c[y]; i++)
			for(j = 0; j <= c[z]; j++)
				for(k = 0; k < 7; k++)
					g[i][j][k] = f[i][j][k], f[i][j][k] = -1;
		for(i = 0; i <= c[y]; i++)
			for(j = 0; j <= c[z]; j++)
				for(k = 0; k < 7; k++)
					if(g[i][j][k] != -1) {
						if(l < c[x]) cmax(f[i][j][fix(k + x)], g[i][j][k] + !fix(k + x));
						if(i < c[y]) cmax(g[i + 1][j][fix(k + y)], g[i][j][k] + !fix(k + y));
						if(j < c[z]) cmax(g[i][j + 1][fix(k + z)], g[i][j][k] + !fix(k + z));
					}
	}
	printf("%d\n", ans - g[c[y]][c[z]][0]);
 	return 0;
}

