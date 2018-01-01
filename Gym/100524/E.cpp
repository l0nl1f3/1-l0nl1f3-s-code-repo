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

const int MaxN = 3333;

int n, a[MaxN]; LL f[MaxN], g[MaxN][MaxN], b[MaxN];
int main() {
	int i, j;
	freopen("ebola.in", "r", stdin);
	freopen("ebola.out", "w", stdout);
	
	while(n = read(), n) {
		for(i = 1; i <= n; i++) b[i] = b[i - 1] + (a[i] = read());
		for(j = 1; j <= n; j++)
			for(i = j - 1; i; i--) 
				g[i][j] = g[i + 1][j] + b[j] - b[i] + min(b[j] - b[i], 3ll * (j - i) * a[i]);
		for(i = 1; i <= n; i++) {
			f[i] = f[i - 1] + 2ll * (b[n] - b[i]);
			for(j = 1; j <= i; j++)
				cmin(f[i], f[j - 1] + g[j][i] + (4LL * (i - j + 1) - 2) * (b[n] - b[i]));
		} 
		cout << f[n] << endl;
	}
	return 0;
}



