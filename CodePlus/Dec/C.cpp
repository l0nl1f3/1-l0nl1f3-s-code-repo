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

const int MaxN = 500, P = 1e9 + 7;

int n, m;  char s[MaxN][MaxN];

int add(int x, int y) { return x + y >= P ? x + y - P : x + y; }
int sub(int x, int y) {	return x - y < 0 ? x - y + P : x - y;  }
int mul(int x, int y) {	return (LL) x * y % P; }
int exp(int x, LL n) {
	int res = 1;
	for(; n; n >>= 1) {
		if(n & 1) 
			res = mul(res, x);
		x = mul(x, x);
	}
	return res;
}

int g[MaxN][MaxN];
int gauss(int N){
	int i, j, k, l, o;
	for(l = j = 1; j <= N; j++){
		for(k = j; k <= N; k++)
			if(g[j][k])	break;
		if(k == N + 1)	return 0;
		if(k > j)
			for(l *= -1, o = j; o <= N; o++)
				swap(g[j][o], g[k][o]);
		l = mul(l, g[j][j]);
		o = exp(g[j][j], P - 2);
		for(k = j; k <= N; k++)
			g[j][k] = mul(g[j][k], o);
		for(k = j + 1; k <= N; k++)
			if(g[k][j])
				for(o = N;o >= j;o--)
					g[k][o] = sub(g[k][o], mul(g[k][j], g[j][o]));
	}
	
	return l < 0 ? l + P : l;
}

int f[MaxN * MaxN], id[MaxN * MaxN];
int find(int x) {
	return f[x] == x ? x : f[x] = find(f[x]);
}

int loop, N;

void mrg(int x, int y) {
	x = find(x); y = find(y);
	if(x == y) loop = 1;
	else
		f[x] = y;
}

void Add(int x, int y) {
	x = id[find(x)];
	y = id[find(y)];
	++g[y][y]; --g[x][y];
}

void solve() {
	int i, j; N = loop = 0;
	for(i = 0; i <= n * m; i++) f[i] = i;
	for(i = 1; i <= n; i++) 
		for(j = 1; j <= m; j++) {
			++N;
			if(s[i][j] == 'L')
				if(j > 1) mrg(N - 1, N);
				else mrg(0, N);
			if(s[i][j] == 'R')
				if(j < m) mrg(N + 1, N);
				else mrg(0, N);
			if(s[i][j] == 'U')
				if(i > 1) mrg(N - m, N);
				else mrg(0, N);
			if(s[i][j] == 'D')
				if(i < n) mrg(N + m, N);
				else mrg(0, N);
		}
	if(loop) {
		puts("0"); return;
	}
	int M = 0;
	for(i = 0; i <= n * m; i++) if(f[i] == i && i != find(0)) id[i] = ++M; id[find(0)] = ++M;
	N = 0;
	memset(g, 0, sizeof(g));
	for(i = 1; i <= n; i++) 
		for(j = 1; j <= m; j++) {
			++N;
			if(s[i][j] == '.') {
				if(j > 1) Add(N - 1, N); else Add(0, N);
				if(j < m) Add(N + 1, N); else Add(0, N);
				if(i > 1) Add(N - m, N); else Add(0, N);
				if(i < n) Add(N + m, N); else Add(0, N);
			}
		}
	for(i = 1; i <= M; i++)
		for(j = 1; j <= M; j++)
			g[i][j] = (g[i][j] % P + P) % P;
	cout << gauss(M - 1) << endl;
}
int main() {
	int i, T = read();
	while(T--) {
		n = read(); m = read();
		for(i = 1; i <= n; i++) scanf("%s", s[i] + 1);
		solve();
	}
	return 0;
}

