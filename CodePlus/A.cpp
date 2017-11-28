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

const int MaxN = 5333;

int n, m, f[MaxN][MaxN], g[MaxN][MaxN], h[MaxN][MaxN], a[MaxN], b[MaxN], d[5][5]; char s[MaxN];

int F(char c) {
	if(c == 'A') return 1;
	if(c == 'T') return 2;
	if(c == 'G') return 3;
	return 4;	
}

int main() {
	int i, j;
	scanf("%s", s + 1); n = strlen(s + 1);
	for(i = 1; i <= n; i++) a[i] = F(s[i]);
	scanf("%s", s + 1); m = strlen(s + 1);
	for(i = 1; i <= m; i++) b[i] = F(s[i]);
	for(i = 1; i <= 4; i++)
		for(j = 1; j <= 4; j++)
			d[i][j] = read();
	int A = read(), B = read();
	memset(h, 0x80, sizeof(h));
	memset(g, 0x80, sizeof(g));
	memset(f, 0x80, sizeof(f));
	f[0][0] = 0;
	for(i = 1; i <= m; i++) f[0][i] = -B - A * (i - 1);
	for(i = 1; i <= n; i++) f[i][0] = -B - A * (i - 1);
	for(i = 1; i <= n; i++)
		for(j = 1; j <= m; j++) {
			f[i][j] = f[i - 1][j - 1] + d[a[i]][b[j]];
			g[i][j] = max(g[i - 1][j] - B, f[i - 1][j] - A);
			h[i][j] = max(h[i][j - 1] - B, f[i][j - 1] - A);
			cmax(f[i][j], max(h[i][j], g[i][j]));
		}
	cout << f[n][m];
	return 0;
}

