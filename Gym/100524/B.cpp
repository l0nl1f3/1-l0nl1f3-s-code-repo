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

const int MaxN = 123, P = 175781251;
int n, f[MaxN], g[MaxN], h[MaxN], c[MaxN][MaxN];

int exp(int a, int n) {
	int res = 1;
	for(; n; n >>= 1) {
		if(n & 1) res = (LL) res * a % P;
		a = (LL) a * a % P; 
	}
	return res;
}

int main() {
	int i, j;
	freopen("bipartite.in", "r", stdin);
	freopen("bipartite.out", "w", stdout);
	c[0][0] = 1;
	for(i = 1; i < MaxN; i++) {
		c[i][0] = 1;
		for(j = 1; j <= i; j++)
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % P;
	}
	for(i = 1; i < MaxN; i++) {
		for(j = 0; j <= i; j++) g[i] = (g[i] + (LL) c[i][j] * exp(3, j * (i - j))) % P;
		for(j = 1; j < i; j++) f[i] = (f[i] + (LL) c[i - 1][j] * f[j]  % P * f[i - j] % P) % P;
		f[i] = ((LL) g[i] * exp(2, P - 2) % P - f[i]) % P; f[i] = (f[i] + P) % P; 
	}
	while(n = read(), n) cout << (f[n] + P) % P << endl;
	return 0;
}



