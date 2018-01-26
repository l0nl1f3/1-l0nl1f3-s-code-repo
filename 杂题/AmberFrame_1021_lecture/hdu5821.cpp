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
	for (ch = getchar(); !isdigit(ch); ch = getchar())
		if (ch == '-') f = -1;
	for (; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 2333;

int n, q, a[MaxN], b[MaxN], c[MaxN], d[MaxN];
 
void solve() {
	n = read(); q = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++) b[i] = read();
	for (int i = 1; i <= n; i++) {
		c[i] = 0; 
		for (int j = 1; j <= n; j++) {
			if (a[i] == b[j]) {
				c[i] = j;
				b[j] = -1;
				break;
			}
		}
	}
	
	while(q--) {
		int l = read(), r = read();
		sort(c + l, c + r + 1);
	}

	for (int i = 1; i <= n; i++) 
		if (c[i] != i) {
			puts("No"); return;
		}
	puts("Yes");
}
int main() {
	int T = read();
	while (T--) 
		solve();
	return 0;
}



