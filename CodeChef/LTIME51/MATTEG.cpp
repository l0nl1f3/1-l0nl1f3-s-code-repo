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

const int MaxN = 1234;
const int MaxState = 1953125 + MaxN; 
int r, c, n, sx, sy, x[MaxN], y[MaxN], val[MaxN][MaxN];

int dx[] = {0, 1, -1, 1, -1};
int dy[] = {0, 1, -1, -1, 1};

#define exp EMMMMMM
int f[MaxState], exp[MaxN];

int get_bit(int p, int i) {
	return (p/exp[i]) % 5;
}

void solve() {
	int ans = val[sx][sy], i, j, k;
	f[0] = ans;
	for(i = 1; i < exp[n]; i++) {
		int nx = sx, ny = sy;
		for(j = 0; j < n; j++) {
			if(k = get_bit(i, j))
				nx += dx[k] * x[j],
				ny += dy[k] * y[j];
		}
		
		f[i] = -1e9;
		if(nx < 0 || nx >= r || ny < 0 || ny >= c)	continue; 
		for(j = 0; j < n; j++) 
			if(k = get_bit(i, j))
				cmax(f[i], f[i - exp[j] * k] + val[nx][ny]);
		cmax(ans, f[i]);
	}
	cout << ans << endl;
} 

int main() {
	int i, j, T = inp(); exp[0] = 1;
	for(i = 1; i <= 10; i++) exp[i] = exp[i - 1] * 5;
	while(T--) {
		r = inp(); c = inp(); n = inp(); sx = inp(); sy = inp();
		
		for(i = 0; i < n; i++)
			x[i] = inp();
		for(i = 0; i < n; i++)
			y[i] = inp();
			
		for(i = 0; i < r; i++)
			for(j = 0; j < c; j++)
				val[i][j] = inp();
		solve();
	}
	return 0;
}



